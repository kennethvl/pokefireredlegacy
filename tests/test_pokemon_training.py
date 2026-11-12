"""Transactions use production pricing/application functions and actual IV field IDs."""
import unittest
import json
import struct
from collections import deque
import test_exp_progression as progression

ROOT = progression.ROOT


class PokemonTrainingTests(unittest.TestCase):
    def test_prices_payment_and_real_iv_changes(self):
        source = (ROOT / 'src/pokemon_training.c').read_text()
        start = source.index('static const u8 sIvFields[')
        fields = source[start:source.index(';', start) + 1]
        code = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "constants/global.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/pokemon_training.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int bool8;
#define TRUE 1
#define FALSE 0
struct Pokemon {u32 fields[100];} gPlayerParty[PARTY_SIZE];
struct {u32 money;} save, *gSaveBlock1Ptr = &save;
u16 gSpecialVar_0x8004, gSpecialVar_0x8005, gSpecialVar_0x8006;
int recalculations;
u32 GetMonData(struct Pokemon *mon, int field) {return mon->fields[field];}
u8 GetStatNature(struct Pokemon *mon) {return mon->fields[MON_DATA_STAT_NATURE];}
void SetMonData(struct Pokemon *mon, int field, const void *value) {
    mon->fields[field] = *(const u8 *)value;
    if (field == MON_DATA_STAT_NATURE) recalculations++;
}
void CalculateMonStats(struct Pokemon *mon) {(void)mon; recalculations++;}
bool8 IsEnoughMoney(u32 *money, u32 price) {return *money >= price;}
void RemoveMoney(u32 *money, u32 price) {assert(*money >= price); *money -= price;}
''' + fields + '\n' + progression.function('src/pokemon_training.c', 'GetTrainingPrice')
        code += progression.function('src/pokemon_training.c', 'ApplyPokemonTraining')
        code += r'''
void setup(void) {
    memset(gPlayerParty, 0, sizeof(gPlayerParty));
    gPlayerParty[0].fields[MON_DATA_SPECIES] = SPECIES_ALAKAZAM;
    gPlayerParty[0].fields[MON_DATA_PERSONALITY] = NATURE_ADAMANT;
    gPlayerParty[0].fields[MON_DATA_STAT_NATURE] = NATURE_ADAMANT;
    gSpecialVar_0x8004 = 0; save.money = 100000; recalculations = 0;
}
int main(void) {
    u32 price;
    int i, j;
    setup(); gSpecialVar_0x8006 = TRAINING_NATURE; gSpecialVar_0x8005 = NATURE_MODEST;
    assert(GetTrainingPrice(&price) == TRAINING_SUCCESS && price == 5000);
    assert(ApplyPokemonTraining() == TRAINING_SUCCESS && save.money == 95000);
    assert(GetStatNature(&gPlayerParty[0]) == NATURE_MODEST);
    assert(gPlayerParty[0].fields[MON_DATA_PERSONALITY] == NATURE_ADAMANT);
    assert(recalculations == 1);
    assert(ApplyPokemonTraining() == TRAINING_NO_CHANGE && save.money == 95000);
    gSpecialVar_0x8005 = NATURE_ADAMANT; save.money = 4999;
    assert(ApplyPokemonTraining() == TRAINING_NO_MONEY && GetStatNature(&gPlayerParty[0]) == NATURE_MODEST);
    for (i = 0; i < NUM_STATS; i++) {
        setup(); gSpecialVar_0x8006 = TRAINING_IV; gSpecialVar_0x8005 = i;
        assert(ApplyPokemonTraining() == TRAINING_SUCCESS && save.money == 95000);
        for (j = 0; j < NUM_STATS; j++) assert(gPlayerParty[0].fields[sIvFields[j]] == (i == j ? 31 : 0));
        assert(ApplyPokemonTraining() == TRAINING_NO_CHANGE && save.money == 95000);
    }
    setup(); gSpecialVar_0x8006 = TRAINING_IV; gSpecialVar_0x8005 = TRAINING_ALL_IVS;
    gPlayerParty[0].fields[MON_DATA_HP_IV] = gPlayerParty[0].fields[MON_DATA_ATK_IV] = 31;
    assert(GetTrainingPrice(&price) == TRAINING_SUCCESS && price == 20000);
    save.money = 19999;
    assert(ApplyPokemonTraining() == TRAINING_NO_MONEY);
    assert(gPlayerParty[0].fields[MON_DATA_DEF_IV] == 0 && save.money == 19999);
    save.money = 20000; assert(ApplyPokemonTraining() == TRAINING_SUCCESS && save.money == 0);
    for (i = 0; i < NUM_STATS; i++) assert(gPlayerParty[0].fields[sIvFields[i]] == 31);
    assert(recalculations == 1 && ApplyPokemonTraining() == TRAINING_NO_CHANGE);
    // These are the stored IVs read by breeding and Hidden Power, rather than an overlay.
    assert(gPlayerParty[0].fields[MON_DATA_HP_IV] & 1);
    assert(gPlayerParty[0].fields[MON_DATA_SPDEF_IV] & 2);
    setup(); gSpecialVar_0x8006 = TRAINING_IV; gSpecialVar_0x8005 = TRAINING_ALL_IVS;
    gPlayerParty[0].fields[MON_DATA_IS_EGG] = TRUE;
    assert(ApplyPokemonTraining() == TRAINING_INVALID && save.money == 100000);
    gPlayerParty[0].fields[MON_DATA_IS_EGG] = FALSE; gSpecialVar_0x8004 = PARTY_SIZE;
    assert(ApplyPokemonTraining() == TRAINING_INVALID && save.money == 100000);
    gSpecialVar_0x8004 = 0; gSpecialVar_0x8005 = TRAINING_CANCEL;
    assert(ApplyPokemonTraining() == TRAINING_INVALID && save.money == 100000);
    puts("Training: individual/batch prices, no-op/cancel/egg rejection, funds and actual IVs passed");
}
'''
        progression.ProgressionTests.compile_and_run(self, code)

    def test_every_center_has_reachable_adjacent_trainers(self):
        layouts = {layout['id']: layout for layout in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']}
        maps = sorted((ROOT / 'data/maps').glob('*PokemonCenter_1F/map.json'))
        self.assertEqual(len(maps), 19)
        for path in maps:
            data = json.loads(path.read_text())
            layout = layouts[data['layout']]
            width, height = layout['width'], layout['height']
            raw = (ROOT / layout['blockdata_filepath']).read_bytes()
            tiles = struct.unpack('<' + 'H' * (len(raw) // 2), raw)
            nature = [o for o in data['object_events'] if o['script'] == 'PokemonTraining_EventScript_Nature']
            ivs = [o for o in data['object_events'] if o['script'] == 'PokemonTraining_EventScript_Ivs']
            self.assertEqual(len(nature), 1, path.parent.name)
            self.assertEqual(len(ivs), 1, path.parent.name)
            man, woman = nature[0], ivs[0]
            self.assertEqual(man['graphics_id'], 'OBJ_EVENT_GFX_OLD_MAN_1')
            self.assertEqual(woman['graphics_id'], 'OBJ_EVENT_GFX_OLD_WOMAN')
            self.assertEqual((woman['x'], woman['y']), (man['x'] + 1, man['y']))
            occupied = {(o['x'], o['y']) for o in data['object_events']}
            self.assertEqual(len(occupied), len(data['object_events']), path.parent.name)
            self.assertLessEqual(len(data['object_events']), 15)
            warps = {(w['x'], w['y']) for w in data['warp_events']}
            for npc in [man, woman]:
                cell = npc['y'] * width + npc['x']
                self.assertEqual((tiles[cell] >> 10) & 3, 0, path.parent.name)
                self.assertEqual(tiles[cell] >> 12, npc['elevation'])
                self.assertNotIn((npc['x'], npc['y']), warps)
            # Flood the walkable floor from a doorway, treating existing NPCs as obstacles.
            start = max(data['warp_events'], key=lambda w: w['y'])
            seen, queue = set(), deque([(start['x'], start['y'])])
            while queue:
                x, y = queue.popleft()
                if (x, y) in seen or (x, y) in occupied or not (0 <= x < width and 0 <= y < height):
                    continue
                if (tiles[y * width + x] >> 10) & 3:
                    continue
                seen.add((x, y))
                queue.extend([(x-1,y),(x+1,y),(x,y-1),(x,y+1)])
            for npc in [man, woman]:
                x, y = npc['x'], npc['y']
                self.assertTrue(any(pos in seen for pos in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]), path.parent.name)


if __name__ == '__main__':
    unittest.main()

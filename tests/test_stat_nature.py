"""Host regressions for independent stat nature and its compact Summary label."""
import re
import unittest
import test_exp_progression as progression

ROOT = progression.ROOT


class StatNatureTests(unittest.TestCase):
    def test_stored_modifier_and_stat_math(self):
        source = (ROOT / 'src/pokemon.c').read_text()
        getter = source[source.index('    case MON_DATA_STAT_NATURE:'):]
        getter = getter[:getter.index('    case MON_DATA_NATURE:')]
        setter_start = source.index('    case MON_DATA_STAT_NATURE:', source.index('void SetBoxMonData('))
        setter = source[setter_start:source.index('    case MON_DATA_NATURE:', setter_start)]
        table_start = source.index('const s8 gNatureStatTable[')
        table = source[table_start:source.index('\n};', table_start) + 3]
        code = r'''
#define IS_POKEMON_C
#include "global.h"
#include "pokemon.h"
#include <assert.h>
#include <stdio.h>
u32 ReadNature(struct BoxPokemon *boxMon) {
    struct PokemonSubstruct0 *substruct0 = &boxMon->secure.substructs[0].type0;
    u32 retVal = 0;
    switch (MON_DATA_STAT_NATURE) {
''' + getter + r'''} return retVal;
}
void WriteNature(struct BoxPokemon *boxMon, u8 nature) {
    struct PokemonSubstruct0 *substruct0 = &boxMon->secure.substructs[0].type0;
    const u8 *data = &nature;
    switch (MON_DATA_STAT_NATURE) {
''' + setter + r'''}
}
u32 GetMonData(struct Pokemon *mon, s32 field, u8 *unused) {
    (void)unused;
    if (field == MON_DATA_PERSONALITY) return mon->box.personality;
    assert(field == MON_DATA_STAT_NATURE); return ReadNature(&mon->box);
}
''' + table + '\n' + progression.function('src/pokemon.c', 'GetNature')
        code += progression.function('src/pokemon.c', 'GetStatNature')
        code += progression.function('src/pokemon.c', 'ModifyStatByNature')
        code += r'''
int main(void) {
    struct Pokemon mon = {0}, reloaded;
    assert(sizeof(struct PokemonSubstruct0) == 12);
    assert(sizeof(struct BoxPokemon) == 80 && sizeof(struct Pokemon) == 100);
    mon.box.personality = NATURE_ADAMANT;
    mon.box.secure.substructs[0].type0.forme = 2;
    assert(GetNature(&mon) == NATURE_ADAMANT && GetStatNature(&mon) == NATURE_ADAMANT);
    WriteNature(&mon.box, NATURE_MODEST);
    assert(mon.box.personality == NATURE_ADAMANT && GetNature(&mon) == NATURE_ADAMANT);
    assert(GetStatNature(&mon) == NATURE_MODEST);
    assert(mon.box.secure.substructs[0].type0.forme == 2);
    assert(ModifyStatByNature(GetStatNature(&mon), 100, STAT_ATK) == 90);
    assert(ModifyStatByNature(GetStatNature(&mon), 100, STAT_SPATK) == 110);
    assert(ModifyStatByNature(GetStatNature(&mon), 100, STAT_HP) == 100);
    memcpy(&reloaded, &mon, sizeof(mon));
    reloaded.box.secure.substructs[0].type0.species = SPECIES_KADABRA;
    assert(GetStatNature(&reloaded) == NATURE_MODEST);
    WriteNature(&mon.box, NATURE_ADAMANT);
    assert(mon.box.secure.substructs[0].type0.statNature == 0);
    assert(GetStatNature(&mon) == NATURE_ADAMANT);
    WriteNature(&mon.box, 255); assert(GetStatNature(&mon) == NATURE_ADAMANT);
    puts("Stat nature: record layout, original nature, persistence, forms and modifiers passed");
}
'''
        progression.ProgressionTests.compile_and_run(self, code)

    def test_synchronize_uses_effective_nature_every_time(self):
        code = progression.COMMON + r'''
#include "constants/abilities.h"
int ability = ABILITY_SYNCHRONIZE, randomCalls;
u8 GetMonAbility(struct Pokemon *mon) {(void)mon; return ability;}
u8 GetStatNature(struct Pokemon *mon) {return mon->fields[MON_DATA_STAT_NATURE];}
u16 Random(void) {return randomCalls++;}
''' + progression.function('src/wild_encounter.c', 'PickWildMonNature') + r'''
int main(void) {
    int i;
    gPlayerParty[0].fields[MON_DATA_PERSONALITY] = NATURE_ADAMANT;
    gPlayerParty[0].fields[MON_DATA_STAT_NATURE] = NATURE_MODEST;
    for (i = 0; i < 100; i++) assert(PickWildMonNature() == NATURE_MODEST);
    assert(randomCalls == 0);
    // The lead's HP is deliberately irrelevant, matching the existing lead-ability rule.
    gPlayerParty[0].fields[MON_DATA_HP] = 0;
    assert(PickWildMonNature() == NATURE_MODEST);
    ability = ABILITY_NONE;
    assert(PickWildMonNature() < NUM_NATURES && randomCalls == 1);
    ability = ABILITY_SYNCHRONIZE; gPlayerParty[0].fields[MON_DATA_SANITY_IS_EGG] = TRUE;
    assert(PickWildMonNature() < NUM_NATURES && randomCalls == 2);
    puts("Synchronize: 100 percent effective nature, random fallback and egg exclusion passed");
}
'''
        progression.ProgressionTests.compile_and_run(self, code)

    def test_summary_labels_fit(self):
        text = (ROOT / 'src/text.c').read_text()
        body = re.search(r'sFontSmallLatinGlyphWidths\[\]\s*=\s*\{(.*?)\};', text, re.S).group(1)
        widths = [int(n) for n in re.findall(r'\b\d+\b', body)]
        charmap = {char: int(code, 16) for char, code in re.findall(r"^'(.)'\s*=\s*([0-9A-F]{2})", (ROOT / 'charmap.txt').read_text(), re.M)}
        names = re.findall(r'_\("([A-Za-z]+)"\)', (ROOT / 'src/data/text/nature_names.h').read_text())
        self.assertEqual(len(names), 25)
        for original in names:
            for selected in names:
                label = f'Nature: {original} / Stat nature: {selected}'
                self.assertLessEqual(sum(widths[charmap[c]] for c in label), 224, label)
                self.assertLess(len(label), 80)


if __name__ == '__main__':
    unittest.main()

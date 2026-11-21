"""Host-side regressions for Mom's Pokémon Center services.

Run with: python3 -m unittest discover -s tests
The rules tests compile src/mon_modifier_logic.c (which depends on nothing but C) and check it directly.
"""
import unittest

import test_exp_progression as progression

ROOT = progression.ROOT


class MomRulesTests(unittest.TestCase):
    def test_service_rules_and_dialogue_stages(self):
        code = r'''
#include <assert.h>
#include "mon_modifier_logic.h"
#include "../src/mon_modifier_logic.c"
#define S(name) MODLOGIC_MOM_SERVICE_##name
#define STAGE(name) MODLOGIC_MOM_STAGE_##name
int main(void) {
    const unsigned char maxed[6] = {31, 31, 31, 31, 31, 31};
    const unsigned char mixed[6] = {31, 0, 31, 31, 31, 31};
    const unsigned char maxEvs[6] = {255, 255, 255, 255, 255, 255};
    const unsigned char someEvs[6] = {255, 255, 255, 255, 255, 4};
    unsigned char s;

    assert(ModLogic_CountIVsBelowMax(maxed, 31) == 0);
    assert(ModLogic_CountIVsBelowMax(mixed, 31) == 1);

    assert(ModLogic_CanSwapAbility(10, 20));
    assert(!ModLogic_CanSwapAbility(10, 0));   // only one ability
    assert(!ModLogic_CanSwapAbility(10, 10));  // same ability twice
    assert(ModLogic_OtherAbilitySlot(0) == 1 && ModLogic_OtherAbilitySlot(1) == 0);

    // Eggs: every service refuses them
    for (s = 0; s < MODLOGIC_MOM_NUM_SERVICES; s++)
        assert(ModLogic_MomServiceIsUseless(s, 1, mixed, 31, someEvs, 255, 10, 20));

    assert(ModLogic_MomServiceIsUseless(S(HYPER_TRAINING), 0, maxed, 31, someEvs, 255, 10, 20));
    assert(!ModLogic_MomServiceIsUseless(S(HYPER_TRAINING), 0, mixed, 31, someEvs, 255, 10, 20));
    assert(ModLogic_MomServiceIsUseless(S(MAX_EVS), 0, mixed, 31, maxEvs, 255, 10, 20));
    assert(!ModLogic_MomServiceIsUseless(S(MAX_EVS), 0, mixed, 31, someEvs, 255, 10, 20));
    assert(ModLogic_MomServiceIsUseless(S(ABILITY), 0, mixed, 31, someEvs, 255, 10, 0));
    assert(!ModLogic_MomServiceIsUseless(S(ABILITY), 0, mixed, 31, someEvs, 255, 10, 20));
    // Nature, Hidden Power and the Move Relearner are offered to any non-Egg (the relearner checks moves itself)
    assert(!ModLogic_MomServiceIsUseless(S(NATURE), 0, maxed, 31, maxEvs, 255, 10, 0));
    assert(!ModLogic_MomServiceIsUseless(S(HIDDEN_POWER), 0, maxed, 31, maxEvs, 255, 10, 0));
    assert(!ModLogic_MomServiceIsUseless(S(RELEARN_MOVES), 0, maxed, 31, maxEvs, 255, 10, 0));

    // Story stages: (badges, rescued Mr. Fuji, Silph Co. freed, champion). Later stages win.
    assert(ModLogic_MomDialogueStage(0, 0, 0, 0) == STAGE(FRESH));
    assert(ModLogic_MomDialogueStage(1, 0, 0, 0) == STAGE(BADGES));
    assert(ModLogic_MomDialogueStage(4, 1, 0, 0) == STAGE(ROCKETS));
    assert(ModLogic_MomDialogueStage(5, 1, 1, 0) == STAGE(SILPH_SAVED));
    assert(ModLogic_MomDialogueStage(8, 1, 1, 0) == STAGE(ALL_BADGES));
    assert(ModLogic_MomDialogueStage(8, 1, 1, 1) == STAGE(CHAMPION));
    assert(ModLogic_MomDialogueStage(0, 0, 0, 1) == STAGE(CHAMPION));
    return 0;
}
'''
        progression.ProgressionTests.compile_and_run(self, code)


class MomTextTests(unittest.TestCase):
    def test_mom_dialogue_fits_the_message_box(self):
        import re
        text = (ROOT / 'src/text.c').read_text()
        charmap = {char: int(code, 16) for char, code in re.findall(r"^'(.)'\s*=\s*([0-9A-F]{2})", (ROOT / 'charmap.txt').read_text(), re.M)}
        charmap["'"] = int(re.search(r"^'\\''\s*=\s*([0-9A-F]{2})", (ROOT / 'charmap.txt').read_text(), re.M).group(1), 16)
        letters = [charmap[c] for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz']
        source = (ROOT / 'src/mom_services.c').read_text()
        lines = re.findall(r'sText_Mom(?:Hello|Bye)\w+\[\] = _\("(.*?)"\);', source)
        self.assertEqual(len(lines), 6 * 3 + 6 * 2)
        # Mom speaks in the female font, or the normal one if her text color isn't set
        for font in ('sFontFemaleLatinGlyphWidths', 'sFontNormalLatinGlyphWidths'):
            body = re.search(font + r'\[\]\s*=\s*\{(.*?)\};', text, re.S).group(1)
            widths = [int(n) for n in re.findall(r'\b\d+\b', body)]
            name = 7 * max(widths[c] for c in letters)  # a 7-letter player or rival name of the widest letter
            for message in lines:
                for line in re.split(r'\\[np]', message.rstrip('$')):
                    width = 0
                    for part in re.split(r'(\{PLAYER\}|\{RIVAL\})', line):
                        if part in ('{PLAYER}', '{RIVAL}'):
                            width += name
                        else:
                            width += sum(widths[charmap[c]] for c in part)
                    self.assertLessEqual(width, 26 * 8, f'{font}: {line}')


    def test_nature_labels_fit_their_buffer(self):
        import re
        names = re.findall(r'_\("([A-Z]+)"\)', (ROOT / 'src/data/text/nature_names.h').read_text())
        rows = re.findall(r'\[NATURE_\w+\]\s*=\s*\{([^}]*)\}', (ROOT / 'src/pokemon.c').read_text())
        source = (ROOT / 'src/mom_services.c').read_text()
        stats = [re.search(r'sText_Stat' + s + r'\[\] = _\("(.*?)"\)', source).group(1)
                 for s in ('Atk', 'Def', 'Speed', 'SpAtk', 'SpDef')]
        header = (ROOT / 'include/mom_services.h').read_text()
        length = int(re.search(r'#define MOM_NATURE_OPTION_LENGTH (\d+)', header).group(1))
        internal = (ROOT / 'include/pokemon_storage_system_internal.h').read_text()
        self.assertIn(f'momNatureTexts[NUM_NATURES][{length}]', internal)
        self.assertEqual(len(names), 25)
        self.assertEqual(len(rows), 25)
        for name, row in zip(names, rows):
            values = [int(v) for v in row.split(',')]
            if 1 in values:
                label = f'{name} +{stats[values.index(1)]} -{stats[values.index(-1)]}'
            else:
                label = f'{name} (neutral)'
            self.assertLess(len(label), length, label)  # plus the end-of-string byte


    def test_pc_messages_fit_the_pc_message_box(self):
        import re
        charmap_text = (ROOT / 'charmap.txt').read_text()
        charmap = {char: int(code, 16) for char, code in re.findall(r"^'(.)'\s*=\s*([0-9A-F]{2})", charmap_text, re.M)}
        charmap["'"] = int(re.search(r"^'\\''\s*=\s*([0-9A-F]{2})", charmap_text, re.M).group(1), 16)
        body = re.search(r'sFontNormalCopy1LatinGlyphWidths\[\]\s*=\s*\{(.*?)\};', (ROOT / 'src/text.c').read_text(), re.S).group(1)
        widths = [int(n) for n in re.findall(r'\b\d+\b', body)]

        def width(text):
            return sum(widths[charmap[c]] for c in text)

        def longest(strings):
            return max(strings, key=width)

        types = re.findall(r'\[TYPE_\w+\]\s*=\s*_\("(.*?)"\)', (ROOT / 'src/battle_main.c').read_text())
        abilities = re.findall(r'\[ABILITY_\w+\]\s*=\s*_\("(.*?)"\)', (ROOT / 'src/data/text/abilities.h').read_text())
        natures = re.findall(r'_\("([A-Z]+)"\)', (ROOT / 'src/data/text/nature_names.h').read_text())
        mom = (ROOT / 'src/mom_services.c').read_text()
        hyper = re.findall(r'sText_\w+IVs?\[\] = _\("(.*?)"\)', mom)
        self.assertEqual(len(hyper), 7)
        self.assertGreater(len(types), 15)
        self.assertGreater(len(abilities), 70)
        fill = {
            'sText_MomHyperConfirm': longest(hyper),
            'sText_MomAbilityConfirm': longest(abilities),
            'sText_MomNatureNow': longest(natures),
            'sText_MomNatureConfirm': longest(natures),
            'sText_MomTypeNow': longest(types),
            'sText_MomTypeConfirm': longest(types),
            'sText_MomAlreadyThat': longest(types + natures),
        }
        tasks = (ROOT / 'src/pokemon_storage_system_tasks.c').read_text()
        messages = re.findall(r'static const u8 (sText_Mom\w+)\[\] = _\("(.*?)"\);', tasks)
        self.assertEqual(len(messages), 12)
        for name, message in messages:
            text = message.replace('{STR_VAR_1}', fill.get(name, ''))
            self.assertNotIn('{', text, name)
            self.assertLessEqual(width(text), 18 * 8, f'{name}: {text}')


class MomPlacementTests(unittest.TestCase):
    def test_mom_stands_in_front_of_every_nurse_on_her_own_tile(self):
        import json
        import re
        import struct

        layouts = {l['id']: l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts'] if 'id' in l}
        centers = sorted((ROOT / 'data/maps').glob('*PokemonCenter_1F/map.json'))
        self.assertEqual(len(centers), 19)
        for path in centers:
            name = path.parent.name
            data = json.loads(path.read_text())
            objects = data['object_events']
            nurses = [o for o in objects if o['graphics_id'] == 'OBJ_EVENT_GFX_NURSE']
            moms = [o for o in objects if o['script'] == 'PokemonCenter_EventScript_Mom']
            self.assertEqual(len(nurses), 1, name)
            self.assertEqual(len(moms), 1, name)
            nurse, mom = nurses[0], moms[0]
            tile = (nurse['x'] - 1, nurse['y'] + 2)

            # One tile left of and two below the nurse: the floor in front of the counter
            self.assertEqual((mom['x'], mom['y']), tile, name)
            self.assertEqual(mom['graphics_id'], 'OBJ_EVENT_GFX_MOM', name)
            self.assertEqual(mom['movement_type'], 'MOVEMENT_TYPE_FACE_DOWN', name)
            self.assertEqual(mom['flag'], 'FLAG_TEMP_10', name)

            # A walkable tile
            layout = layouts[data['layout']]
            blocks = (ROOT / layout['blockdata_filepath']).read_bytes()
            block = struct.unpack_from('<H', blocks, (tile[1] * layout['width'] + tile[0]) * 2)[0]
            self.assertEqual((block >> 10) & 3, 0, name + ': Mom is on a wall or counter')

            # No other NPC (hidden ones included) starts on her tile, and no script moves one there
            for obj in objects:
                if obj is not mom:
                    self.assertNotEqual((obj['x'], obj['y']), tile, name + ': ' + obj['graphics_id'])
            scripts = (path.parent / 'scripts.pory').read_text()
            for x, y in re.findall(r'setobjectxyperm\s+\w+,\s*(\d+),\s*(\d+)', scripts):
                self.assertNotEqual((int(x), int(y)), tile, name + ': setobjectxyperm')
            self.assertNotIn('PokemonTraining_EventScript', path.read_text(), name)

            # The map shows or hides her on every load
            transition = re.search(name + r'_OnTransition::\n(.*?)\n\s*end', scripts, re.S)
            self.assertIsNotNone(transition, name)
            self.assertIn('call PokemonCenter_EventScript_UpdateMom', transition.group(1), name)


if __name__ == "__main__":
    unittest.main()

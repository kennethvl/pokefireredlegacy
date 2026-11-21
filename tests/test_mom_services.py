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


if __name__ == "__main__":
    unittest.main()

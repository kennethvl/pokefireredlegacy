"""Host-side regressions for EXP, level-range moves, and Rare Candy evolution.

Run with: python3 tests/test_exp_progression.py
Compiles the production functions against small engine stubs and real learnsets /
evolution tables. This does not replace ROM/emulator testing of the UI scenes.
"""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


def function(path, name):
    source = (ROOT / path).read_text()
    import re
    match = re.search(r"^(?:static )?(?:void|bool8|u16) " + name + r"\([^;]*?\)\n\{", source, re.M)
    assert match, name
    start = match.start()
    pos = match.end()
    depth = 1
    while depth:
        depth += (source[pos] == "{") - (source[pos] == "}")
        pos += 1
    return source[start:pos] + "\n"


def array(path, name):
    source = (ROOT / path).read_text()
    start = source.index("static const u16 " + name)
    return source[start:source.index("\n};", start) + 3] + "\n"


COMMON = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "constants/global.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/hold_effects.h"
#include "constants/map_types.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int16_t s16;
typedef int32_t s32;
typedef int bool8;
#define TRUE 1
#define FALSE 0
struct Pokemon {u32 fields[100]; u16 moves[4];};
struct Pokemon gPlayerParty[PARTY_SIZE];
u32 GetMonData(struct Pokemon *mon, int field, ...) {return mon->fields[field];}
void SetMonData(struct Pokemon *mon, int field, const void *value) {
    assert(field == MON_DATA_EXP);
    mon->fields[field] = *(const u32 *)value;
}
'''


class ProgressionTests(unittest.TestCase):
    def compile_and_run(self, code):
        with tempfile.TemporaryDirectory(prefix="pokemon-progression-") as tmp:
            source = Path(tmp) / "test.c"
            binary = Path(tmp) / "test"
            source.write_text(code)
            subprocess.run([os.environ.get("CC", "cc"), "-std=c99", "-Wall", "-Wextra",
                            "-Werror", "-Wno-unused-function", "-DFIRERED", "-I", str(ROOT / "include"),
                            "-I", str(ROOT), str(source), "-o", str(binary)], check=True)
            subprocess.run([str(binary)], check=True)

    def test_full_award_and_caps(self):
        code = COMMON + r'''
#define BIT_FLANK 2
#define RET_VALUE_LEVELED_UP 1
#define HEALTHBOX_ALL 0
#define tExpTask_monId data[0]
#define tExpTask_battler data[1]
#define tExpTask_gainedExp data[2]
struct Task {s16 data[16]; void (*func)(u8);} gTasks[1];
struct {u8 growthRate;} gSpeciesInfo[NUM_SPECIES];
u32 gExperienceTables[1][MAX_LEVEL + 1];
u8 gBattlerPartyIndexes[4], gHealthboxSpriteIds[4], gActiveBattler;
void (*gBattlerControllerFuncs[4])(void);
int cap = MAX_LEVEL, doubles, levelMessages, updatedBox, remainingExp;
bool8 IsDoubleBattle(void) {return doubles;}
bool8 levelCappedNuzlocke(u8 level) {return level >= cap;}
void CompleteOnInactiveTextPrinter(void) {}
void DestroyExpTaskAndCompleteOnInactiveTextPrinter(u8 task) {(void)task;}
void Task_LaunchLvlUpAnim(u8 task) {(void)task;}
void DestroyTask(u8 task) {(void)task;}
void BtlController_EmitTwoReturnValues(int buffer, int result, int remaining) {
    assert(buffer == 1 && result == RET_VALUE_LEVELED_UP);
    levelMessages++; remainingExp = remaining;
}
void UpdateHealthboxAttribute(int box, struct Pokemon *mon, int attribute) {
    (void)mon; assert(attribute == HEALTHBOX_ALL); updatedBox = box;
}
void CalculateMonStats(struct Pokemon *mon) {
    int level = 1;
    while (level < MAX_LEVEL && mon->fields[MON_DATA_EXP] >= gExperienceTables[0][level + 1]) level++;
    mon->fields[MON_DATA_LEVEL] = level;
}
''' + function("src/battle_controller_player.c", "Task_GiveExpToMon") + r'''
void award(int slot, int level, u32 exp) {
    gPlayerParty[slot].fields[MON_DATA_SPECIES] = SPECIES_CATERPIE;
    gPlayerParty[slot].fields[MON_DATA_LEVEL] = level;
    gPlayerParty[slot].fields[MON_DATA_EXP] = gExperienceTables[0][level];
    gTasks[0].tExpTask_monId = slot;
    gTasks[0].tExpTask_gainedExp = exp;
    gTasks[0].tExpTask_battler = 0;
    levelMessages = 0;
    Task_GiveExpToMon(0);
}
int main(void) {
    int i;
    for (i = 0; i <= MAX_LEVEL; i++) gExperienceTables[0][i] = i * i * i;
    for (i = 0; i < PARTY_SIZE; i++) {
        award(i, 5, 8000 - 125);
        assert(gPlayerParty[i].fields[MON_DATA_LEVEL] == 20);
        assert(gPlayerParty[i].fields[MON_DATA_EXP] == 8000);
        assert(levelMessages == 1 && remainingExp == 0);
    }
    cap = 10;
    award(0, 5, 8000 - 125);
    assert(gPlayerParty[0].fields[MON_DATA_LEVEL] == 10);
    assert(gPlayerParty[0].fields[MON_DATA_EXP] == 1000);
    cap = MAX_LEVEL;
    award(0, 99, 65535);
    assert(gPlayerParty[0].fields[MON_DATA_LEVEL] == 100);
    assert(gPlayerParty[0].fields[MON_DATA_EXP] == 1000000);
    assert(levelMessages == 1);
    award(0, 5, 1);
    assert(gPlayerParty[0].fields[MON_DATA_LEVEL] == 5 && levelMessages == 0);
    assert(gPlayerParty[0].fields[MON_DATA_EXP] == 126);
    doubles = 1; gBattlerPartyIndexes[2] = 2;
    award(2, 5, 8000 - 125);
    assert(gTasks[0].func == Task_LaunchLvlUpAnim);
    puts("Full EXP awards: final level, party slots, doubles and caps passed");
}
'''
        self.compile_and_run(code)

    def test_crossed_level_moves_and_evolution(self):
        code = COMMON + r'''
#include "src/data/pokemon/level_up_learnsets.h"
#include "src/data/pokemon/level_up_learnset_pointers.h"
struct Evolution {u16 method, param, targetSpecies;};
#include "src/data/pokemon/evolution.h"
u8 sLearningMoveTableID, sLearningMoveLevel;
u16 gMoveToLearn;
struct {struct {u8 holdEffect;} enigmaBerry;} save, *gSaveBlock1Ptr = &save;
struct {u8 mapType;} gMapHeader;
u8 ItemId_GetHoldEffect(u16 item) {return item == ITEM_EVERSTONE ? HOLD_EFFECT_PREVENT_EVOLVE : 0;}
u16 GiveMoveToMon(struct Pokemon *mon, u16 move) {
    int i;
    for (i = 0; i < 4; i++) if (mon->moves[i] == move) return MON_ALREADY_KNOWS_MOVE;
    for (i = 0; i < 4; i++) if (!mon->moves[i]) {mon->moves[i] = move; return move;}
    return MON_HAS_MAX_MOVES;
}
u16 MonTryLearningNewMoveInRange(struct Pokemon *, bool8, u8);
''' + array("src/pokemon.c", "sDeoxysLevelUpLearnsets")
        code += function("src/pokemon.c", "MonTryLearningNewMove")
        code += function("src/pokemon.c", "MonTryLearningNewMoveInRange")
        code += function("src/pokemon.c", "GetEvolutionTargetSpecies")
        code += r'''
u8 gLeveledUpInBattle, gBattleInitialMonLevels[PARTY_SIZE];
const u8 gBitTable[] = {1,2,4,8,16,32};
void (*gBattleMainFunc)(void);
int evolutionScenes, rangeStart;
void WaitForEvoSceneToFinish(void) {}
void ReturnFromBattleToOverworld(void) {}
void SetEvolutionMoveLearningRange(u8 level) {rangeStart = level;}
void EvolutionScene(struct Pokemon *mon, u16 species, u8 flags, u8 slot) {
    (void)flags; (void)slot; evolutionScenes++; mon->fields[MON_DATA_SPECIES] = species;
}
''' + function("src/battle_main.c", "TryEvolvePokemon")
        code += r'''
int main(void) {
    struct Pokemon mon = {0};
    u16 result;
    mon.fields[MON_DATA_SPECIES] = SPECIES_BULBASAUR;
    mon.fields[MON_DATA_LEVEL] = 20;
    assert(MonTryLearningNewMoveInRange(&mon, TRUE, 5) == MOVE_LEECH_SEED);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MOVE_VINE_WHIP);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MOVE_ACID);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MOVE_POISON_POWDER);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MON_HAS_MAX_MOVES);
    assert(gMoveToLearn == MOVE_SLEEP_POWDER);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MON_HAS_MAX_MOVES);
    assert(gMoveToLearn == MOVE_RAZOR_LEAF);
    // Declining a replacement advances the iterator instead of asking again.
    result = MonTryLearningNewMoveInRange(&mon, FALSE, 5);
    assert(result == MOVE_NONE);
    assert(MonTryLearningNewMoveInRange(&mon, TRUE, 5) == MON_ALREADY_KNOWS_MOVE);
    memset(&mon, 0, sizeof(mon));
    mon.fields[MON_DATA_SPECIES] = SPECIES_CATERPIE;
    mon.fields[MON_DATA_LEVEL] = 9;
    assert(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) == SPECIES_METAPOD);
    mon.fields[MON_DATA_SPECIES] = SPECIES_METAPOD;
    assert(MonTryLearningNewMoveInRange(&mon, TRUE, 5) == MOVE_HARDEN);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 5) == MOVE_NONE);
    // An exact-level caller still only sees the current level's moves.
    assert(MonTryLearningNewMove(&mon, TRUE) == MOVE_NONE);
    mon.fields[MON_DATA_LEVEL] = 12;
    mon.fields[MON_DATA_SPECIES] = SPECIES_CATERPIE;
    assert(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) == SPECIES_METAPOD);
    mon.fields[MON_DATA_SPECIES] = SPECIES_METAPOD;
    mon.fields[MON_DATA_LEVEL] = 13;
    assert(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE) == SPECIES_BUTTERFREE);
    memset(&mon, 0, sizeof(mon));
    mon.fields[MON_DATA_SPECIES] = SPECIES_DEOXYS;
    mon.fields[MON_DATA_LEVEL] = 10;
    assert(MonTryLearningNewMoveInRange(&mon, TRUE, 4) == MOVE_NIGHT_SHADE);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 4) == MOVE_TELEPORT);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 4) == MOVE_NONE);
    // Hitmonlee's source table lists Lv. 42 before Lv. 41; offers must remain chronological.
    memset(&mon, 0, sizeof(mon));
    mon.fields[MON_DATA_SPECIES] = SPECIES_HITMONLEE;
    mon.fields[MON_DATA_LEVEL] = 42;
    assert(MonTryLearningNewMoveInRange(&mon, TRUE, 40) == MOVE_ENDURE);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 40) == MOVE_HI_JUMP_KICK);
    assert(MonTryLearningNewMoveInRange(&mon, FALSE, 40) == MOVE_NONE);
    gPlayerParty[0].fields[MON_DATA_SPECIES] = SPECIES_CATERPIE;
    gPlayerParty[0].fields[MON_DATA_LEVEL] = 12;
    gBattleInitialMonLevels[0] = 5; gLeveledUpInBattle = 1;
    TryEvolvePokemon();
    assert(evolutionScenes == 1 && rangeStart == 5 && gLeveledUpInBattle == 0);
    assert(gPlayerParty[0].fields[MON_DATA_SPECIES] == SPECIES_METAPOD);
    TryEvolvePokemon();
    assert(evolutionScenes == 1); // Returning from the scene must not evolve again.
    gPlayerParty[0].fields[MON_DATA_LEVEL] = 13;
    gBattleInitialMonLevels[0] = 12; gLeveledUpInBattle = 1;
    TryEvolvePokemon();
    assert(evolutionScenes == 2 && rangeStart == 12);
    assert(gPlayerParty[0].fields[MON_DATA_SPECIES] == SPECIES_BUTTERFREE);
    puts("Crossed-level moves, Harden, one evolution per event and Deoxys passed");
}
'''
        self.compile_and_run(code)

    def test_grouped_party_flow(self):
        code = COMMON + r'''
#include "constants/battle.h"
#include "constants/battle_string_ids.h"
#include "constants/abilities.h"
#include "constants/songs.h"
#define BUFFER_A 0
#define CONTROLLER_TWORETURNVALUES 1
#define RET_VALUE_LEVELED_UP 11
#define PREPARE_MON_NICK_WITH_PREFIX_BUFFER(...) ((void)0)
#define PREPARE_BYTE_NUMBER_BUFFER(...) ((void)0)
struct {u16 expYield;} gSpeciesInfo[NUM_SPECIES];
struct {u16 species, item, ability, hp, maxHP, attack, defense, speed, spAttack, spDefense; u8 level;} gBattleMons[4];
struct {struct {u8 holdEffect;} enigmaBerry;} save, *gSaveBlock1Ptr = &save;
struct {u16 expValue; u8 givenExpMons, expGetterMonId, expGetterBattlerId, wildVictorySong;} battle, *gBattleStruct = &battle;
struct {u8 getexpState;} gBattleScripting;
struct {u16 stats[6];} stats;
struct {void *dummy; void *dummy2; struct {u16 stats[6];} *beforeLvlUp;} resources, *gBattleResources = &resources;
u8 gBattlerFainted, gActiveBattler, gLeveledUpInBattle, sExpGetterStartLevel;
u8 gBattlerPartyIndexes[4], gAbsentBattlerFlags;
u32 gBattleTypeFlags, gBattleControllerExecFlags;
u8 gBattleBufferB[4][4];
const u8 gBitTable[] = {1,2,4,8,16,32};
const u8 expScript[16] = {0,0}, BattleScript_LevelUp[1] = {1};
const u8 *gBattlescriptCurrInstr = expScript;
s32 gBattleMoveDamage;
int partyMessages, summaries[6], gained[6], evs[6], friendship[6], cap = 100;
u8 GetBattlerForBattleScript(u8 battler) {(void)battler; return 1;}
u8 GetBattlerSide(u8 battler) {return battler & 1;}
u8 GetBattlerAtPosition(u8 position) {return position;}
bool8 levelCappedNuzlocke(u8 level) {return level >= cap;}
u8 ItemId_GetHoldEffect(u16 item) {return item == ITEM_LUCKY_EGG ? HOLD_EFFECT_LUCKY_EGG : 0;}
bool8 IsTradedMon(struct Pokemon *mon) {return mon->fields[MON_DATA_OT_ID] != 0;}
void BattleStopLowHpSound(void) {}
void PlayBGM(u16 song) {(void)song;}
void PrepareStringBattle(u16 string, u8 battler) {
    assert(string == STRINGID_PARTYGAINEDEXP && battler == 0); partyMessages++;
}
void MonGainEVs(struct Pokemon *mon, u16 species) {(void)species; evs[mon-gPlayerParty]++;}
void BtlController_EmitExpUpdate(u8 buffer, u8 slot, u16 exp) {
    (void)buffer; gained[slot] = exp;
    // Model the controller's one final-level response; its calculation is tested separately.
    gPlayerParty[slot].fields[MON_DATA_LEVEL] = 20;
    gBattleBufferB[gActiveBattler][0] = CONTROLLER_TWORETURNVALUES;
    gBattleBufferB[gActiveBattler][1] = RET_VALUE_LEVELED_UP;
}
void MarkBattlerForControllerExec(u8 battler) {(void)battler;}
void HandleLowHpMusicChange(struct Pokemon *mon, u8 battler) {(void)mon; (void)battler;}
void BattleScriptPushCursor(void) {}
void AdjustFriendship(struct Pokemon *mon, int event) {
    assert(event == FRIENDSHIP_EVENT_GROW_LEVEL); friendship[mon-gPlayerParty]++;
}
''' + function("src/battle_script_commands.c", "Cmd_getexp") + r'''
void run_award(void) {
    int iterations = 0;
    gBattleScripting.getexpState = 0; gBattlescriptCurrInstr = expScript;
    while (gBattlescriptCurrInstr != expScript + 2) {
        assert(++iterations < 100);
        Cmd_getexp();
        if (gBattlescriptCurrInstr == BattleScript_LevelUp) {
            summaries[gBattleStruct->expGetterMonId]++;
            gBattlescriptCurrInstr = expScript;
        }
    }
}
int main(void) {
    int i;
    // beforeLvlUp only stores u16 stats; provide the same layout without engine allocation.
    resources.beforeLvlUp = (void *)&stats;
    gBattleMons[1].species = SPECIES_CHANSEY; gBattleMons[1].level = 10;
    gSpeciesInfo[SPECIES_CHANSEY].expYield = 70; // full base award = 100
    gBattlerPartyIndexes[1] = 0;
    for (i = 0; i < 6; i++) {
        gPlayerParty[i].fields[MON_DATA_SPECIES] = SPECIES_BULBASAUR;
        gPlayerParty[i].fields[MON_DATA_LEVEL] = 5;
        gPlayerParty[i].fields[MON_DATA_HP] = 20;
    }
    gPlayerParty[1].fields[MON_DATA_HELD_ITEM] = ITEM_LUCKY_EGG;
    gPlayerParty[2].fields[MON_DATA_OT_ID] = 1;
    gPlayerParty[3].fields[MON_DATA_HP] = 0;
    gPlayerParty[4].fields[MON_DATA_IS_EGG] = TRUE;
    gPlayerParty[5].fields[MON_DATA_SPECIES] = SPECIES_NONE;
    run_award();
    assert(partyMessages == 1);
    assert(gained[0] == 100 && gained[1] == 150 && gained[2] == 150);
    for (i = 0; i < 3; i++) assert(summaries[i] == 1 && friendship[i] == 15 && evs[i] == 1);
    for (i = 3; i < 6; i++) assert(summaries[i] == 0 && gained[i] == 0 && evs[i] == 0);
    assert(gLeveledUpInBattle == 7);
    // Capped mons still receive EVs without a misleading EXP message or a level summary.
    cap = 20; partyMessages = 0;
    run_award(); assert(partyMessages == 0);
    for (i = 0; i < 3; i++) assert(summaries[i] == 1 && evs[i] == 2);
    puts("Party EXP flow: one message, one summary per mon, bonuses, exclusions and EVs passed");
}
'''
        self.compile_and_run(code)

    def test_level_100_rare_candy(self):
        code = COMMON + r'''
#include "constants/flags.h"
#define QL_EVENT_USED_ITEM 1
struct Evolution {u16 method, param, targetSpecies;};
#include "src/data/pokemon/evolution.h"
struct {struct {u8 holdEffect;} enigmaBerry;} save, *gSaveBlock1Ptr = &save;
struct {u8 mapType;} gMapHeader;
u8 ItemId_GetHoldEffect(u16 item) {return item == ITEM_EVERSTONE ? HOLD_EFFECT_PREVENT_EVOLVE : 0;}
''' + function("src/pokemon.c", "GetEvolutionTargetSpecies") + r'''
typedef void (*TaskFunc)(u8);
struct {TaskFunc func;} gTasks[1];
struct {u8 slotId;} gPartyMenu;
u16 gSpecialVar_ItemId = ITEM_RARE_CANDY;
u8 sRareCandyStartLevel;
bool8 gPartyMenuUseExitCallback;
int candyCount, evolutions, noEffectMessages, ordinaryCandyUses, hardcoreAllowed = TRUE, nuzlocke;
int cap = MAX_LEVEL;
const u8 gText_WontHaveEffectHardcore[] = "hardcore", gText_WontHaveEffect[] = "no effect";
bool8 FlagGet(int flag) {return flag == FLAG_NUZLOCKE && nuzlocke;}
bool8 CanUseRareCandyHardcore(void) {return hardcoreAllowed;}
bool8 levelCappedNuzlocke(u8 level) {return level >= cap;}
bool8 PokemonItemUseNoEffect(struct Pokemon *mon, u16 item, u8 slot, u8 move) {
    (void)mon; (void)item; (void)slot; (void)move; return FALSE;
}
void ItemUse_SetQuestLogEvent(int event, struct Pokemon *mon, u16 item, u16 move) {
    (void)event; (void)mon; (void)item; (void)move;
}
void RemoveBagItem(u16 item, int count) {assert(item == ITEM_RARE_CANDY); candyCount -= count;}
void PartyMenuTryEvolution(u8 task) {
    u16 target = GetEvolutionTargetSpecies(&gPlayerParty[0], EVO_MODE_NORMAL, ITEM_NONE);
    (void)task; assert(target != SPECIES_NONE); evolutions++;
    gPlayerParty[0].fields[MON_DATA_SPECIES] = target;
}
void DisplayPartyMenuMessage(const u8 *text, int wait) {(void)text; (void)wait; noEffectMessages++;}
void ScheduleBgCopyTilemapToVram(int bg) {(void)bg;}
void ItemUseCB_RareCandyStep(u8 task, TaskFunc func) {(void)task; (void)func; ordinaryCandyUses++;}
''' + function("src/party_menu.c", "ItemUseCB_RareCandy") + r'''
void setup(u16 species) {
    memset(gPlayerParty, 0, sizeof(gPlayerParty));
    gPlayerParty[0].fields[MON_DATA_SPECIES] = species;
    gPlayerParty[0].fields[MON_DATA_LEVEL] = 100;
    candyCount = 5; evolutions = noEffectMessages = ordinaryCandyUses = 0;
}
int main(void) {
    setup(SPECIES_MAGIKARP);
    ItemUseCB_RareCandy(0, NULL);
    assert(candyCount == 4 && evolutions == 1 && noEffectMessages == 0);
    assert(gPlayerParty[0].fields[MON_DATA_LEVEL] == 100);
    assert(gPlayerParty[0].fields[MON_DATA_SPECIES] == SPECIES_GYARADOS);
    setup(SPECIES_GYARADOS); ItemUseCB_RareCandy(0, NULL);
    assert(candyCount == 5 && evolutions == 0 && noEffectMessages == 1);
    setup(SPECIES_PIKACHU); ItemUseCB_RareCandy(0, NULL);
    assert(candyCount == 5 && evolutions == 0); // Stone evolution isn't bypassed.
    setup(SPECIES_MAGIKARP); gPlayerParty[0].fields[MON_DATA_HELD_ITEM] = ITEM_EVERSTONE;
    ItemUseCB_RareCandy(0, NULL); assert(candyCount == 5 && evolutions == 0);
    setup(SPECIES_CATERPIE); ItemUseCB_RareCandy(0, NULL);
    assert(candyCount == 4 && evolutions == 1);
    assert(gPlayerParty[0].fields[MON_DATA_SPECIES] == SPECIES_METAPOD);
    setup(SPECIES_MAGIKARP); hardcoreAllowed = FALSE;
    ItemUseCB_RareCandy(0, NULL); assert(candyCount == 5 && evolutions == 0);
    hardcoreAllowed = TRUE; nuzlocke = TRUE; gPlayerParty[0].fields[MON_DATA_DEAD] = TRUE;
    ItemUseCB_RareCandy(0, NULL); assert(candyCount == 5 && evolutions == 0);
    nuzlocke = FALSE;
    setup(SPECIES_MAGIKARP); gPlayerParty[0].fields[MON_DATA_LEVEL] = 99;
    ItemUseCB_RareCandy(0, NULL); assert(ordinaryCandyUses == 1 && evolutions == 0);
    setup(SPECIES_MAGIKARP); gPlayerParty[0].fields[MON_DATA_IS_EGG] = TRUE;
    ItemUseCB_RareCandy(0, NULL); assert(candyCount == 5 && evolutions == 0);
    puts("Lv. 100 Rare Candy: evolution, consumption, one stage and restrictions passed");
}
'''
        self.compile_and_run(code)


if __name__ == "__main__":
    unittest.main()

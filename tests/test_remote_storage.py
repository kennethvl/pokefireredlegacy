"""Host checks for pause-menu storage availability and safe storage return paths.

Run with: python3 tests/test_remote_storage.py
Uses the production menu functions; ROM UI rendering still needs emulator QA.
"""
import json
import unittest

import test_exp_progression as progression

ROOT = progression.ROOT
function = progression.function


class RemoteStorageTests(unittest.TestCase):
    def compile_and_run(self, code):
        progression.ProgressionTests.compile_and_run(self, code)

    def test_availability_and_menu_size(self):
        source = (ROOT / "src/start_menu.c").read_text()
        start = source.index("enum StartMenuOption")
        menu_enum = source[start:source.index("};", start) + 2]
        groups = json.loads((ROOT / "data/maps/map_groups.json").read_text())
        needed = {"PokemonLeague_LoreleisRoom", "PokemonLeague_BrunosRoom",
                  "PokemonLeague_AgathasRoom", "PokemonLeague_LancesRoom",
                  "PokemonLeague_ChampionsRoom", "PokemonLeague_HallOfFame",
                  "IndigoPlateau_PokemonCenter_1F", "PalletTown"}
        maps = []
        for group_id, group in enumerate(groups["group_order"]):
            for map_id, name in enumerate(groups[group]):
                if name in needed:
                    data = json.loads((ROOT / f"data/maps/{name}/map.json").read_text())
                    maps.append(f'#define {data["id"]} {map_id | (group_id << 8)}\n')
        code = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "constants/flags.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef int bool8;
#define TRUE 1
#define FALSE 0
#define FONT_SMALL 0
#define FONT_NORMAL 2
''' + menu_enum + "\n" + "".join(maps) + r'''
struct {struct {u8 mapGroup, mapNum;} location;} save, *gSaveBlock1Ptr = &save;
u8 sNumStartMenuItems, sStartMenuCursorPos, sStartMenuOrder[MAX_STARTMENU_ITEMS];
int hasPokemon = TRUE, hasPokedex = TRUE, inLink, inUnion, inSafari;
bool8 FlagGet(int flag) {return flag == FLAG_SYS_POKEMON_GET ? hasPokemon : hasPokedex;}
bool8 IsUpdateLinkStateCBActive(void) {return inLink;}
bool8 InUnionRoom(void) {return inUnion;}
bool8 GetSafariZoneFlag(void) {return inSafari;}
void AppendToList(u8 *order, u8 *count, u8 entry) {assert(*count < MAX_STARTMENU_ITEMS); order[(*count)++] = entry;}
'''
        for name in ["AppendToStartMenuItems", "CanAccessPokemonStorage", "SetUpStartMenu_NormalField",
                     "SetUpStartMenu_SafariZone", "SetUpStartMenu_Link", "SetUpStartMenu_UnionRoom",
                     "SetUpStartMenu", "GetStartMenuFont", "GetStartMenuRowHeight"]:
            code += function("src/start_menu.c", name)
        code += r'''
void set_map(u16 map) {save.location.mapGroup = map >> 8; save.location.mapNum = map & 255;}
int has_storage(void) {
    int i;
    for (i = 0; i < sNumStartMenuItems; i++) if (sStartMenuOrder[i] == STARTMENU_STORAGE) return TRUE;
    return FALSE;
}
int main(void) {
    unsigned i;
    const u16 blocked[] = {MAP_POKEMON_LEAGUE_LORELEIS_ROOM, MAP_POKEMON_LEAGUE_BRUNOS_ROOM,
        MAP_POKEMON_LEAGUE_AGATHAS_ROOM, MAP_POKEMON_LEAGUE_LANCES_ROOM, MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM};
    const u16 allowed[] = {MAP_PALLET_TOWN, MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F, MAP_POKEMON_LEAGUE_HALL_OF_FAME};
    for (i = 0; i < sizeof(allowed)/sizeof(allowed[0]); i++) {
        set_map(allowed[i]); SetUpStartMenu();
        assert(has_storage() && sNumStartMenuItems == 8);
        assert(sStartMenuOrder[2] == STARTMENU_STORAGE);
        assert(GetStartMenuFont() == FONT_SMALL && GetStartMenuRowHeight() == 13);
        assert((sNumStartMenuItems - 1) * GetStartMenuRowHeight() + 13 <= 104);
    }
    for (i = 0; i < sizeof(blocked)/sizeof(blocked[0]); i++) {
        sStartMenuCursorPos = 7; set_map(blocked[i]); SetUpStartMenu();
        assert(!has_storage() && sNumStartMenuItems == 7);
        assert(sStartMenuCursorPos < sNumStartMenuItems);
        assert(GetStartMenuFont() == FONT_NORMAL && GetStartMenuRowHeight() == 15);
    }
    set_map(MAP_PALLET_TOWN); inSafari = TRUE; SetUpStartMenu();
    assert(has_storage() && sNumStartMenuItems == 8 && sStartMenuOrder[0] == STARTMENU_RETIRE);
    inLink = TRUE; SetUpStartMenu(); assert(!has_storage());
    inLink = FALSE; inUnion = TRUE; SetUpStartMenu(); assert(!has_storage());
    inUnion = inSafari = FALSE; hasPokemon = hasPokedex = FALSE;
    SetUpStartMenu(); assert(!has_storage());
    puts("Storage availability: five League rooms blocked; field/Safari and menu bounds passed");
}
'''
        self.compile_and_run(code)

    def test_storage_entry_and_exit_callbacks(self):
        code = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
typedef uint8_t u8;
typedef int bool8;
#define TRUE 1
#define FALSE 0
#define OPTION_MOVE_MONS 2
#define STATE_LOAD 0
#define tState data[0]
#define tSelectedOption data[1]
struct {int data[16];} gTasks[1];
bool8 sStorageOpenedFromStartMenu;
u8 sPreviousBoxOption;
void (*gFieldCallback)(void), (*mainCallback)(void);
int enteredOption = -1, getterCalls, locks;
void Task_PCMainMenu(u8 task) {(void)task;}
u8 CreateTask(void (*callback)(u8), u8 priority) {(void)callback; assert(priority == 80); return 0;}
void LockPlayerFieldControls(void) {locks++;}
void FieldTask_ReturnToPcMenu(void) {}
void CB2_ReturnToField(void) {}
void CB2_ReturnToFieldWithOpenMenu(void) {}
void EnterPokeStorage(u8 option) {enteredOption = option;}
u8 GetCurrentBoxOption(void) {getterCalls++; return OPTION_MOVE_MONS;}
void SetMainCallback2(void (*callback)(void)) {mainCallback = callback;}
'''
        for name in ["CB2_OpenPokemonStorageFromStartMenu", "CB2_ExitPokeStorage", "ShowPokemonStorageSystemPC"]:
            code += function("src/pokemon_storage_system_menu.c", name)
        code += r'''
int main(void) {
    CB2_OpenPokemonStorageFromStartMenu();
    assert(sStorageOpenedFromStartMenu && enteredOption == OPTION_MOVE_MONS);
    CB2_ExitPokeStorage();
    assert(!sStorageOpenedFromStartMenu && mainCallback == CB2_ReturnToFieldWithOpenMenu);
    assert(getterCalls == 0 && gFieldCallback == NULL); // Also safe if storage allocation failed.
    CB2_OpenPokemonStorageFromStartMenu();
    ShowPokemonStorageSystemPC();
    assert(!sStorageOpenedFromStartMenu && locks == 1);
    CB2_ExitPokeStorage();
    assert(mainCallback == CB2_ReturnToField && gFieldCallback == FieldTask_ReturnToPcMenu);
    assert(sPreviousBoxOption == OPTION_MOVE_MONS && getterCalls == 1);
    puts("Storage entry/exit: pause returns to pause; regular PCs keep their original return path");
}
'''
        self.compile_and_run(code)

    def test_pause_callback_waits_for_fade_and_cleans_up(self):
        code = r'''
#include <assert.h>
#include <stdio.h>
typedef int bool8;
#define TRUE 1
#define FALSE 0
struct {bool8 active;} gPaletteFade;
int sounds, safariCleanup, windowCleanup;
void (*mainCallback)(void);
void PlayRainStoppingSoundEffect(void) {sounds++;}
void DestroySafariZoneStatsWindow(void) {safariCleanup++;}
void CleanupOverworldWindowsAndTilemaps(void) {windowCleanup++;}
void CB2_OpenPokemonStorageFromStartMenu(void) {}
void SetMainCallback2(void (*callback)(void)) {mainCallback = callback;}
''' + function("src/start_menu.c", "StartMenuStorageCallback") + r'''
int main(void) {
    gPaletteFade.active = TRUE;
    assert(!StartMenuStorageCallback() && windowCleanup == 0 && mainCallback == NULL);
    gPaletteFade.active = FALSE;
    assert(StartMenuStorageCallback());
    assert(sounds == 1 && safariCleanup == 1 && windowCleanup == 1);
    assert(mainCallback == CB2_OpenPokemonStorageFromStartMenu);
    puts("Pause storage launch waits for fade and cleans up the overworld UI");
}
'''
        self.compile_and_run(code)


if __name__ == "__main__":
    unittest.main()

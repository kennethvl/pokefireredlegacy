#include "global.h"
#include "gflib.h"
#include "scanline_effect.h"
#include "overworld.h"
#include "link.h"
#include "pokedex.h"
#include "item_menu.h"
#include "party_menu.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "link_rfu.h"
#include "help_message.h"
#include "event_data.h"
#include "fieldmap.h"
#include "safari_zone.h"
#include "start_menu.h"
#include "menu.h"
#include "load_save.h"
#include "strings.h"
#include "menu_helpers.h"
#include "text_window.h"
#include "field_fadetransition.h"
#include "field_player_avatar.h"
#include "new_menu_helpers.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "script.h"
#include "quest_log.h"
#include "new_game.h"
#include "event_scripts.h"
#include "field_weather.h"
#include "field_specials.h"
#include "pokedex_screen.h"
#include "trainer_card.h"
#include "option_menu.h"
#include "save_menu_util.h"
#include "help_system.h"
#include "list_menu.h"
#include "menu_indicators.h"
#include "constants/songs.h"
#include "constants/maps.h"
#include "constants/field_weather.h"

enum StartMenuOption
{
    STARTMENU_POKEDEX = 0,
    STARTMENU_POKEMON,
    STARTMENU_BAG,
    STARTMENU_PLAYER,
    STARTMENU_SAVE,
    STARTMENU_OPTION,
    STARTMENU_EXIT,
    STARTMENU_RETIRE,
    STARTMENU_PLAYER2,
    STARTMENU_STORAGE,
    MAX_STARTMENU_ITEMS
};

enum SaveCBReturn
{
    SAVECB_RETURN_CONTINUE = 0,
    SAVECB_RETURN_OKAY,
    SAVECB_RETURN_CANCEL,
    SAVECB_RETURN_ERROR
};

static EWRAM_DATA bool8 (*sStartMenuCallback)(void) = NULL;
static EWRAM_DATA u8 sStartMenuCursorPos = 0; // absolute index into sStartMenuOrder
static EWRAM_DATA u16 sStartMenuScrollOffset = 0; // first entry shown when the menu scrolls (u16: read by the scroll arrows)
static EWRAM_DATA u8 sStartMenuArrowsTaskIdPlus1 = 0; // scroll arrows task id + 1, or 0 if there are none
static EWRAM_DATA bool8 sStorageMoveItems = FALSE; // SELECT on STORAGE opens it in Move Items mode
static EWRAM_DATA u8 sNumStartMenuItems = 0;
static EWRAM_DATA u8 sStartMenuOrder[MAX_STARTMENU_ITEMS] = {};
static EWRAM_DATA s8 sDrawStartMenuState[2] = {};
static EWRAM_DATA u8 sSafariZoneStatsWindowId = 0;
static ALIGNED(4) EWRAM_DATA u8 sSaveStatsWindowId = 0;

static u8 (*sSaveDialogCB)(void);
static u8 sSaveDialogDelay;
static bool8 sSaveDialogIsPrinting;

static void SetUpStartMenu_Link(void);
static void SetUpStartMenu_UnionRoom(void);
static void SetUpStartMenu_SafariZone(void);
static void SetUpStartMenu_NormalField(void);
static bool8 StartCB_HandleInput(void);
static void StartMenu_FadeScreenIfLeavingOverworld(void);
static bool8 StartMenuPokedexSanityCheck(void);
static bool8 StartMenuPokedexCallback(void);
static bool8 StartMenuPokemonCallback(void);
static bool8 StartMenuStorageCallback(void);
static bool8 CanAccessPokemonStorage(void);
static u8 GetStartMenuVisibleCount(void);
static void ClampStartMenuScroll(void);
static void RemoveStartMenuScrollArrows(void);
static bool8 StartMenuBagCallback(void);
static bool8 StartMenuPlayerCallback(void);
static bool8 StartMenuSaveCallback(void);
static bool8 StartMenuOptionCallback(void);
static bool8 StartMenuExitCallback(void);
static bool8 StartMenuSafariZoneRetireCallback(void);
static bool8 StartMenuLinkPlayerCallback(void);
static bool8 StartCB_Save1(void);
static bool8 StartCB_Save2(void);
static void StartMenu_PrepareForSave(void);
static u8 RunSaveDialogCB(void);
static void task50_save_game(u8 taskId);
static u8 SaveDialogCB_PrintAskSaveText(void);
static u8 SaveDialogCB_AskSavePrintYesNoMenu(void);
static u8 SaveDialogCB_AskSaveHandleInput(void);
static u8 SaveDialogCB_PrintAskOverwriteText(void);
static u8 SaveDialogCB_AskOverwritePrintYesNoMenu(void);
static u8 SaveDialogCB_AskReplacePreviousFilePrintYesNoMenu(void);
static u8 SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput(void);
static u8 SaveDialogCB_PrintSavingDontTurnOffPower(void);
static u8 SaveDialogCB_DoSave(void);
static u8 SaveDialogCB_PrintSaveResult(void);
static u8 SaveDialogCB_WaitPrintSuccessAndPlaySE(void);
static u8 SaveDialogCB_ReturnSuccess(void);
static u8 SaveDialogCB_WaitPrintErrorAndPlaySE(void);
static u8 SaveDialogCB_ReturnError(void);
static void CB2_WhileSavingAfterLinkBattle(void);
static void task50_after_link_battle_save(u8 taskId);
static void PrintSaveStats(void);
static void CloseSaveStatsWindow(void);
static void CloseStartMenu(void);

static const struct MenuAction sStartMenuActionTable[] = {
    { gText_MenuPokedex, {.u8_void = StartMenuPokedexCallback} },
    { gText_MenuPokemon, {.u8_void = StartMenuPokemonCallback} },
    { gText_MenuBag, {.u8_void = StartMenuBagCallback} },
    { gText_MenuPlayer, {.u8_void = StartMenuPlayerCallback} },
    { gText_MenuSave, {.u8_void = StartMenuSaveCallback} },
    { gText_MenuOption, {.u8_void = StartMenuOptionCallback} },
    { gText_MenuExit, {.u8_void = StartMenuExitCallback} },
    { gText_MenuRetire, {.u8_void = StartMenuSafariZoneRetireCallback} },
    { gText_MenuPlayer, {.u8_void = StartMenuLinkPlayerCallback} },
    { gText_MenuStorage, {.u8_void = StartMenuStorageCallback} }
};

static const struct WindowTemplate sSafariZoneStatsWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 10,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 0x008
};

static const u8 *const sStartMenuDescPointers[] = {
    gStartMenuDesc_Pokedex,
    gStartMenuDesc_Pokemon,
    gStartMenuDesc_Bag,
    gStartMenuDesc_Player,
    gStartMenuDesc_Save,
    gStartMenuDesc_Option,
    gStartMenuDesc_Exit,
    gStartMenuDesc_Retire,
    gStartMenuDesc_Player,
    gStartMenuDesc_Storage
};

static const struct BgTemplate sBGTemplates_AfterLinkSaveMessage[] = {
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }
};

static const struct WindowTemplate sWindowTemplates_AfterLinkSaveMessage[] = {
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x198
    }, DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sSaveStatsWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 14,
    .height = 9,
    .paletteNum = 13,
    .baseBlock = 0x008
};

static ALIGNED(2) const u8 sTextColor_StatName[] = { 1, 2, 3 };
static ALIGNED(2) const u8 sTextColor_StatValue[] = { 1, 4, 5 };
static ALIGNED(2) const u8 sTextColor_LocationHeader[] = { 1, 6, 7 };

// Unused
static void SetHasPokedexAndPokemon(void)
{
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_POKEMON_GET);
}

static void SetUpStartMenu(void)
{
    sNumStartMenuItems = 0;
    if (IsUpdateLinkStateCBActive() == TRUE)
        SetUpStartMenu_Link();
    else if (InUnionRoom() == TRUE)
        SetUpStartMenu_UnionRoom();
    else if (GetSafariZoneFlag() == TRUE)
        SetUpStartMenu_SafariZone();
    else
        SetUpStartMenu_NormalField();
    if (sStartMenuCursorPos >= sNumStartMenuItems)
        sStartMenuCursorPos = sNumStartMenuItems - 1;
    ClampStartMenuScroll();
}

static void AppendToStartMenuItems(u8 newEntry)
{
    AppendToList(sStartMenuOrder, &sNumStartMenuItems, newEntry);
}

static bool8 CanAccessPokemonStorage(void)
{
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;

    switch (map)
    {
    case MAP_POKEMON_LEAGUE_LORELEIS_ROOM:
    case MAP_POKEMON_LEAGUE_BRUNOS_ROOM:
    case MAP_POKEMON_LEAGUE_AGATHAS_ROOM:
    case MAP_POKEMON_LEAGUE_LANCES_ROOM:
    case MAP_POKEMON_LEAGUE_CHAMPIONS_ROOM:
        return FALSE;
    default:
        return TRUE;
    }
}

static void SetUpStartMenu_NormalField(void)
{
    if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
        AppendToStartMenuItems(STARTMENU_POKEDEX);
    if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE)
    {
        AppendToStartMenuItems(STARTMENU_POKEMON);
        if (CanAccessPokemonStorage())
            AppendToStartMenuItems(STARTMENU_STORAGE);
    }
    AppendToStartMenuItems(STARTMENU_BAG);
    AppendToStartMenuItems(STARTMENU_PLAYER);
    AppendToStartMenuItems(STARTMENU_SAVE);
    AppendToStartMenuItems(STARTMENU_OPTION);
    AppendToStartMenuItems(STARTMENU_EXIT);
}

static void SetUpStartMenu_SafariZone(void)
{
    AppendToStartMenuItems(STARTMENU_RETIRE);
    AppendToStartMenuItems(STARTMENU_POKEDEX);
    AppendToStartMenuItems(STARTMENU_POKEMON);
    if (CanAccessPokemonStorage())
        AppendToStartMenuItems(STARTMENU_STORAGE);
    AppendToStartMenuItems(STARTMENU_BAG);
    AppendToStartMenuItems(STARTMENU_PLAYER);
    AppendToStartMenuItems(STARTMENU_OPTION);
    AppendToStartMenuItems(STARTMENU_EXIT);
}

static void SetUpStartMenu_Link(void)
{
    AppendToStartMenuItems(STARTMENU_POKEMON);
    AppendToStartMenuItems(STARTMENU_BAG);
    AppendToStartMenuItems(STARTMENU_PLAYER2);
    AppendToStartMenuItems(STARTMENU_OPTION);
    AppendToStartMenuItems(STARTMENU_EXIT);
}

static void SetUpStartMenu_UnionRoom(void)
{
    AppendToStartMenuItems(STARTMENU_POKEMON);
    AppendToStartMenuItems(STARTMENU_BAG);
    AppendToStartMenuItems(STARTMENU_PLAYER);
    AppendToStartMenuItems(STARTMENU_OPTION);
    AppendToStartMenuItems(STARTMENU_EXIT);
}

static void DrawSafariZoneStatsWindow(void)
{
    sSafariZoneStatsWindowId = AddWindow(&sSafariZoneStatsWindowTemplate);
    PutWindowTilemap(sSafariZoneStatsWindowId);
    DrawStdWindowFrame(sSafariZoneStatsWindowId, FALSE);
    ConvertIntToDecimalStringN(gStringVar3, gNumSafariBalls, STR_CONV_MODE_RIGHT_ALIGN, 2);
    StringExpandPlaceholders(gStringVar4, gText_MenuSafariStats);
    AddTextPrinterParameterized(sSafariZoneStatsWindowId, FONT_NORMAL, gStringVar4, 4, 3, 0xFF, NULL);
    CopyWindowToVram(sSafariZoneStatsWindowId, COPYWIN_GFX);
}

static void DestroySafariZoneStatsWindow(void)
{
    if (GetSafariZoneFlag())
    {
        ClearStdWindowAndFrameToTransparent(sSafariZoneStatsWindowId, FALSE);
        CopyWindowToVram(sSafariZoneStatsWindowId, COPYWIN_GFX);
        RemoveWindow(sSafariZoneStatsWindowId);
    }
}

// The menu shows at most this many entries (its normal size without STORAGE); the rest scroll into view.
#define START_MENU_MAX_VISIBLE 7
#define START_MENU_ROW_HEIGHT  15

static u8 GetStartMenuVisibleCount(void)
{
    return sNumStartMenuItems < START_MENU_MAX_VISIBLE ? sNumStartMenuItems : START_MENU_MAX_VISIBLE;
}

// Keeps sStartMenuCursorPos valid and inside the visible part of the menu.
static void ClampStartMenuScroll(void)
{
    u8 visible = GetStartMenuVisibleCount();

    if (sStartMenuCursorPos >= sNumStartMenuItems)
        sStartMenuCursorPos = 0;
    if (sStartMenuCursorPos < sStartMenuScrollOffset)
        sStartMenuScrollOffset = sStartMenuCursorPos;
    else if (sStartMenuCursorPos >= sStartMenuScrollOffset + visible)
        sStartMenuScrollOffset = sStartMenuCursorPos - visible + 1;
    if (sStartMenuScrollOffset > sNumStartMenuItems - visible)
        sStartMenuScrollOffset = sNumStartMenuItems - visible;
}

#define GFXTAG_START_MENU_SCROLL_ARROWS 2000
#define PALTAG_START_MENU_SCROLL_ARROWS 100

// Up/down arrows beside the pause menu when it has more entries than fit (shown/hidden by the arrows task as it
// reads sStartMenuScrollOffset). Every way out of the menu removes them via RemoveStartMenuScrollArrows.
static void AddStartMenuScrollArrows(void)
{
    struct ScrollArrowsTemplate template =
    {
        .firstArrowType = SCROLL_ARROW_UP,
        .firstX = 204,
        .firstY = 6,
        .secondArrowType = SCROLL_ARROW_DOWN,
        .secondX = 204,
        .secondY = (START_MENU_MAX_VISIBLE * 2 + 1) * 8 + 2,
        .fullyUpThreshold = 0,
        .fullyDownThreshold = 0,
        .tileTag = GFXTAG_START_MENU_SCROLL_ARROWS,
        .palTag = PALTAG_START_MENU_SCROLL_ARROWS,
        .palNum = 0,
    };

    if (sStartMenuArrowsTaskIdPlus1 != 0 || sNumStartMenuItems <= START_MENU_MAX_VISIBLE)
        return;
    template.fullyDownThreshold = sNumStartMenuItems - START_MENU_MAX_VISIBLE;
    sStartMenuArrowsTaskIdPlus1 = AddScrollIndicatorArrowPair(&template, &sStartMenuScrollOffset) + 1;
}

static void RemoveStartMenuScrollArrows(void)
{
    if (sStartMenuArrowsTaskIdPlus1 == 0)
        return;
    RemoveScrollIndicatorArrowPair(sStartMenuArrowsTaskIdPlus1 - 1);
    sStartMenuArrowsTaskIdPlus1 = 0;
}

// *cursor_p is the row on screen; the entry printed there is row + sStartMenuScrollOffset.
static s8 PrintStartMenuItems(s8 *cursor_p, u8 nitems)
{
    s16 i = *cursor_p;
    do
    {
        u8 entry = sStartMenuOrder[i + sStartMenuScrollOffset];

        if (entry == STARTMENU_PLAYER || entry == STARTMENU_PLAYER2)
        {
            Menu_PrintFormatIntlPlayerName(GetStartMenuWindowId(), sStartMenuActionTable[entry].text, 8, i * START_MENU_ROW_HEIGHT);
        }
        else
        {
            StringExpandPlaceholders(gStringVar4, sStartMenuActionTable[entry].text);
            AddTextPrinterParameterized(GetStartMenuWindowId(), FONT_NORMAL, gStringVar4, 8, i * START_MENU_ROW_HEIGHT, 0xFF, NULL);
        }
        i++;
        if (i >= GetStartMenuVisibleCount())
        {
            *cursor_p = i;
            return TRUE;
        }
    } while (--nitems);
    *cursor_p = i;
    return FALSE;
}

static s8 DoDrawStartMenu(void)
{
    switch (sDrawStartMenuState[0])
    {
    case 0:
        sDrawStartMenuState[0]++;
        break;
    case 1:
        SetUpStartMenu();
        sDrawStartMenuState[0]++;
        break;
    case 2:
        LoadStdWindowFrameGfx();
        DrawStdWindowFrame(CreateStartMenuWindow(GetStartMenuVisibleCount()), FALSE);
        sDrawStartMenuState[0]++;
        break;
    case 3:
        if (GetSafariZoneFlag())
            DrawSafariZoneStatsWindow();
        sDrawStartMenuState[0]++;
        break;
    case 4:
        if (PrintStartMenuItems(&sDrawStartMenuState[1], 2) == TRUE)
            sDrawStartMenuState[0]++;
        break;
    case 5:
        Menu_InitCursor(GetStartMenuWindowId(), FONT_NORMAL, 0, 0, START_MENU_ROW_HEIGHT, GetStartMenuVisibleCount(), sStartMenuCursorPos - sStartMenuScrollOffset);
        AddStartMenuScrollArrows();
        if (!MenuHelpers_IsLinkActive() && InUnionRoom() != TRUE && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_HELP)
        {
            DrawHelpMessageWindowWithText(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]]);
        }
        CopyWindowToVram(GetStartMenuWindowId(), COPYWIN_MAP);
        return TRUE;
    }
    return FALSE;
}

static void DrawStartMenuInOneGo(void)
{
    sDrawStartMenuState[0] = 0;
    sDrawStartMenuState[1] = 0;
    while (!DoDrawStartMenu())
        ;
}

static void task50_startmenu(u8 taskId)
{
    if (DoDrawStartMenu() == TRUE)
        SwitchTaskToFollowupFunc(taskId);
}

static void OpenStartMenuWithFollowupFunc(TaskFunc func)
{
    u8 taskId;
    sDrawStartMenuState[0] = 0;
    sDrawStartMenuState[1] = 0;
    taskId = CreateTask(task50_startmenu, 80);
    SetTaskFuncWithFollowupFunc(taskId, task50_startmenu, func);
}

static bool8 FieldCB2_DrawStartMenu(void)
{
    if (!DoDrawStartMenu())
        return FALSE;
    FadeTransition_FadeInOnReturnToStartMenu();
    return TRUE;
}

void SetUpReturnToStartMenu(void)
{
    sDrawStartMenuState[0] = 0;
    sDrawStartMenuState[1] = 0;
    gFieldCallback2 = FieldCB2_DrawStartMenu;
}

void Task_StartMenuHandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (data[0])
    {
    case 0:
        if (InUnionRoom() == TRUE)
            SetUsingUnionRoomStartMenu();
        sStartMenuCallback = StartCB_HandleInput;
        data[0]++;
        break;
    case 1:
        if (sStartMenuCallback() == TRUE)
            DestroyTask(taskId);
        break;
    }
}

void ShowStartMenu(void)
{
    if (!IsUpdateLinkStateCBActive())
    {
        FreezeObjectEvents();
        HandleEnforcedLookDirectionOnPlayerStopMoving();
        StopPlayerAvatar();
    }
    OpenStartMenuWithFollowupFunc(Task_StartMenuHandleInput);
    LockPlayerFieldControls();
}

// Moves the cursor by delta (wrapping around). If the menu is longer than the window, the list scrolls
// so the cursor stays visible.
static void MoveStartMenuCursor(s8 delta)
{
    u8 visible = GetStartMenuVisibleCount();
    u16 oldOffset = sStartMenuScrollOffset;
    s8 row;

    if (sNumStartMenuItems <= visible)
    {
        sStartMenuCursorPos = Menu_MoveCursor(delta);
        return;
    }

    sStartMenuCursorPos = (sStartMenuCursorPos + sNumStartMenuItems + delta) % sNumStartMenuItems;
    ClampStartMenuScroll();
    if (sStartMenuScrollOffset == oldOffset)
    {
        Menu_MoveCursorNoWrapAround(delta);
        return;
    }

    FillWindowPixelBuffer(GetStartMenuWindowId(), PIXEL_FILL(1));
    row = 0;
    PrintStartMenuItems(&row, visible);
    Menu_InitCursor(GetStartMenuWindowId(), FONT_NORMAL, 0, 0, START_MENU_ROW_HEIGHT, visible, sStartMenuCursorPos - sStartMenuScrollOffset);
    CopyWindowToVram(GetStartMenuWindowId(), COPYWIN_GFX);
}

static bool8 StartCB_HandleInput(void)
{
    // A opens STORAGE in Move Pokémon mode, SELECT in Move Items mode.
    if (JOY_NEW(A_BUTTON | SELECT_BUTTON) && sStartMenuOrder[sStartMenuCursorPos] == STARTMENU_STORAGE)
    {
        PlaySE(SE_SELECT);
        sStorageMoveItems = JOY_NEW(SELECT_BUTTON) ? TRUE : FALSE;
        sStartMenuCallback = StartMenuStorageCallback;
        StartMenu_FadeScreenIfLeavingOverworld();
        return FALSE;
    }
    if (JOY_NEW(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        MoveStartMenuCursor(-1);
        if (!MenuHelpers_IsLinkActive() && InUnionRoom() != TRUE && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_HELP)
        {
            PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
        }
    }
    if (JOY_NEW(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        MoveStartMenuCursor(+1);
        if (!MenuHelpers_IsLinkActive() && InUnionRoom() != TRUE && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_HELP)
        {
            PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
        }
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (!StartMenuPokedexSanityCheck())
            return FALSE;
        sStartMenuCallback = sStartMenuActionTable[sStartMenuOrder[sStartMenuCursorPos]].func.u8_void;
        StartMenu_FadeScreenIfLeavingOverworld();
        return FALSE;
    }
    if (JOY_NEW(B_BUTTON | START_BUTTON))
    {
        DestroySafariZoneStatsWindow();
        DestroyHelpMessageWindow_();
        CloseStartMenu();
        return TRUE;
    }
    return FALSE;
}

static void StartMenu_FadeScreenIfLeavingOverworld(void)
{
    if (sStartMenuCallback != StartMenuSaveCallback
     && sStartMenuCallback != StartMenuExitCallback
     && sStartMenuCallback != StartMenuSafariZoneRetireCallback)
    {
        RemoveStartMenuScrollArrows();
        StopPokemonLeagueLightingEffectTask();
        FadeScreen(FADE_TO_BLACK, 0);
    }
}

static bool8 StartMenuPokedexSanityCheck(void)
{
    if (sStartMenuActionTable[sStartMenuOrder[sStartMenuCursorPos]].func.u8_void == StartMenuPokedexCallback && GetNationalPokedexCount(0) == 0)
        return FALSE;
    return TRUE;
}

static bool8 StartMenuPokedexCallback(void)
{
    if (!gPaletteFade.active)
    {
        IncrementGameStat(GAME_STAT_CHECKED_POKEDEX);
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_OpenPokedexFromStartMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuPokemonCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_PartyMenuFromStartMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuStorageCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(sStorageMoveItems ? CB2_OpenPokemonStorageItemsFromStartMenu : CB2_OpenPokemonStorageFromStartMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuBagCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_BagMenuFromStartMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuPlayerCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        ShowPlayerTrainerCard(CB2_ReturnToFieldWithOpenMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuSaveCallback(void)
{
    sStartMenuCallback = StartCB_Save1;
    return FALSE;
}

static bool8 StartMenuOptionCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        DestroySafariZoneStatsWindow();
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_OptionsMenuFromStartMenu);
        gMain.savedCallback = CB2_ReturnToFieldWithOpenMenu;
        return TRUE;
    }
    return FALSE;
}

static bool8 StartMenuExitCallback(void)
{
    DestroySafariZoneStatsWindow();
    DestroyHelpMessageWindow_();
    CloseStartMenu();
    return TRUE;
}

static bool8 StartMenuSafariZoneRetireCallback(void)
{
    DestroySafariZoneStatsWindow();
    DestroyHelpMessageWindow_();
    CloseStartMenu();
    SafariZoneRetirePrompt();
    return TRUE;
}


static bool8 StartMenuLinkPlayerCallback(void)
{
    if (!gPaletteFade.active)
    {
        PlayRainStoppingSoundEffect();
        CleanupOverworldWindowsAndTilemaps();
        ShowTrainerCardInLink(gLocalLinkPlayerId, CB2_ReturnToFieldWithOpenMenu);
        return TRUE;
    }
    return FALSE;
}

static bool8 StartCB_Save1(void)
{
    BackupHelpContext();
    SetHelpContext(HELPCONTEXT_SAVE);
    StartMenu_PrepareForSave();
    sStartMenuCallback = StartCB_Save2;
    return FALSE;
}

static bool8 StartCB_Save2(void)
{
    switch (RunSaveDialogCB())
    {
    case SAVECB_RETURN_CONTINUE:
        break;
    case SAVECB_RETURN_OKAY:
        ClearDialogWindowAndFrameToTransparent(0, TRUE);
        ClearPlayerHeldMovementAndUnfreezeObjectEvents();
        UnlockPlayerFieldControls();
        RestoreHelpContext();
        return TRUE;
    case SAVECB_RETURN_CANCEL:
        ClearDialogWindowAndFrameToTransparent(0, FALSE);
        DrawStartMenuInOneGo();
        RestoreHelpContext();
        sStartMenuCallback = StartCB_HandleInput;
        break;
    case SAVECB_RETURN_ERROR:
        ClearDialogWindowAndFrameToTransparent(0, TRUE);
        ClearPlayerHeldMovementAndUnfreezeObjectEvents();
        UnlockPlayerFieldControls();
        RestoreHelpContext();
        return TRUE;
    }
    return FALSE;
}

static void StartMenu_PrepareForSave(void)
{
    SaveMapView();
    sSaveDialogCB = SaveDialogCB_PrintAskSaveText;
    sSaveDialogIsPrinting = FALSE;
}

static u8 RunSaveDialogCB(void)
{
    if (RunTextPrinters_CheckPrinter0Active() == TRUE)
        return 0;
    sSaveDialogIsPrinting = FALSE;
    return sSaveDialogCB();
}

void Field_AskSaveTheGame(void)
{
    BackupHelpContext();
    SetHelpContext(HELPCONTEXT_SAVE);
    StartMenu_PrepareForSave();
    CreateTask(task50_save_game, 80);
}

static void PrintSaveTextWithFollowupFunc(const u8 *str, bool8 (*saveDialogCB)(void))
{
    StringExpandPlaceholders(gStringVar4, str);
    LoadMessageBoxAndFrameGfx(0, TRUE);
    AddTextPrinterForMessage(TRUE);
    sSaveDialogIsPrinting = TRUE;
    sSaveDialogCB = saveDialogCB;
}

static void task50_save_game(u8 taskId)
{
    switch (RunSaveDialogCB())
    {
    case 0:
        return;
    case 2:
    case 3:
        gSpecialVar_Result = FALSE;
        break;
    case 1:
        gSpecialVar_Result = TRUE;
        break;
    }
    DestroyTask(taskId);
    ScriptContext_Enable();
    RestoreHelpContext();
}

static void CloseSaveMessageWindow(void)
{
    ClearDialogWindowAndFrame(0, TRUE);
}

static void CloseSaveStatsWindow_(void)
{
    CloseSaveStatsWindow();
}

static void SetSaveDialogDelayTo60Frames(void)
{
    sSaveDialogDelay = 60;
}

static bool8 SaveDialog_Wait60FramesOrAButtonHeld(void)
{
    sSaveDialogDelay--;
    if (JOY_HELD(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        return TRUE;
    }
    else if (sSaveDialogDelay == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool8 SaveDialog_Wait60FramesThenCheckAButtonHeld(void)
{
    if (sSaveDialogDelay == 0)
    {
        if (JOY_HELD(A_BUTTON))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        sSaveDialogDelay--;
        return FALSE;
    }
}

static u8 SaveDialogCB_PrintAskSaveText(void)
{
    RemoveStartMenuScrollArrows();
    ClearStdWindowAndFrame(GetStartMenuWindowId(), FALSE);
    RemoveStartMenuWindow();
    DestroyHelpMessageWindow(0);
    PrintSaveStats();
    PrintSaveTextWithFollowupFunc(gText_WouldYouLikeToSaveTheGame, SaveDialogCB_AskSavePrintYesNoMenu);
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_AskSavePrintYesNoMenu(void)
{
    DisplayYesNoMenuDefaultYes();
    sSaveDialogCB = SaveDialogCB_AskSaveHandleInput;
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_AskSaveHandleInput(void)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        /*if ((gSaveFileStatus != SAVE_STATUS_EMPTY && gSaveFileStatus != SAVE_STATUS_INVALID) || !gDifferentSaveFile)
            sSaveDialogCB = SaveDialogCB_PrintAskOverwriteText;
        else*/
            sSaveDialogCB = SaveDialogCB_PrintSavingDontTurnOffPower;
        break;
    case 1:
    case -1:
        CloseSaveStatsWindow_();
        CloseSaveMessageWindow();
        return SAVECB_RETURN_CANCEL;
    }
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_PrintAskOverwriteText(void)
{
    if (gDifferentSaveFile == TRUE)
        PrintSaveTextWithFollowupFunc(gText_DifferentGameFile, SaveDialogCB_AskReplacePreviousFilePrintYesNoMenu);
    else
        PrintSaveTextWithFollowupFunc(gText_AlreadySaveFile_WouldLikeToOverwrite, SaveDialogCB_AskOverwritePrintYesNoMenu);
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_AskOverwritePrintYesNoMenu(void)
{
    DisplayYesNoMenuDefaultYes();
    sSaveDialogCB = SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput;
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_AskReplacePreviousFilePrintYesNoMenu(void)
{
    DisplayYesNoMenuDefaultNo();
    sSaveDialogCB = SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput;
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_AskOverwriteOrReplacePreviousFileHandleInput(void)
{
    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:
        sSaveDialogCB = SaveDialogCB_PrintSavingDontTurnOffPower;
        break;
    case 1:
    case -1:
        CloseSaveStatsWindow_();
        CloseSaveMessageWindow();
        return SAVECB_RETURN_CANCEL;
    }
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_PrintSavingDontTurnOffPower(void)
{
    SaveQuestLogData();
    PrintSaveTextWithFollowupFunc(gText_SavingDontTurnOffThePower, SaveDialogCB_DoSave);
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_DoSave(void)
{
    IncrementGameStat(GAME_STAT_SAVED_GAME);
    if (gDifferentSaveFile == TRUE)
    {
        TrySavingData(SAVE_OVERWRITE_DIFFERENT_FILE);
        gDifferentSaveFile = FALSE;
    }
    else
    {
        TrySavingData(SAVE_NORMAL);
    }
    sSaveDialogCB = SaveDialogCB_PrintSaveResult;
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_PrintSaveResult(void)
{
    if (gSaveAttemptStatus == SAVE_STATUS_OK)
        PrintSaveTextWithFollowupFunc(gText_PlayerSavedTheGame, SaveDialogCB_WaitPrintSuccessAndPlaySE);
    else
        PrintSaveTextWithFollowupFunc(gText_SaveError_PleaseExchangeBackupMemory, SaveDialogCB_WaitPrintErrorAndPlaySE);
    SetSaveDialogDelayTo60Frames();
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_WaitPrintSuccessAndPlaySE(void)
{
    if (!RunTextPrinters_CheckPrinter0Active())
    {
        PlaySE(SE_SAVE);
        sSaveDialogCB = SaveDialogCB_ReturnSuccess;
    }
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_ReturnSuccess(void)
{
    if (!IsSEPlaying() && SaveDialog_Wait60FramesOrAButtonHeld())
    {
        CloseSaveStatsWindow_();
        return SAVECB_RETURN_OKAY;
    }
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_WaitPrintErrorAndPlaySE(void)
{
    if (!RunTextPrinters_CheckPrinter0Active())
    {
        PlaySE(SE_BOO);
        sSaveDialogCB = SaveDialogCB_ReturnError;
    }
    return SAVECB_RETURN_CONTINUE;
}

static u8 SaveDialogCB_ReturnError(void)
{
    if (!SaveDialog_Wait60FramesThenCheckAButtonHeld())
        return SAVECB_RETURN_CONTINUE;
    CloseSaveStatsWindow_();
    return SAVECB_RETURN_ERROR;
}

static void VBlankCB_WhileSavingAfterLinkBattle(void)
{
    TransferPlttBuffer();
}

bool32 DoSetUpSaveAfterLinkBattle(u8 *state)
{
    switch (*state)
    {
    case 0:
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetVBlankCallback(NULL);
        ScanlineEffect_Stop();
        DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);
        DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
        break;
    case 1:
        ResetSpriteData();
        ResetTasks();
        ResetPaletteFade();
        ScanlineEffect_Clear();
        break;
    case 2:
        ResetBgsAndClearDma3BusyFlags(FALSE);
        InitBgsFromTemplates(0, sBGTemplates_AfterLinkSaveMessage, NELEMS(sBGTemplates_AfterLinkSaveMessage));
        InitWindows(sWindowTemplates_AfterLinkSaveMessage);
        LoadStdWindowGfx(0, 0x008, BG_PLTT_ID(15));
        break;
    case 3:
        ShowBg(0);
        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        SetVBlankCallback(VBlankCB_WhileSavingAfterLinkBattle);
        EnableInterrupts(INTR_FLAG_VBLANK);
        break;
    case 4:
        return TRUE;
    }
    (*state)++;
    return FALSE;
}

void CB2_SetUpSaveAfterLinkBattle(void)
{
    if (DoSetUpSaveAfterLinkBattle(&gMain.state))
    {
        CreateTask(task50_after_link_battle_save, 80);
        SetMainCallback2(CB2_WhileSavingAfterLinkBattle);
    }
}

static void CB2_WhileSavingAfterLinkBattle(void)
{
    RunTasks();
    UpdatePaletteFade();
}

static void task50_after_link_battle_save(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        switch (data[0])
        {
        case 0:
            FillWindowPixelBuffer(0, PIXEL_FILL(1));
            AddTextPrinterParameterized2(0, FONT_NORMAL, gText_SavingDontTurnOffThePower2, 0xFF, NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
            DrawTextBorderOuter(0, 0x008, 15);
            PutWindowTilemap(0);
            CopyWindowToVram(0, COPYWIN_FULL);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            if (gWirelessCommType != 0 && InUnionRoom())
                data[0] = 5;
            else
                data[0] = 1;
            break;
        case 1:
            SetContinueGameWarpStatusToDynamicWarp();
            WriteSaveBlock2();
            data[0] = 2;
            break;
        case 2:
            if (WriteSaveBlock1Sector())
            {
                ClearContinueGameWarpStatus2();
                data[0] = 3;
            }
            break;
        case 3:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            data[0] = 4;
            break;
        case 4:
            FreeAllWindowBuffers();
            SetMainCallback2(gMain.savedCallback);
            DestroyTask(taskId);
            break;
        case 5:
            CreateTask(Task_LinkFullSave, 5);
            data[0] = 6;
            break;
        case 6:
            if (!FuncIsActiveTask(Task_LinkFullSave))
                data[0] = 3;
            break;
        }
    }
}

static void PrintSaveStats(void)
{
    u8 y;
    u8 x;
    sSaveStatsWindowId = AddWindow(&sSaveStatsWindowTemplate);
    LoadStdWindowGfx(sSaveStatsWindowId, 0x21D, BG_PLTT_ID(13));
    DrawStdFrameWithCustomTileAndPalette(sSaveStatsWindowId, FALSE, 0x21D, 13);
    SaveStatToString(SAVE_STAT_LOCATION, gStringVar4, 8);
    x = (u32)(112 - GetStringWidth(FONT_NORMAL, gStringVar4, -1)) / 2;
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_NORMAL, x, 0, sTextColor_LocationHeader, -1, gStringVar4);
    x = (u32)(112 - GetStringWidth(FONT_NORMAL, gStringVar4, -1)) / 2;
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 14, sTextColor_StatName, -1, gSaveStatName_Player);
    SaveStatToString(SAVE_STAT_NAME, gStringVar4, 2);
    Menu_PrintFormatIntlPlayerName(sSaveStatsWindowId, gStringVar4, 60, 14);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 28, sTextColor_StatName, -1, gSaveStatName_Badges);
    SaveStatToString(SAVE_STAT_BADGES, gStringVar4, 2);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, 28, sTextColor_StatValue, -1, gStringVar4);
    y = 42;
    if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
    {
        AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, 42, sTextColor_StatName, -1, gSaveStatName_Pokedex);
        SaveStatToString(SAVE_STAT_POKEDEX, gStringVar4, 2);
        AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, 42, sTextColor_StatValue, -1, gStringVar4);
        y = 56;
    }
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 2, y, sTextColor_StatName, -1, gSaveStatName_Time);
    SaveStatToString(SAVE_STAT_TIME, gStringVar4, 2);
    AddTextPrinterParameterized3(sSaveStatsWindowId, FONT_SMALL, 60, y, sTextColor_StatValue, -1, gStringVar4);
    CopyWindowToVram(sSaveStatsWindowId, COPYWIN_GFX);
}

static void CloseSaveStatsWindow(void)
{
    ClearStdWindowAndFrame(sSaveStatsWindowId, FALSE);
    RemoveWindow(sSaveStatsWindowId);
}

static void CloseStartMenu(void)
{
    RemoveStartMenuScrollArrows();
    PlaySE(SE_SELECT);
    ClearStdWindowAndFrame(GetStartMenuWindowId(), TRUE);
    RemoveStartMenuWindow();
    ClearPlayerHeldMovementAndUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
}

void AppendToList(u8 *list, u8 *cursor, u8 newEntry)
{
    list[*cursor] = newEntry;
    (*cursor)++;
}

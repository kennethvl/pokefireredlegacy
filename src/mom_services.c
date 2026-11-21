#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "field_message_box.h"
#include "list_menu.h"
#include "menu.h"
#include "menu_indicators.h"
#include "mom_services.h"
#include "mon_modifier_logic.h"
#include "new_menu_helpers.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "random.h"
#include "script.h"
#include "task.h"
#include "constants/abilities.h"
#include "constants/flags.h"
#include "constants/pkmn_center_mom.h"
#include "constants/songs.h"

// Mom's services work on a struct BoxPokemon, so the same code handles party Pokémon (&gPlayerParty[i].box)
// and Pokémon in the PC boxes. The PC (pokemon_storage_system_tasks.c) runs the menus and messages.

// If boxMon is a party Pokémon, recalculate its stats (boxed Pokémon don't store stats).
static void RecalcStatsIfParty(struct BoxPokemon *boxMon)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (&gPlayerParty[i].box == boxMon)
        {
            CalculateMonStats(&gPlayerParty[i]);
            return;
        }
    }
}

static const u8 sIVMonData[NUM_STATS] =
{
    MON_DATA_HP_IV, MON_DATA_ATK_IV, MON_DATA_DEF_IV, MON_DATA_SPEED_IV, MON_DATA_SPATK_IV, MON_DATA_SPDEF_IV,
};

static const u8 sEVMonData[NUM_STATS] =
{
    MON_DATA_HP_EV, MON_DATA_ATK_EV, MON_DATA_DEF_EV, MON_DATA_SPEED_EV, MON_DATA_SPATK_EV, MON_DATA_SPDEF_EV,
};

static void GetBoxMonIVs(struct BoxPokemon *boxMon, u8 *ivs)
{
    u8 i;

    for (i = 0; i < NUM_STATS; i++)
        ivs[i] = GetBoxMonData(boxMon, sIVMonData[i], NULL);
}

static void GetBoxMonEVs(struct BoxPokemon *boxMon, u8 *evs)
{
    u8 i;

    for (i = 0; i < NUM_STATS; i++)
        evs[i] = GetBoxMonData(boxMon, sEVMonData[i], NULL);
}

// Called for every icon the PC shows, so it only reads the data the service needs.
bool8 Mom_IsServiceUseless(u8 service, struct BoxPokemon *boxMon)
{
    u8 ivs[NUM_STATS] = {0}, evs[NUM_STATS] = {0};
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);

    if (species == SPECIES_NONE)
        return TRUE;
    if (service == MODLOGIC_MOM_SERVICE_HYPER_TRAINING)
        GetBoxMonIVs(boxMon, ivs);
    else if (service == MODLOGIC_MOM_SERVICE_MAX_EVS)
        GetBoxMonEVs(boxMon, evs);
    return ModLogic_MomServiceIsUseless(service,
                                        GetBoxMonData(boxMon, MON_DATA_IS_EGG, NULL) || GetBoxMonData(boxMon, MON_DATA_SANITY_IS_BAD_EGG, NULL),
                                        ivs, MAX_PER_STAT_IVS, evs, MAX_PER_STAT_EVS,
                                        gSpeciesInfo[species].abilities[0], gSpeciesInfo[species].abilities[1]);
}

// ---- Hyper Training: raise IVs to 31 ----

static const u8 sText_AllIVs[] = _("all its IVs");
static const u8 sText_HpIV[] = _("its HP IV");
static const u8 sText_AttackIV[] = _("its ATTACK IV");
static const u8 sText_DefenseIV[] = _("its DEFENSE IV");
static const u8 sText_SpAtkIV[] = _("its SP. ATK IV");
static const u8 sText_SpDefIV[] = _("its SP. DEF IV");
static const u8 sText_SpeedIV[] = _("its SPEED IV");

static const u8 *const sHyperTrainingLabels[] =
{
    [MOM_HYPER_ALL]   = sText_AllIVs,
    [MOM_HYPER_HP]    = sText_HpIV,
    [MOM_HYPER_ATK]   = sText_AttackIV,
    [MOM_HYPER_DEF]   = sText_DefenseIV,
    [MOM_HYPER_SPATK] = sText_SpAtkIV,
    [MOM_HYPER_SPDEF] = sText_SpDefIV,
    [MOM_HYPER_SPEED] = sText_SpeedIV,
};

// MON_DATA_*_IV for each single-stat selection (index MOM_HYPER_ALL is unused).
static const u8 sHyperTrainingMonData[] =
{
    [MOM_HYPER_HP]    = MON_DATA_HP_IV,
    [MOM_HYPER_ATK]   = MON_DATA_ATK_IV,
    [MOM_HYPER_DEF]   = MON_DATA_DEF_IV,
    [MOM_HYPER_SPATK] = MON_DATA_SPATK_IV,
    [MOM_HYPER_SPDEF] = MON_DATA_SPDEF_IV,
    [MOM_HYPER_SPEED] = MON_DATA_SPEED_IV,
};

const u8 *Mom_GetHyperTrainingLabel(u8 selection)
{
    return sHyperTrainingLabels[selection];
}

// TRUE if the selection (MOM_HYPER_*) would raise at least one IV.
bool8 Mom_CanHyperTrain(struct BoxPokemon *boxMon, u8 selection)
{
    if (selection == MOM_HYPER_ALL)
    {
        u8 ivs[NUM_STATS];

        GetBoxMonIVs(boxMon, ivs);
        return ModLogic_CountIVsBelowMax(ivs, MAX_PER_STAT_IVS) != 0;
    }
    return GetBoxMonData(boxMon, sHyperTrainingMonData[selection], NULL) < MAX_PER_STAT_IVS;
}

void Mom_ApplyHyperTraining(struct BoxPokemon *boxMon, u8 selection)
{
    u32 maxIV = MAX_PER_STAT_IVS;
    u8 i;

    if (selection == MOM_HYPER_ALL)
    {
        for (i = 0; i < NUM_STATS; i++)
            SetBoxMonData(boxMon, sIVMonData[i], &maxIV);
    }
    else
    {
        SetBoxMonData(boxMon, sHyperTrainingMonData[selection], &maxIV);
    }
    RecalcStatsIfParty(boxMon);
}

// ---- Max EVs: every stat's EVs to 255 (the total EV cap is 6 x 255 too) ----

void Mom_ApplyMaxEVs(struct BoxPokemon *boxMon)
{
    u8 maxEV = MAX_PER_STAT_EVS;
    u8 i;

    for (i = 0; i < NUM_STATS; i++)
        SetBoxMonData(boxMon, sEVMonData[i], &maxEV);
    RecalcStatsIfParty(boxMon);
}

// ---- Ability change: switch between the species' two abilities (like an Ability Capsule) ----

// The ability slot (0 or 1) the Pokémon uses; falls back to slot 0 if its species has no ability in slot 1.
static u8 GetCurrentAbilitySlot(struct BoxPokemon *boxMon)
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    u8 slot = GetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, NULL) ? 1 : 0;

    if (gSpeciesInfo[species].abilities[slot] == ABILITY_NONE)
        slot = 0;
    return slot;
}

// The ability the Pokémon would switch to.
u8 Mom_GetOtherAbility(struct BoxPokemon *boxMon)
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);

    return gSpeciesInfo[species].abilities[ModLogic_OtherAbilitySlot(GetCurrentAbilitySlot(boxMon))];
}

void Mom_ApplyAbilitySwap(struct BoxPokemon *boxMon)
{
    u8 newSlot = ModLogic_OtherAbilitySlot(GetCurrentAbilitySlot(boxMon));

    SetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, &newSlot);
}

// ---- Nature change (stats only, like a Mint); the real nature is kept ----

static const u8 sText_NatureUp[] = _(" +");
static const u8 sText_NatureDown[] = _(" -");
static const u8 sText_NatureNeutral[] = _(" (neutral)");
static const u8 sText_StatAtk[] = _("ATK");
static const u8 sText_StatDef[] = _("DEF");
static const u8 sText_StatSpeed[] = _("SPD");
static const u8 sText_StatSpAtk[] = _("SP.ATK");
static const u8 sText_StatSpDef[] = _("SP.DEF");
static const u8 *const sNatureStatNames[NUM_NATURE_STATS] =
{
    sText_StatAtk,
    sText_StatDef,
    sText_StatSpeed,
    sText_StatSpAtk,
    sText_StatSpDef,
};

// Writes an "ADAMANT +ATK -SP.ATK" style label (at most MOM_NATURE_OPTION_LENGTH bytes) to dst so the player
// can see what each nature does.
void Mom_GetNatureOptionText(u8 nature, u8 *dst)
{
    u8 *str = StringCopy(dst, gNatureNamePointers[nature]);
    u8 stat, up = NUM_NATURE_STATS, down = NUM_NATURE_STATS;

    for (stat = 0; stat < NUM_NATURE_STATS; stat++)
    {
        if (gNatureStatTable[nature][stat] > 0)
            up = stat;
        else if (gNatureStatTable[nature][stat] < 0)
            down = stat;
    }

    if (up == NUM_NATURE_STATS || down == NUM_NATURE_STATS)
    {
        StringCopy(str, sText_NatureNeutral);
    }
    else
    {
        str = StringCopy(str, sText_NatureUp);
        str = StringCopy(str, sNatureStatNames[up]);
        str = StringCopy(str, sText_NatureDown);
        StringCopy(str, sNatureStatNames[down]);
    }
}

// The nature the Pokémon's stats follow (its stat nature if Mom changed it, otherwise its real nature).
u8 Mom_GetStatNature(struct BoxPokemon *boxMon)
{
    return GetBoxMonData(boxMon, MON_DATA_STAT_NATURE, NULL);
}

// Sets the stat nature. Choosing the Pokémon's real nature clears the change (see SetBoxMonData).
void Mom_ApplyNature(struct BoxPokemon *boxMon, u8 nature)
{
    SetBoxMonData(boxMon, MON_DATA_STAT_NATURE, &nature);
    RecalcStatsIfParty(boxMon);
}

// ---- Hidden Power type change (bypasses the IV-derived type; its power still comes from the IVs) ----

static const u8 sHiddenPowerTypes[MOM_NUM_HIDDEN_POWER_TYPES] =
{
    TYPE_FIGHTING, TYPE_FLYING, TYPE_POISON, TYPE_GROUND, TYPE_ROCK, TYPE_BUG, TYPE_GHOST, TYPE_STEEL,
    TYPE_FIRE, TYPE_WATER, TYPE_GRASS, TYPE_ELECTRIC, TYPE_PSYCHIC, TYPE_ICE, TYPE_DRAGON, TYPE_DARK,
};

u8 Mom_GetHiddenPowerListType(u8 index)
{
    return sHiddenPowerTypes[index];
}

u8 Mom_GetHiddenPowerType(struct BoxPokemon *boxMon)
{
    struct Pokemon mon;

    BoxMonToMon(boxMon, &mon);
    return GetMonHiddenPowerType(&mon);
}

void Mom_ApplyHiddenPower(struct BoxPokemon *boxMon, u8 type)
{
    SetBoxMonData(boxMon, MON_DATA_HIDDEN_POWER_TYPE, &type);
}

// ---- Move Relearner (level-up and Egg moves) ----

// Number of level-up and Egg moves the Pokémon could relearn.
u8 Mom_CountMovesToRelearn(struct BoxPokemon *boxMon)
{
    struct Pokemon mon;
    u16 moves[MAX_RELEARNER_WITH_EGG_MOVES];

    if (GetBoxMonData(boxMon, MON_DATA_IS_EGG, NULL))
        return 0;
    BoxMonToMon(boxMon, &mon);
    return GetRelearnerMovesWithEggMoves(&mon, moves);
}

// ---- Mom's service menu ----

static const u8 sText_MomHyperTraining[] = _("HYPER TRAINING");
static const u8 sText_MomNature[] = _("NATURE");
static const u8 sText_MomAbility[] = _("ABILITY");
static const u8 sText_MomHiddenPower[] = _("HIDDEN POWER");
static const u8 sText_MomMaxEVs[] = _("MAX EVS");
static const u8 sText_MomRelearnMoves[] = _("RELEARN MOVES");
static const u8 sText_MomCancel[] = _("CANCEL");

// The list index is the service (MODLOGIC_MOM_SERVICE_*); CANCEL returns MOM_NUM_SERVICES.
static const struct ListMenuItem sMomServiceItems[] =
{
    {sText_MomHyperTraining, MODLOGIC_MOM_SERVICE_HYPER_TRAINING},
    {sText_MomNature,        MODLOGIC_MOM_SERVICE_NATURE},
    {sText_MomAbility,       MODLOGIC_MOM_SERVICE_ABILITY},
    {sText_MomHiddenPower,   MODLOGIC_MOM_SERVICE_HIDDEN_POWER},
    {sText_MomMaxEVs,        MODLOGIC_MOM_SERVICE_MAX_EVS},
    {sText_MomRelearnMoves,  MODLOGIC_MOM_SERVICE_RELEARN_MOVES},
    {sText_MomCancel,        MOM_NUM_SERVICES},
};

#define MOM_MENU_ROWS     6
#define MOM_MENU_WIDTH    13
#define MOM_MENU_LEFT     (29 - MOM_MENU_WIDTH)
#define MOM_MENU_TOP      1
#define MOM_MENU_ARROW_X  (8 * (MOM_MENU_LEFT + MOM_MENU_WIDTH / 2) + 4)
#define TAG_MOM_MENU_ARROWS_GFX 2000 // the tags other field list menus use (field_specials.c)
#define TAG_MOM_MENU_ARROWS_PAL 100

// The cursor comes back to the last service between visits to the PC (reset when Mom says goodbye).
static EWRAM_DATA u16 sMomMenuScroll = 0;
static EWRAM_DATA u16 sMomMenuRow = 0;

#define tWindowId    data[0]
#define tListTaskId  data[1]
#define tArrowsId    data[2]
#define tSkipFrame   data[3]

static void Task_MomServiceMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    s32 input;

    if (task->tSkipFrame)
    {
        // Don't read the A press that closed Mom's message as a choice.
        task->tSkipFrame = FALSE;
        return;
    }
    input = ListMenu_ProcessInput(task->tListTaskId);
    ListMenuGetScrollAndRow(task->tListTaskId, &sMomMenuScroll, &sMomMenuRow);
    if (input == LIST_NOTHING_CHOSEN)
        return;
    PlaySE(SE_SELECT);
    gSpecialVar_Result = (input == LIST_CANCEL) ? MOM_NUM_SERVICES : input;
    RemoveScrollIndicatorArrowPair(task->tArrowsId);
    DestroyListMenuTask(task->tListTaskId, &sMomMenuScroll, &sMomMenuRow);
    ClearStdWindowAndFrameToTransparent(task->tWindowId, TRUE);
    RemoveWindow(task->tWindowId);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

// Shows Mom's scrolling service list and puts the chosen MODLOGIC_MOM_SERVICE_* (or MOM_NUM_SERVICES for
// CANCEL / B) in VAR_RESULT. Use with waitstate.
void MomShowServiceMenu(void)
{
    struct ListMenuTemplate list = {0};
    const struct WindowTemplate window = {0, MOM_MENU_LEFT, MOM_MENU_TOP, MOM_MENU_WIDTH, MOM_MENU_ROWS * 2, 15, 0x038};
    u8 taskId = CreateTask(Task_MomServiceMenu, 80);
    struct Task *task = &gTasks[taskId];

    task->tWindowId = AddWindow(&window);
    SetStdWindowBorderStyle(task->tWindowId, 0);
    list.items = sMomServiceItems;
    list.totalItems = ARRAY_COUNT(sMomServiceItems);
    list.maxShowed = MOM_MENU_ROWS;
    list.windowId = task->tWindowId;
    list.item_X = 8;
    list.upText_Y = 2;
    list.cursorPal = 2;
    list.fillValue = 1;
    list.cursorShadowPal = 3;
    list.fontId = FONT_NORMAL;
    if (sMomMenuScroll + sMomMenuRow >= ARRAY_COUNT(sMomServiceItems))
        sMomMenuScroll = sMomMenuRow = 0;
    task->tListTaskId = ListMenuInit(&list, sMomMenuScroll, sMomMenuRow);
    task->tArrowsId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, MOM_MENU_ARROW_X,
                                                               8 * MOM_MENU_TOP - 4,
                                                               8 * (MOM_MENU_TOP + MOM_MENU_ROWS * 2) + 4,
                                                               ARRAY_COUNT(sMomServiceItems) - MOM_MENU_ROWS,
                                                               TAG_MOM_MENU_ARROWS_GFX, TAG_MOM_MENU_ARROWS_PAL, &sMomMenuScroll);
    task->tSkipFrame = TRUE;
    PutWindowTilemap(task->tWindowId);
    CopyWindowToVram(task->tWindowId, COPYWIN_FULL);
}

#undef tWindowId
#undef tListTaskId
#undef tArrowsId
#undef tSkipFrame

// ---- Greetings and goodbyes, by story stage (see ModLogic_MomDialogueStage) ----

#define MOM_GREETINGS_PER_STAGE 3
#define MOM_GOODBYES_PER_STAGE  2

static const u8 sText_MomHelloFresh1[] = _("Oh, {PLAYER}! There you are!\nAre you eating properly?\pPROF. OAK says I worry too much.\nWell, I'm your MOM!$");
static const u8 sText_MomHelloFresh2[] = _("{PLAYER}! Let me look at you…\nYou've grown already, I swear!\pDid you pack your spare socks?\nDon't roll your eyes at me!$");
static const u8 sText_MomHelloFresh3[] = _("Oh, {PLAYER}! I couldn't help it.\nI had to see how you're doing!\pThe house is so quiet without\nyou. Even the TV seems lonely.$");

static const u8 sText_MomHelloBadges1[] = _("{PLAYER}! Is that a GYM BADGE?\nOh, show me, show me!\pI'm telling all of PALLET TOWN\nthe minute I get home!$");
static const u8 sText_MomHelloBadges2[] = _("There's my little GYM challenger!\p{RIVAL}'s sister says {RIVAL}\nis doing well, too. Go get him!$");
static const u8 sText_MomHelloBadges3[] = _("Oh, {PLAYER}, your hair's a mess!\nHold still, let me fix it…\pThere. Now you look like a\nproper POKéMON TRAINER, dear.$");

static const u8 sText_MomHelloRockets1[] = _("{PLAYER}! I saw the news about\nTEAM ROCKET in SAFFRON CITY…\pPromise me you'll be careful.\nI mean it, young one!$");
static const u8 sText_MomHelloRockets2[] = _("Come here, let me hug you.\nI've been so worried, dear.\pThose ROCKET people are scary,\nbut you're braver than them all.$");
static const u8 sText_MomHelloRockets3[] = _("They say SILPH CO. is all locked\nup. Those poor workers…\pIf anyone can help them,\nit's my brave little one.$");

static const u8 sText_MomHelloSilph1[] = _("{PLAYER}! Everyone's talking about\nhow you saved SILPH CO.!\pThe PRESIDENT himself thanked\nyou? Oh, I'm so proud!$");
static const u8 sText_MomHelloSilph2[] = _("You chased TEAM ROCKET right out\nof SAFFRON, didn't you?\pDon't let it go to your head.\n…But I'm bragging to everyone.$");
static const u8 sText_MomHelloSilph3[] = _("{PLAYER}! I'm so very proud of you.\pYou're strong, and you're kind.\nThat's all a MOM could ask for!$");

static const u8 sText_MomHelloAllBadges1[] = _("Eight BADGES, {PLAYER}! Eight!\nThe POKéMON LEAGUE is next…\pI'll be cheering the loudest.\nI've been practicing!$");
static const u8 sText_MomHelloAllBadges2[] = _("VICTORY ROAD, huh? I'll be brave\nabout it. I will. I promise.\p…Did you pack enough POTIONS?\nAnd a sweater? It gets chilly!$");
static const u8 sText_MomHelloAllBadges3[] = _("PROF. OAK says you're ready.\pI know you are, too… but you'll\nalways be my baby, {PLAYER}.$");

static const u8 sText_MomHelloChampion1[] = _("My baby, the CHAMPION! I tell\neveryone at the market, you know.\pPROF. OAK's told his whole lab.\nTwice. He's so proud, it's silly!$");
static const u8 sText_MomHelloChampion2[] = _("Oh, CHAMPION {PLAYER}! Should I bow?\nHa ha! Come here, give me a hug.\pYou'll always be my sweet child,\nno matter how many titles you win.$");
static const u8 sText_MomHelloChampion3[] = _("I watched your match on TV.\nI cried the whole time!\pDon't forget to come home to\nPALLET TOWN for dinner, CHAMPION.$");

static const u8 *const sMomGreetings[MODLOGIC_MOM_NUM_STAGES][MOM_GREETINGS_PER_STAGE] =
{
    [MODLOGIC_MOM_STAGE_FRESH]       = {sText_MomHelloFresh1, sText_MomHelloFresh2, sText_MomHelloFresh3},
    [MODLOGIC_MOM_STAGE_BADGES]      = {sText_MomHelloBadges1, sText_MomHelloBadges2, sText_MomHelloBadges3},
    [MODLOGIC_MOM_STAGE_ROCKETS]     = {sText_MomHelloRockets1, sText_MomHelloRockets2, sText_MomHelloRockets3},
    [MODLOGIC_MOM_STAGE_SILPH_SAVED] = {sText_MomHelloSilph1, sText_MomHelloSilph2, sText_MomHelloSilph3},
    [MODLOGIC_MOM_STAGE_ALL_BADGES]  = {sText_MomHelloAllBadges1, sText_MomHelloAllBadges2, sText_MomHelloAllBadges3},
    [MODLOGIC_MOM_STAGE_CHAMPION]    = {sText_MomHelloChampion1, sText_MomHelloChampion2, sText_MomHelloChampion3},
};

static const u8 sText_MomByeFresh1[] = _("Take care out there, {PLAYER}!\nAnd don't forget to eat well!$");
static const u8 sText_MomByeFresh2[] = _("Brush your teeth, call home, and\nlisten to your POKéMON, dear!$");
static const u8 sText_MomByeBadges1[] = _("Go get that next BADGE, dear!\nAll of PALLET is rooting for you!$");
static const u8 sText_MomByeBadges2[] = _("Wear clean socks to your next\nGYM battle! It's good luck!$");
static const u8 sText_MomByeRockets1[] = _("Please be careful, {PLAYER}.\nCome home safe to me.$");
static const u8 sText_MomByeRockets2[] = _("I love you very much.\nNow go be brave, sweetheart.$");
static const u8 sText_MomByeSilph1[] = _("Off you go, my little hero!\nBut call home more often!$");
static const u8 sText_MomByeSilph2[] = _("Be kind to your POKéMON, dear.\nThey worked hard for you, too.$");
static const u8 sText_MomByeAllBadges1[] = _("Go show the LEAGUE who you are!\nAnd eat a good breakfast first!$");
static const u8 sText_MomByeAllBadges2[] = _("Trust your POKéMON, dear.\nAnd wear a scarf!$");
static const u8 sText_MomByeChampion1[] = _("Come home for dinner soon, dear.\nI'll make your favorite!$");
static const u8 sText_MomByeChampion2[] = _("Off you go, CHAMPION! But you're\nstill doing the dishes at home.$");

static const u8 *const sMomGoodbyes[MODLOGIC_MOM_NUM_STAGES][MOM_GOODBYES_PER_STAGE] =
{
    [MODLOGIC_MOM_STAGE_FRESH]       = {sText_MomByeFresh1, sText_MomByeFresh2},
    [MODLOGIC_MOM_STAGE_BADGES]      = {sText_MomByeBadges1, sText_MomByeBadges2},
    [MODLOGIC_MOM_STAGE_ROCKETS]     = {sText_MomByeRockets1, sText_MomByeRockets2},
    [MODLOGIC_MOM_STAGE_SILPH_SAVED] = {sText_MomByeSilph1, sText_MomByeSilph2},
    [MODLOGIC_MOM_STAGE_ALL_BADGES]  = {sText_MomByeAllBadges1, sText_MomByeAllBadges2},
    [MODLOGIC_MOM_STAGE_CHAMPION]    = {sText_MomByeChampion1, sText_MomByeChampion2},
};

static u8 GetMomDialogueStage(void)
{
    u8 numBadges = 0;
    u16 flag;

    for (flag = FLAG_BADGE01_GET; flag < FLAG_BADGE01_GET + NUM_BADGES; flag++)
    {
        if (FlagGet(flag))
            numBadges++;
    }
    return ModLogic_MomDialogueStage(numBadges, FlagGet(FLAG_RESCUED_MR_FUJI),
                                     FlagGet(FLAG_HIDE_SAFFRON_ROCKETS), FlagGet(FLAG_SYS_GAME_CLEAR));
}

// Prints a random greeting for the current story stage. The script follows with waitmessage + waitbuttonpress.
void MomShowGreeting(void)
{
    sMomMenuScroll = sMomMenuRow = 0;
    ShowFieldMessage(sMomGreetings[GetMomDialogueStage()][Random() % MOM_GREETINGS_PER_STAGE]);
}

// Prints a random goodbye for the current story stage. The script follows with waitmessage + waitbuttonpress.
void MomShowGoodbye(void)
{
    ShowFieldMessage(sMomGoodbyes[GetMomDialogueStage()][Random() % MOM_GOODBYES_PER_STAGE]);
}

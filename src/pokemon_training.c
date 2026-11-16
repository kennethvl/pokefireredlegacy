#include "global.h"
#include "battle_main.h"
#include "gflib.h"
#include "event_data.h"
#include "list_menu.h"
#include "menu.h"
#include "money.h"
#include "new_menu_helpers.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "script.h"
#include "strings.h"
#include "task.h"
#include "constants/pokemon_training.h"
#include "constants/songs.h"
#include "constants/abilities.h"

#define TRAINING_SERVICE_MENU 4
#define TRAINING_IV_SERVICE_MENU 5

static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("Attack");
static const u8 sText_Defense[] = _("Defense");
static const u8 sText_SpAttack[] = _("Sp. Atk");
static const u8 sText_SpDefense[] = _("Sp. Def");
static const u8 sText_Speed[] = _("Speed");
static const u8 sText_MaxAll[] = _("Max all remaining");
static const u8 sText_Max[] = _(" (MAX)");
static const u8 sText_Colon[] = _(": ");
static const u8 sText_Nature[] = _("Nature");
static const u8 sText_Ability[] = _("Ability");
static const u8 sText_Ivs[] = _("IV training");
static const u8 sText_HiddenPower[] = _("HIDDEN POWER type");
static const u8 *const sIvNames[NUM_STATS] = {sText_HP, sText_Attack, sText_Defense, sText_SpAttack, sText_SpDefense, sText_Speed};
static const u8 sIvFields[NUM_STATS] = {MON_DATA_HP_IV, MON_DATA_ATK_IV, MON_DATA_DEF_IV, MON_DATA_SPATK_IV, MON_DATA_SPDEF_IV, MON_DATA_SPEED_IV};
static EWRAM_DATA struct ListMenuItem sTrainingItems[NUM_NATURES + 1] = {0};
static EWRAM_DATA u8 sTrainingIvLabels[NUM_STATS][24] = {0};

// Script arguments: 8004 = party slot, 8005 = choice, 8006 = service.
// Quote only; the application rechecks both eligibility and money before changing anything.
static u16 GetTrainingPrice(u32 *price)
{
    struct Pokemon *mon;
    u16 choice = gSpecialVar_0x8005;
    u8 i;
    u8 remaining = 0;

    *price = 0;
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        return TRAINING_INVALID;
    mon = &gPlayerParty[gSpecialVar_0x8004];
    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE
     || GetMonData(mon, MON_DATA_IS_EGG)
     || GetMonData(mon, MON_DATA_SANITY_IS_BAD_EGG))
        return TRAINING_INVALID;

    if (gSpecialVar_0x8006 == TRAINING_NATURE)
    {
        if (choice >= NUM_NATURES)
            return TRAINING_INVALID;
        if (GetStatNature(mon) == choice)
            return TRAINING_NO_CHANGE;
        *price = TRAINING_PRICE;
    }
    else if (gSpecialVar_0x8006 == TRAINING_HIDDEN_POWER)
    {
        if (choice <= TYPE_NORMAL || choice >= NUMBER_OF_MON_TYPES || choice == TYPE_MYSTERY)
            return TRAINING_INVALID;
        if (GetMonData(mon, MON_DATA_HIDDEN_POWER_TYPE) == choice)
            return TRAINING_NO_CHANGE;
        *price = TRAINING_PRICE;
    }
    else if (gSpecialVar_0x8006 == TRAINING_ABILITY)
    {
        u16 species = GetMonData(mon, MON_DATA_SPECIES);

        if (choice > 1 || gSpeciesInfo[species].abilities[choice] == ABILITY_NONE)
            return TRAINING_INVALID;
        if (GetMonAbility(mon) == gSpeciesInfo[species].abilities[choice])
            return TRAINING_NO_CHANGE;
        *price = TRAINING_PRICE;
    }
    else if (gSpecialVar_0x8006 == TRAINING_IV)
    {
        if (choice > TRAINING_ALL_IVS)
            return TRAINING_INVALID;
        for (i = 0; i < NUM_STATS; i++)
            if ((choice == TRAINING_ALL_IVS || choice == i) && GetMonData(mon, sIvFields[i]) < MAX_PER_STAT_IVS)
                remaining++;
        if (remaining == 0)
            return TRAINING_NO_CHANGE;
        *price = TRAINING_PRICE * remaining;
    }
    else
        return TRAINING_INVALID;
    return TRAINING_SUCCESS;
}

void BufferPokemonTrainingNatures(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];

    StringCopy(gStringVar2, gNatureNamePointers[GetNature(mon)]);
    StringCopy(gStringVar3, gNatureNamePointers[GetStatNature(mon)]);
}

void BufferPokemonTrainingAbility(void)
{
    StringCopy(gStringVar2, gAbilityNames[GetMonAbility(&gPlayerParty[gSpecialVar_0x8004])]);
}

void BufferPokemonTrainingHiddenPower(void)
{
    StringCopy(gStringVar2, gTypeNames[GetMonHiddenPowerType(&gPlayerParty[gSpecialVar_0x8004])]);
}

u16 QuotePokemonTraining(void)
{
    u32 price;
    u16 result = GetTrainingPrice(&price);

    if (result == TRAINING_SUCCESS)
    {
        ConvertIntToDecimalStringN(gStringVar2, price, STR_CONV_MODE_LEFT_ALIGN, 5);
        if (gSpecialVar_0x8006 == TRAINING_NATURE)
            StringCopy(gStringVar3, gNatureNamePointers[gSpecialVar_0x8005]);
        else if (gSpecialVar_0x8006 == TRAINING_HIDDEN_POWER)
            StringCopy(gStringVar3, gTypeNames[gSpecialVar_0x8005]);
        else if (gSpecialVar_0x8006 == TRAINING_ABILITY)
            StringCopy(gStringVar3, gAbilityNames[gSpeciesInfo[GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES)].abilities[gSpecialVar_0x8005]]);
        else if (gSpecialVar_0x8005 == TRAINING_ALL_IVS)
            StringCopy(gStringVar3, sText_MaxAll);
        else
            StringCopy(gStringVar3, sIvNames[gSpecialVar_0x8005]);
    }
    return result;
}

u16 ApplyPokemonTraining(void)
{
    u32 price;
    u16 result = GetTrainingPrice(&price);
    struct Pokemon *mon;
    u8 value;
    u8 i;

    if (result != TRAINING_SUCCESS)
        return result;
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, price))
        return TRAINING_NO_MONEY;

    mon = &gPlayerParty[gSpecialVar_0x8004];
    if (gSpecialVar_0x8006 == TRAINING_NATURE)
    {
        value = gSpecialVar_0x8005;
        SetMonData(mon, MON_DATA_STAT_NATURE, &value);
    }
    else if (gSpecialVar_0x8006 == TRAINING_HIDDEN_POWER)
    {
        value = gSpecialVar_0x8005;
        SetMonData(mon, MON_DATA_HIDDEN_POWER_TYPE, &value);
    }
    else if (gSpecialVar_0x8006 == TRAINING_ABILITY)
    {
        value = gSpecialVar_0x8005;
        SetMonData(mon, MON_DATA_ABILITY_NUM, &value);
    }
    else
    {
        value = MAX_PER_STAT_IVS;
        for (i = 0; i < NUM_STATS; i++)
            if (gSpecialVar_0x8005 == TRAINING_ALL_IVS || gSpecialVar_0x8005 == i)
                SetMonData(mon, sIvFields[i], &value);
        CalculateMonStats(mon);
    }
    RemoveMoney(&gSaveBlock1Ptr->money, price);
    return TRAINING_SUCCESS;
}

static void Task_TrainingMenu(u8 taskId)
{
    s32 input;
    u8 windowId = gTasks[taskId].data[0];
    u8 listId = gTasks[taskId].data[1];

    if (gTasks[taskId].data[2] != 0)
    {
        gTasks[taskId].data[2] = 0;
        return;
    }
    input = ListMenu_ProcessInput(listId);
    if (input == LIST_NOTHING_CHOSEN)
        return;
    PlaySE(SE_SELECT);
    gSpecialVar_Result = input == LIST_CANCEL ? TRAINING_CANCEL : input;
    DestroyListMenuTask(listId, NULL, NULL);
    ClearStdWindowAndFrameToTransparent(windowId, TRUE);
    RemoveWindow(windowId);
    DestroyTask(taskId);
    ScriptContext_Enable();
}

static void ShowTrainingMenu(u8 service)
{
    struct ListMenuTemplate list = {0};
    const struct WindowTemplate window = {0, 6, 1, 22, 12, 15, 0x038};
    u8 count = service == TRAINING_NATURE ? NUM_NATURES + 1 : NUM_STATS + 2;
    u16 species = SPECIES_NONE;
    u8 i;
    u8 number[4];
    u8 taskId;
    u8 windowId;
    u8 iv;

    if (service == TRAINING_SERVICE_MENU || service == TRAINING_IV_SERVICE_MENU)
        count = 3;
    else if (service == TRAINING_HIDDEN_POWER)
        count = NUMBER_OF_MON_TYPES - 1;
    else if (service == TRAINING_ABILITY)
    {
        species = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES);
        count = gSpeciesInfo[species].abilities[1] != ABILITY_NONE
             && gSpeciesInfo[species].abilities[1] != gSpeciesInfo[species].abilities[0] ? 3 : 2;
    }

    for (i = 0; i < count; i++)
    {
        sTrainingItems[i].index = i;
        if (i == count - 1)
        {
            sTrainingItems[i].label = gText_OptionMenuCancel;
            sTrainingItems[i].index = TRAINING_CANCEL;
        }
        else if (service == TRAINING_SERVICE_MENU)
        {
            sTrainingItems[i].label = i == 0 ? sText_Nature : sText_Ability;
            sTrainingItems[i].index = i == 0 ? TRAINING_NATURE : TRAINING_ABILITY;
        }
        else if (service == TRAINING_IV_SERVICE_MENU)
        {
            sTrainingItems[i].label = i == 0 ? sText_Ivs : sText_HiddenPower;
            sTrainingItems[i].index = i == 0 ? TRAINING_IV : TRAINING_HIDDEN_POWER;
        }
        else if (service == TRAINING_HIDDEN_POWER)
        {
            u8 type = i + 1;

            if (type >= TYPE_MYSTERY)
                type++;
            sTrainingItems[i].label = gTypeNames[type];
            sTrainingItems[i].index = type;
        }
        else if (service == TRAINING_ABILITY)
            sTrainingItems[i].label = gAbilityNames[gSpeciesInfo[species].abilities[i]];
        else if (service == TRAINING_NATURE)
            sTrainingItems[i].label = gNatureNamePointers[i];
        else if (i == TRAINING_ALL_IVS)
            sTrainingItems[i].label = sText_MaxAll;
        else
        {
            iv = GetMonData(&gPlayerParty[gSpecialVar_0x8004], sIvFields[i]);
            StringCopy(sTrainingIvLabels[i], sIvNames[i]);
            StringAppend(sTrainingIvLabels[i], sText_Colon);
            ConvertIntToDecimalStringN(number, iv, STR_CONV_MODE_LEFT_ALIGN, 2);
            StringAppend(sTrainingIvLabels[i], number);
            if (iv == MAX_PER_STAT_IVS)
                StringAppend(sTrainingIvLabels[i], sText_Max);
            sTrainingItems[i].label = sTrainingIvLabels[i];
        }
    }
    windowId = AddWindow(&window);
    SetStdWindowBorderStyle(windowId, 0);
    list.items = sTrainingItems;
    list.totalItems = count;
    list.maxShowed = count < 6 ? count : 6;
    list.windowId = windowId;
    list.item_X = 8;
    list.cursorPal = 2;
    list.fillValue = 1;
    list.cursorShadowPal = 3;
    list.fontId = FONT_NORMAL;
    taskId = CreateTask(Task_TrainingMenu, 80);
    gTasks[taskId].data[0] = windowId;
    gTasks[taskId].data[1] = ListMenuInit(&list, 0, 0);
    gTasks[taskId].data[2] = 1;
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

void ShowNatureTrainingMenu(void)
{
    ShowTrainingMenu(TRAINING_NATURE);
}

void ShowIvTrainingMenu(void)
{
    ShowTrainingMenu(TRAINING_IV);
}

void ShowAbilityTrainingMenu(void)
{
    ShowTrainingMenu(TRAINING_ABILITY);
}

void ShowPokemonTrainingServiceMenu(void)
{
    ShowTrainingMenu(TRAINING_SERVICE_MENU);
}

void ShowIvTrainingServiceMenu(void)
{
    ShowTrainingMenu(TRAINING_IV_SERVICE_MENU);
}

void ShowHiddenPowerTrainingMenu(void)
{
    ShowTrainingMenu(TRAINING_HIDDEN_POWER);
}

#include "mon_modifier_logic.h"

unsigned char ModLogic_CountIVsBelowMax(const unsigned char *ivs, unsigned char maxIV)
{
    unsigned char i, count = 0;

    for (i = 0; i < 6; i++)
        if (ivs[i] < maxIV)
            count++;
    return count;
}

unsigned char ModLogic_CanSwapAbility(unsigned char ability0, unsigned char ability1)
{
    return ability1 != 0 && ability1 != ability0;
}

unsigned char ModLogic_OtherAbilitySlot(unsigned char slot)
{
    return slot ? 0 : 1;
}

static unsigned char AllAtLeast(const unsigned char *values, unsigned char max)
{
    unsigned char i;

    for (i = 0; i < 6; i++)
    {
        if (values[i] < max)
            return 0;
    }
    return 1;
}

unsigned char ModLogic_MomServiceIsUseless(unsigned char service, unsigned char isEgg,
                                           const unsigned char *ivs, unsigned char maxIV,
                                           const unsigned char *evs, unsigned char maxEV,
                                           unsigned char ability0, unsigned char ability1)
{
    if (isEgg)
        return 1;
    switch (service)
    {
    case MODLOGIC_MOM_SERVICE_HYPER_TRAINING:
        return AllAtLeast(ivs, maxIV);
    case MODLOGIC_MOM_SERVICE_MAX_EVS:
        return AllAtLeast(evs, maxEV);
    case MODLOGIC_MOM_SERVICE_ABILITY:
        return !ModLogic_CanSwapAbility(ability0, ability1);
    default:
        return 0;
    }
}

unsigned char ModLogic_MomDialogueStage(unsigned char numBadges, unsigned char rescuedFuji,
                                        unsigned char silphFreed, unsigned char champion)
{
    if (champion)
        return MODLOGIC_MOM_STAGE_CHAMPION;
    if (numBadges >= 8)
        return MODLOGIC_MOM_STAGE_ALL_BADGES;
    if (silphFreed)
        return MODLOGIC_MOM_STAGE_SILPH_SAVED;
    if (rescuedFuji)
        return MODLOGIC_MOM_STAGE_ROCKETS;
    if (numBadges > 0)
        return MODLOGIC_MOM_STAGE_BADGES;
    return MODLOGIC_MOM_STAGE_FRESH;
}

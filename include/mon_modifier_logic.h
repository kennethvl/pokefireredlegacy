#ifndef GUARD_MON_MODIFIER_LOGIC_H
#define GUARD_MON_MODIFIER_LOGIC_H

// Pure rules for Mom's Pokémon Center services (Hyper Training, Nature, Ability, Hidden Power type,
// Max EVs and the Move Relearner). This depends on nothing but the C language so it can be compiled
// and tested on the host (see tests/test_mom_services.py). Game code calls these helpers instead of
// open-coding the rules.

// --- Hyper Training ----------------------------------------------------------------------------
// ivs order: HP, Attack, Defense, Speed, Sp. Attack, Sp. Defense.
unsigned char ModLogic_CountIVsBelowMax(const unsigned char *ivs, unsigned char maxIV);

// --- Ability -------------------------------------------------------------------------------------
// A species can switch abilities only if it has two different abilities (like the Ability Capsule).
// ABILITY_NONE is 0.
unsigned char ModLogic_CanSwapAbility(unsigned char ability0, unsigned char ability1);
unsigned char ModLogic_OtherAbilitySlot(unsigned char slot);

// --- Mom's services in the PC -------------------------------------------------------------------
// Service ids, in the order of Mom's menu (the menu index is the service).
#define MODLOGIC_MOM_SERVICE_HYPER_TRAINING 0
#define MODLOGIC_MOM_SERVICE_NATURE         1
#define MODLOGIC_MOM_SERVICE_ABILITY        2
#define MODLOGIC_MOM_SERVICE_HIDDEN_POWER   3
#define MODLOGIC_MOM_SERVICE_MAX_EVS        4
#define MODLOGIC_MOM_SERVICE_RELEARN_MOVES  5
#define MODLOGIC_MOM_NUM_SERVICES           6

// TRUE if the service can't do anything for this Pokémon, so the PC dims its icon and refuses it:
// Eggs for every service, all IVs at maxIV (Hyper Training), all EVs at maxEV (Max EVs), or only one
// ability (Ability). ivs/evs order: HP, Attack, Defense, Speed, Sp. Attack, Sp. Defense.
unsigned char ModLogic_MomServiceIsUseless(unsigned char service, unsigned char isEgg,
                                           const unsigned char *ivs, unsigned char maxIV,
                                           const unsigned char *evs, unsigned char maxEV,
                                           unsigned char ability0, unsigned char ability1);

// --- Mom's dialogue -----------------------------------------------------------------------------
// Story stage that picks Mom's greeting and goodbye. Later stages win.
#define MODLOGIC_MOM_STAGE_FRESH       0 // no badges yet
#define MODLOGIC_MOM_STAGE_BADGES      1 // 1+ badges
#define MODLOGIC_MOM_STAGE_ROCKETS     2 // Team Rocket holds Saffron City (Mr. Fuji rescued, Silph Co. not freed)
#define MODLOGIC_MOM_STAGE_SILPH_SAVED 3 // Giovanni beaten at Silph Co.
#define MODLOGIC_MOM_STAGE_ALL_BADGES  4 // all 8 badges
#define MODLOGIC_MOM_STAGE_CHAMPION    5 // entered the Hall of Fame
#define MODLOGIC_MOM_NUM_STAGES        6
unsigned char ModLogic_MomDialogueStage(unsigned char numBadges, unsigned char rescuedFuji,
                                        unsigned char silphFreed, unsigned char champion);

#endif // GUARD_MON_MODIFIER_LOGIC_H

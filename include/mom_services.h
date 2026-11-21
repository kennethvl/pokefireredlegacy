#ifndef GUARD_MOM_SERVICES_H
#define GUARD_MOM_SERVICES_H

// Mom's services in the Pokémon Center. The script (data/scripts/pkmn_center_mom.pory) shows her menu
// (MomShowServiceMenu), then opens the PC in Mom's mode for the chosen service (MomOpenPC in
// pokemon_storage_system_tasks.c), which runs each service on the chosen Pokémon with these helpers.
// They take a struct BoxPokemon so they work on party Pokémon (&gPlayerParty[i].box) and boxed ones.
// Service ids are MODLOGIC_MOM_SERVICE_* (mon_modifier_logic.h).

// TRUE if the service can't do anything for this Pokémon (the PC dims it and refuses it).
bool8 Mom_IsServiceUseless(u8 service, struct BoxPokemon *boxMon);

// Hyper Training (selection = MOM_HYPER_*)
const u8 *Mom_GetHyperTrainingLabel(u8 selection);
bool8 Mom_CanHyperTrain(struct BoxPokemon *boxMon, u8 selection);
void Mom_ApplyHyperTraining(struct BoxPokemon *boxMon, u8 selection);

// Max EVs
void Mom_ApplyMaxEVs(struct BoxPokemon *boxMon);

// Ability
u8 Mom_GetOtherAbility(struct BoxPokemon *boxMon);
void Mom_ApplyAbilitySwap(struct BoxPokemon *boxMon);

// Nature (stats only)
#define MOM_NATURE_OPTION_LENGTH 24 // longest: "NAUGHTY +ATK -SP.DEF"
void Mom_GetNatureOptionText(u8 nature, u8 *dst);
u8 Mom_GetStatNature(struct BoxPokemon *boxMon);
void Mom_ApplyNature(struct BoxPokemon *boxMon, u8 nature);

// Hidden Power type (any type except Normal and ???)
#define MOM_NUM_HIDDEN_POWER_TYPES 16
u8 Mom_GetHiddenPowerListType(u8 index);
u8 Mom_GetHiddenPowerType(struct BoxPokemon *boxMon);
void Mom_ApplyHiddenPower(struct BoxPokemon *boxMon, u8 type);

// Move Relearner (level-up and Egg moves)
u8 Mom_CountMovesToRelearn(struct BoxPokemon *boxMon);

// Specials
void MomShowGreeting(void);
void MomShowGoodbye(void);
void MomShowServiceMenu(void);
void MomOpenPC(void);

#endif // GUARD_MOM_SERVICES_H

# 1 "data/scripts/pkmn_center_mom.pory"

# 2 "data/scripts/pkmn_center_mom.pory"
@ Mom, found in every Pokémon Center (after receiving the POKéDEX, and not in HARD / NUZLOCKE mode).
# 3 "data/scripts/pkmn_center_mom.pory"
@ She offers free services: Hyper Training, Nature, Ability and Hidden Power type changes, max EVs and
# 4 "data/scripts/pkmn_center_mom.pory"
@ the Move Relearner (level-up and Egg moves). Each service opens the PC in Mom's mode (MomOpenPC in
# 5 "data/scripts/pkmn_center_mom.pory"
@ src/pokemon_storage_system_tasks.c), where the player picks any party or boxed Pokémon and the service
# 6 "data/scripts/pkmn_center_mom.pory"
@ runs without leaving the PC.
# 7 "data/scripts/pkmn_center_mom.pory"

# 8 "data/scripts/pkmn_center_mom.pory"
@ Called from every Pokémon Center's OnTransition. FLAG_TEMP_10 hides Mom and is cleared on every map load.
# 9 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_EventScript_UpdateMom::
# 10 "data/scripts/pkmn_center_mom.pory"
	goto_if_unset FLAG_SYS_POKEDEX_GET, PokemonCenter_EventScript_HideMom
# 11 "data/scripts/pkmn_center_mom.pory"
	goto_if_set FLAG_HARD, PokemonCenter_EventScript_HideMom
# 12 "data/scripts/pkmn_center_mom.pory"
	goto_if_set FLAG_NUZLOCKE, PokemonCenter_EventScript_HideMom
# 13 "data/scripts/pkmn_center_mom.pory"
	clearflag FLAG_TEMP_10
# 14 "data/scripts/pkmn_center_mom.pory"
	return
# 15 "data/scripts/pkmn_center_mom.pory"

# 16 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_EventScript_HideMom::
# 17 "data/scripts/pkmn_center_mom.pory"
	setflag FLAG_TEMP_10
# 18 "data/scripts/pkmn_center_mom.pory"
	return
# 19 "data/scripts/pkmn_center_mom.pory"

# 20 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_EventScript_Mom::
# 21 "data/scripts/pkmn_center_mom.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 22 "data/scripts/pkmn_center_mom.pory"
	lock
# 23 "data/scripts/pkmn_center_mom.pory"
	faceplayer
# 24 "data/scripts/pkmn_center_mom.pory"
	special MomShowGreeting
# 25 "data/scripts/pkmn_center_mom.pory"
	waitmessage
# 26 "data/scripts/pkmn_center_mom.pory"
	waitbuttonpress
# 27 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_EventScript_MomMenu::
# 28 "data/scripts/pkmn_center_mom.pory"
	message PokemonCenter_Text_MomWhatCanIDo
# 29 "data/scripts/pkmn_center_mom.pory"
	waitmessage
# 30 "data/scripts/pkmn_center_mom.pory"
	special MomShowServiceMenu
# 31 "data/scripts/pkmn_center_mom.pory"
	waitstate
# 32 "data/scripts/pkmn_center_mom.pory"
	goto_if_ge VAR_RESULT, MOM_NUM_SERVICES, PokemonCenter_EventScript_MomGoodbye
# 33 "data/scripts/pkmn_center_mom.pory"
	@ The menu index is the service (MODLOGIC_MOM_SERVICE_*): open the PC for it, then come back here.
# 34 "data/scripts/pkmn_center_mom.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 35 "data/scripts/pkmn_center_mom.pory"
	special MomOpenPC
# 36 "data/scripts/pkmn_center_mom.pory"
	waitstate
# 37 "data/scripts/pkmn_center_mom.pory"
	goto PokemonCenter_EventScript_MomMenu
# 38 "data/scripts/pkmn_center_mom.pory"
	end
# 39 "data/scripts/pkmn_center_mom.pory"

# 40 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_EventScript_MomGoodbye::
# 41 "data/scripts/pkmn_center_mom.pory"
	special MomShowGoodbye
# 42 "data/scripts/pkmn_center_mom.pory"
	waitmessage
# 43 "data/scripts/pkmn_center_mom.pory"
	waitbuttonpress
# 44 "data/scripts/pkmn_center_mom.pory"
	release
# 45 "data/scripts/pkmn_center_mom.pory"
	end
# 46 "data/scripts/pkmn_center_mom.pory"

# 47 "data/scripts/pkmn_center_mom.pory"
PokemonCenter_Text_MomWhatCanIDo:
# 48 "data/scripts/pkmn_center_mom.pory"
	.string "Now, what can your MOM do\n"
# 49 "data/scripts/pkmn_center_mom.pory"
	.string "for you today, dear?$"

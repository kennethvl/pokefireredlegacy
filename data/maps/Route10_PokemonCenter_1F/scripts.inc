# 1 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 2 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
.equ REQUIRED_SEEN_MONS, 10
# 3 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 4 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_MapScripts::
# 5 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_PokemonCenter_1F_OnTransition
# 6 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	.byte 0
# 7 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 8 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_OnTransition::
# 9 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call PokemonCenter_EventScript_UpdateMom
# 10 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	setworldmapflag FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
# 11 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	setrespawn SPAWN_ROUTE10
# 12 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 13 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 14 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_Nurse::
# 15 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	lock
# 16 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	faceplayer
# 17 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 18 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call_if_set FLAG_IS_CHAMPION, Route10_PokemonCenter_1F_BattleNurse
# 19 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	release
# 20 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 21 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 22 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_BattleNurse::
# 23 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	waitmessage
# 24 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_BattleNurse
# 25 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	waitmessage
# 26 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	playse SE_PIN
# 27 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
# 28 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_DEFEATED_NURSE_JOY, Route10_PokemonCenter_1F_EventScript_RematchNurse
# 29 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_Nurse, MSGBOX_YESNO
# 30 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route10_PokemonCenter_1F_EventScript_NoNurse
# 31 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	trainerbattle_single TRAINER_NURSE_JOY, Route10_PokemonCenter_1F_Text_YesNurse, Route10_PokemonCenter_1F_Text_NurseDefeat, Route10_PokemonCenter_1F_EventScript_PostNurse, NO_MUSIC
# 32 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return
# 33 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 34 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 35 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_PostNurse::
# 36 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_NursePostBattle
# 37 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	setflag FLAG_DEFEATED_NURSE_JOY
# 38 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	cleartrainerflag TRAINER_NURSE_JOY
# 39 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 40 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return
# 41 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 42 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_NoNurse::
# 43 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_NoNurse
# 44 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return
# 45 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 46 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_RematchNurse::
# 47 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_RematchNurse, MSGBOX_YESNO
# 48 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route10_PokemonCenter_1F_EventScript_NoNurse
# 49 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	lock
# 50 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	faceplayer
# 51 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	trainerbattle_single TRAINER_NURSE_JOY, Route10_PokemonCenter_1F_Text_YesNurse, Route10_PokemonCenter_1F_Text_RematchNurseDefeat, Route10_PokemonCenter_1F_EventScript_PostRematchNurse, NO_MUSIC
# 52 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return	
# 53 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 54 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_PostRematchNurse::
# 55 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_PostRematchNurse
# 56 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	cleartrainerflag TRAINER_NURSE_JOY
# 57 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 58 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return
# 59 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 60 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 61 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_FatMan::
# 62 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000, MSGBOX_NPC
# 63 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 64 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 65 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_Gentleman::
# 66 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers, MSGBOX_NPC
# 67 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 68 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 69 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_Youngster::
# 70 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender, MSGBOX_NPC
# 71 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 72 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 73 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_Aide::
# 74 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	lock
# 75 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	faceplayer
# 76 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
# 77 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_GOT_HM05, Route10_PokemonCenter_1F_EventScript_AlreadyGotHM05
# 78 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_GiveHM05IfSeen10Mons, MSGBOX_YESNO
# 79 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
# 80 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	setvar VAR_0x8004, 0
# 81 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	specialvar VAR_RESULT, GetPokedexCount
# 82 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	buffernumberstring STR_VAR_3, VAR_0x8006
# 83 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
# 84 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_lt VAR_0x8006, REQUIRED_SEEN_MONS, Aide_EventScript_HaventCaughtEnough
# 85 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_GreatHereYouGo
# 86 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	checkitemspace ITEM_HM05
# 87 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
# 88 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	giveitem_msg Route10_PokemonCenter_1F_Text_ReceivedHM05FromAide, ITEM_HM05
# 89 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	setflag FLAG_GOT_HM05
# 90 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_ExplainHM05
# 91 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	release
# 92 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 93 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 94 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_AlreadyGotHM05::
# 95 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_ExplainHM05
# 96 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	release
# 97 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end
# 98 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 99 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo::
# 100 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	buffernumberstring STR_VAR_1, REQUIRED_SEEN_MONS
# 101 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	bufferitemname STR_VAR_2, ITEM_HM05
# 102 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	return
# 103 "data/maps/Route10_PokemonCenter_1F/scripts.pory"

# 104 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
Route10_PokemonCenter_1F_EventScript_PokecenterChansey::
# 105 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	lock
# 106 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	faceplayer
# 107 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	playmoncry SPECIES_CHANSEY, 0
# 108 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	msgbox Route10_PokemonCenter_1F_Text_PokecenterChansey
# 109 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	waitmoncry
# 110 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	release
# 111 "data/maps/Route10_PokemonCenter_1F/scripts.pory"
	end

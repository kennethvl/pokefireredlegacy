# 1 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 2 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
.set LOCALID_DOOR_GUARD, 5
# 3 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 4 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_MapScripts::
# 5 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_PokemonCenter_1F_OnTransition
# 6 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.byte 0
# 7 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 8 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_OnTransition::
# 9 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	call PokemonCenter_EventScript_UpdateMom
# 10 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	setrespawn SPAWN_INDIGO_PLATEAU
# 11 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	specialvar VAR_RESULT, IsNationalPokedexEnabled
# 12 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor
# 13 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 14 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 15 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_CheckBlockDoor::
# 16 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SYS_CAN_LINK_WITH_RS, EventScript_Return
# 17 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	setobjectxyperm LOCALID_DOOR_GUARD, 4, 2
# 18 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	return
# 19 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 20 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_DoorGuard::
# 21 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 22 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 23 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	specialvar VAR_RESULT, IsNationalPokedexEnabled
# 24 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete
# 25 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
# 26 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 27 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 28 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 29 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_CheckSeviiIslandComplete::
# 30 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SYS_CAN_LINK_WITH_RS, IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete
# 31 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_LoreleiIsAbsentClosedForTimeBeing
# 32 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 33 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 34 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 35 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_SeviiIslandComplete::
# 36 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_FaceEliteFourGoodLuck
# 37 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 38 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 39 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 40 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_GymGuy::
# 41 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	call CinnabarIsland_EventScript_FishermanCheckFishingRod
# 42 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	call CinnabarIsland_EventScript_FishermanCheckPokeballs
# 43 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_GymGuyAdvice, MSGBOX_NPC
# 44 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 45 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 46 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_Clerk::
# 47 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 48 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 49 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 50 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	message Text_MayIHelpYou
# 51 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmessage
# 52 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	pokemart IndigoPlateau_PokemonCenter_1F_Items
# 53 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 54 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 55 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 56 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 57 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.align 2
# 58 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_Items::
# 59 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 60 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 61 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_HYPER_POTION
# 62 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_FULL_RESTORE
# 63 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_MAX_POTION
# 64 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_ETHER
# 65 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_ELIXIR
# 66 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_REVIVE
# 67 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_FULL_HEAL
# 68 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_MAX_REPEL
# 69 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_POKE_BALL
# 70 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 71 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 72 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_NET_BALL
# 73 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 74 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_NEST_BALL
# 75 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 76 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 77 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 78 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 79 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 80 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_NONE
# 81 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 82 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 83 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 84 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_Nurse::
# 85 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 86 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 87 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 88 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 89 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 90 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 91 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_TMGUY::
# 92 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 93 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 94 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 95 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	message IndigoPlateau_PokemonCenter_1F_Text_TmGuy
# 96 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmessage
# 97 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	pokemart IndigoPlateau_PokemonCenter_1F_TMGUY
# 98 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 99 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 100 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 101 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 102 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.align 2
# 103 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_TMGUY::
# 104 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM07
# 105 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM11
# 106 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM13
# 107 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM18
# 108 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM23
# 109 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM24
# 110 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM30
# 111 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM35
# 112 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM37
# 113 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM48
# 114 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_TM49
# 115 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.2byte ITEM_NONE
# 116 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 117 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 118 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 119 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 120 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_TrainMore::
# 121 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_TrainMore, MSGBOX_NPC
# 122 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 123 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 124 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_TrainMoreGengar::
# 125 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 126 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 127 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	playmoncry SPECIES_GENGAR, 0
# 128 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_TrainMoreGengar
# 129 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmoncry
# 130 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 131 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 132 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 133 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_AlmostReady::
# 134 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_AlmostReady, MSGBOX_NPC
# 135 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 136 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 137 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_AlmostReadyAlakazam::
# 138 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 139 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	faceplayer
# 140 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	playmoncry SPECIES_ALAKAZAM, 0
# 141 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	msgbox IndigoPlateau_PokemonCenter_1F_Text_AlmostReadyAlakazam
# 142 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmoncry
# 143 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 144 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	
# 145 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	
# 146 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_HardcoreCandyCheck::
# 147 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	goto_if_unset FLAG_HARD, IndigoPlateau_PokemonCenter_1F_EventScript_NotHard
# 148 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    lock
# 149 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    special CheckGotMoreThan10RareCandies
# 150 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    compare VAR_RESULT, TRUE
# 151 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    goto_if_eq IndigoPlateau_PokemonCenter_1F_EventScript_HardcoreCandyCheckNo
# 152 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    release
# 153 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    end
# 154 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 155 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_HardcoreCandyCheckNo::
# 156 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	lock
# 157 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 158 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_DOOR_GUARD, Common_Movement_FaceLeft
# 159 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 160 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	delay 20
# 161 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_FEMALE
# 162 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
    msgbox IndigoPlateau_PokemonCenter_1F_Text_No, MSGBOX_DEFAULT
# 163 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	closemessage
# 164 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CinnabarIsland_Movement_ForcePlayerFromDoor
# 165 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 166 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 167 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end
# 168 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 169 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_Text_No::
# 170 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.string "Hey, I detect that you have more\n"
# 171 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.string "than 15 rare candies!\l"
# 172 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.string "Please put them away before\l"
# 173 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	.string "entering the league!$"
# 174 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"

# 175 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
IndigoPlateau_PokemonCenter_1F_EventScript_NotHard::
# 176 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	release
# 177 "data/maps/IndigoPlateau_PokemonCenter_1F/scripts.pory"
	end

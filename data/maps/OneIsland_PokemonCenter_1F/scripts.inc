# 1 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 2 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
.equ LOCALID_BILL,  2
# 3 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
.equ LOCALID_CELIO, 3
# 4 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 5 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_MapScripts::
# 6 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_PokemonCenter_1F_OnTransition
# 7 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, OneIsland_PokemonCenter_1F_OnLoad
# 8 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OneIsland_PokemonCenter_1F_OnFrame
# 9 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	.byte 0
# 10 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 11 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_OnLoad::
# 12 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_ge VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile
# 13 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_set FLAG_SYS_CAN_LINK_WITH_RS, OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn
# 14 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 15 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 16 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile::
# 17 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setmetatile 13, 4, METATILE_PokemonCenter_NetworkMachine_Ruby, 1
# 18 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 19 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 20 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile::
# 21 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setmetatile 16, 4, METATILE_PokemonCenter_NetworkMachine_Sapphire, 1
# 22 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 23 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 24 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn::
# 25 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile
# 26 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setmetatile 14, 4, METATILE_PokemonCenter_NetworkMachine_ScreenLeft_On, 1
# 27 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setmetatile 15, 4, METATILE_PokemonCenter_NetworkMachine_ScreenRight_On, 1
# 28 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 29 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 30 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_OnTransition::
# 31 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call PokemonCenter_EventScript_UpdateMom
# 32 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setrespawn SPAWN_ONE_ISLAND
# 33 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6, OneIsland_PokemonCenter_1F_EventScript_SetCelioQuestDone
# 34 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 0, OneIsland_PokemonCenter_1F_EventScript_SetBillCelioFirstMeetingPos
# 35 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 2, OneIsland_PokemonCenter_1F_EventScript_SetBillCelioReadyToLeavePos
# 36 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 37 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 38 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetCelioQuestDone::
# 39 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 7
# 40 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 41 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 42 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetBillCelioFirstMeetingPos::
# 43 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectxyperm LOCALID_BILL, 9, 8
# 44 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectmovementtype LOCALID_BILL, MOVEMENT_TYPE_FACE_UP
# 45 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectxyperm LOCALID_CELIO, 15, 6
# 46 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectmovementtype LOCALID_CELIO, MOVEMENT_TYPE_FACE_UP
# 47 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 48 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 49 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_SetBillCelioReadyToLeavePos::
# 50 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectxyperm LOCALID_BILL, 14, 7
# 51 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectmovementtype LOCALID_BILL, MOVEMENT_TYPE_FACE_LEFT
# 52 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectxyperm LOCALID_CELIO, 14, 8
# 53 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setobjectmovementtype LOCALID_CELIO, MOVEMENT_TYPE_FACE_LEFT
# 54 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 55 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 56 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_OnFrame::
# 57 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	map_script_2 VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 0, OneIsland_PokemonCenter_1F_EventScript_MeetCelioScene
# 58 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	.2byte 0
# 59 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 60 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_MeetCelioScene::
# 61 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 62 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_MALE
# 63 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToCelio
# 64 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, OneIsland_PokemonCenter_1F_Movement_BillWalkToCelio
# 65 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 66 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillHeyThereCelio
# 67 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 68 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 69 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_PIN
# 70 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_ExclamationMark
# 71 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 72 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
# 73 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 74 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_Delay48
# 75 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 76 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioCantBelieveYouCameOut
# 77 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillHowsYourResearchComing
# 78 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterDown
# 79 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 80 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 81 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_ThisIsMyBuddyCelio
# 82 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterRight
# 83 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 84 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 85 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 86 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_set FLAG_SYS_GAME_CLEAR, OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerChamp
# 87 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_unset FLAG_SYS_GAME_CLEAR, OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerNotChamp
# 88 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterDown
# 89 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 90 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioThatsReallyImpressive
# 91 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillBringMeUpToSpeed
# 92 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
# 93 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 94 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPCsCantLinkWithYours
# 95 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 96 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterUp
# 97 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 98 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillLetMeHelpYou
# 99 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterDown
# 100 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 101 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 102 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 103 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CanYouDeliverThisMeteoritePlayer
# 104 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgreceiveditem OneIsland_PokemonCenter_1F_Text_AcceptedMeteoriteFromBill, ITEM_METEORITE, 1, MUS_OBTAIN_KEY_ITEM
# 105 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	additem ITEM_METEORITE
# 106 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterDown
# 107 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 108 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPleaseTakeThis
# 109 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	giveitem_msg OneIsland_PokemonCenter_1F_Text_ObtainedTriPass, ITEM_TRI_PASS, 1, MUS_OBTAIN_KEY_ITEM
# 110 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_PassLetsYouTravelBetweenIslands
# 111 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_ge VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMapPage
# 112 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_lt VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2, OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMap
# 113 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_SYS_SEVII_MAP_123
# 114 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillCatchYouLater
# 115 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 116 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterUp
# 117 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 118 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
# 119 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 120 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_SYS_PC_STORAGE_DISABLED
# 121 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_CELEBI
# 122 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 1
# 123 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	releaseall
# 124 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 125 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 126 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerChamp::
# 127 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_PlayerIsReigningPokemonChamp
# 128 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 129 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 130 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_IntroducePlayerNotChamp::
# 131 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_PlayerIsRisingPokemonChamp
# 132 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 133 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 134 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMapPage::
# 135 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_NEUTRAL
# 136 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_OBTAIN_KEY_ITEM
# 137 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	message OneIsland_PokemonCenter_1F_Text_ReceivedExtraPageForTownMap
# 138 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmessage
# 139 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 140 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call EventScript_RestorePrevTextColor
# 141 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 142 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 143 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_ReceiveTownMap::
# 144 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_HIDE_TOWN_MAP
# 145 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 2
# 146 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	giveitem_msg OneIsland_PokemonCenter_1F_Text_ReceivedTownMap, ITEM_TOWN_MAP, 1, MUS_OBTAIN_KEY_ITEM
# 147 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 148 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 149 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerWalkToCelio::
# 150 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 151 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 152 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 153 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 154 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 155 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 156 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 157 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_up
# 158 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 159 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 160 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_BillWalkToCelio::
# 161 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 162 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 163 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 164 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 165 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 166 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 167 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 168 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_right
# 169 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 170 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 171 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
@ Unused
# 172 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_WalkUp:
# 173 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 174 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 175 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 176 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
@ Unused
# 177 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_StepAsideLeft::
# 178 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 179 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_right
# 180 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 181 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 182 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_Nurse::
# 183 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lock
# 184 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	faceplayer
# 185 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 186 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 187 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 188 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 189 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_Bill::
# 190 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lock
# 191 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_PokemonCenter_1F_EventScript_BillGoTakeStroll
# 192 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_HmmHowAboutLikeThis
# 193 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 194 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 195 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 196 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_BillGoTakeStroll::
# 197 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_FacePlayer
# 198 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 199 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_GotPCWorkingStrollAWhileMore
# 200 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 201 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 202 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 203 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_Celio::
# 204 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lock
# 205 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	faceplayer
# 206 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 7, OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact
# 207 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6, OneIsland_PokemonCenter_1F_EventScript_CelioJustGivenSapphire
# 208 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_RECOVERED_SAPPHIRE, OneIsland_PokemonCenter_1F_EventScript_GiveCelioSapphire
# 209 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5, OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass
# 210 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_GOT_RUBY, OneIsland_PokemonCenter_1F_EventScript_GiveCelioRuby
# 211 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4, OneIsland_PokemonCenter_1F_EventScript_CelioWaitingForRuby
# 212 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	specialvar VAR_RESULT, IsNationalPokedexEnabled
# 213 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OneIsland_PokemonCenter_1F_EventScript_CelioRequestRuby
# 214 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 3, OneIsland_PokemonCenter_1F_EventScript_CelioPlayerMissingNationalDex
# 215 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_SorryForBeingPoorHost
# 216 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 217 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_FaceOriginalDirection
# 218 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 219 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 220 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 221 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 222 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_CelioGiveBillFact::
# 223 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioHearingRumorsAboutYou
# 224 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	random 3
# 225 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, 0, OneIsland_PokemonCenter_1F_EventScript_BillFact1
# 226 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, 1, OneIsland_PokemonCenter_1F_EventScript_BillFact2
# 227 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	famechecker FAMECHECKER_BILL, 5
# 228 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillCantStomachMilk
# 229 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 230 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 231 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 232 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_BillFact1::
# 233 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	famechecker FAMECHECKER_BILL, 3
# 234 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillsFirstMonWasAbra
# 235 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 236 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 237 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 238 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_BillFact2::
# 239 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	famechecker FAMECHECKER_BILL, 4
# 240 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillsHometownInGoldenrod
# 241 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 242 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 243 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 244 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_CelioJustGivenSapphire::
# 245 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_WishYouBestOfLuck
# 246 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 247 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 248 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 249 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_GiveCelioSapphire::
# 250 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_NEUTRAL
# 251 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_OBTAIN_TMHM
# 252 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	message OneIsland_PokemonCenter_1F_Text_HandedSapphireToCelio
# 253 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmessage
# 254 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 255 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call EventScript_RestorePrevTextColor
# 256 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	removeitem ITEM_SAPPHIRE
# 257 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_ThankYouGiveMeTime
# 258 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 259 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine
# 260 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 261 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_CLICK
# 262 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call OneIsland_PokemonCenter_1F_EventScript_SetSapphireMetatile
# 263 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	special DrawWholeMapView
# 264 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_OkayThisIsGood
# 265 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 266 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 60
# 267 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine
# 268 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 269 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 30
# 270 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine
# 271 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 272 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 40
# 273 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_PC_ON
# 274 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call OneIsland_PokemonCenter_1F_EventScript_SetNetworkMachineOn
# 275 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	special DrawWholeMapView
# 276 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_LinkedUpWithLanette
# 277 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
# 278 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 279 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_ManagedToLinkWithHoennThankYou
# 280 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	special SetPostgameFlags
# 281 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_SYS_CAN_LINK_WITH_RS
# 282 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	clearflag FLAG_HIDE_SEVIIGUYS
# 283 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	clearflag FLAG_HIDE_JOHTO_LEADERS
# 284 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_HIDE_CERULEAN_CAVE_GUARD
# 285 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_HIDE_LORELEI_IN_HER_HOUSE
# 286 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	clearflag FLAG_HIDE_GIOVANNI_ONE
# 287 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 6
# 288 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	special InitRoamer
# 289 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 290 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 291 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 292 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass::
# 293 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_PassLetYouGetToAllIslands
# 294 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 295 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 296 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 297 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_GiveCelioRuby::
# 298 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_OhThats
# 299 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_NEUTRAL
# 300 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_OBTAIN_TMHM
# 301 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	message OneIsland_PokemonCenter_1F_Text_HandedRubyToCelio
# 302 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmessage
# 303 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 304 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call EventScript_RestorePrevTextColor
# 305 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 306 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine
# 307 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 308 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_CLICK
# 309 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call OneIsland_PokemonCenter_1F_EventScript_SetRubyMetatile
# 310 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	special DrawWholeMapView
# 311 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 30
# 312 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
# 313 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 314 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_MayIAskOneMoreFavor, MSGBOX_YESNO
# 315 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio
# 316 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass
# 317 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 318 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 319 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio::
# 320 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_PleaseINeedYourHelp, MSGBOX_YESNO
# 321 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, OneIsland_PokemonCenter_1F_EventScript_DeclineHelpCelio
# 322 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass
# 323 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 324 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 325 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_GiveRainbowPass::
# 326 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_AnotherGemstoneInSeviiIslands
# 327 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	removeitem ITEM_RUBY
# 328 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	removeitem ITEM_TRI_PASS
# 329 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 5
# 330 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	additem ITEM_RAINBOW_PASS
# 331 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_SYS_SEVII_MAP_4567
# 332 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_NEUTRAL
# 333 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_OBTAIN_KEY_ITEM
# 334 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	message OneIsland_PokemonCenter_1F_Text_ReturnedTriPassForRainbowPass
# 335 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmessage
# 336 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 337 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_OBTAIN_KEY_ITEM
# 338 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	message OneIsland_PokemonCenter_1F_Text_ObtainedExtraMapPage
# 339 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmessage
# 340 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 341 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call EventScript_RestorePrevTextColor
# 342 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_ExplainRainbowPass
# 343 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 344 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 345 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_CelioWaitingForRuby::
# 346 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_TryingToFindGem
# 347 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 348 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 349 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 350 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_CelioRequestRuby::
# 351 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioCaughtMoreMonMaybeICanBeUseful
# 352 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
# 353 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 354 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_YoullBeTradingFromTrainersFarAway
# 355 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_FacePlayer
# 356 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 357 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_NeedsSpecialGemstone
# 358 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_MT_EMBER_EXTERIOR, 1
# 359 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 4
# 360 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 361 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 362 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 363 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_CelioPlayerMissingNationalDex::
# 364 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioImModifyingMyNetworkMachine
# 365 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 366 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 367 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 368 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_CelioCheckMachine::
# 369 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_up
# 370 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay_8
# 371 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_up
# 372 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 373 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 374 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_CelioPutGemInMachine::
# 375 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_up
# 376 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_up
# 377 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay_16
# 378 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_up
# 379 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_up
# 380 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 381 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 382 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LittleBoy::
# 383 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CameFromPalletDontKnowIt, MSGBOX_NPC
# 384 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 385 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 386 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_Hiker::
# 387 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_EnormousVolcanoOnIsland, MSGBOX_NPC
# 388 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 389 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 390 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_BattleGirl::
# 391 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lock
# 392 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	faceplayer
# 393 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SYS_CAN_LINK_WITH_RS, OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked
# 394 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_WishICouldTradeWithBoyfriend
# 395 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 396 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 397 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 398 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_BattleGirlHoennLinked::
# 399 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_TradedWithFarAwayBoyfriend
# 400 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	release
# 401 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 402 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 403 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_NetworkMachine::
# 404 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 405 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SYS_CAN_LINK_WITH_RS, OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn
# 406 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithKanto
# 407 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_MachineUnderAdjustment
# 408 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	releaseall
# 409 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 410 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 411 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithKanto::
# 412 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKanto
# 413 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	releaseall
# 414 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 415 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 416 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_NetworkMachineLinkedWithHoenn::
# 417 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_MachineLinkedWithKantoAndHoenn
# 418 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	releaseall
# 419 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 420 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 421 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerTop::
# 422 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 423 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_TEMP_1, 1
# 424 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
# 425 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 426 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 427 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidTop::
# 428 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 429 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_TEMP_1, 2
# 430 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
# 431 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 432 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 433 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerMidBottom::
# 434 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 435 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_TEMP_1, 3
# 436 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
# 437 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 438 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 439 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandTriggerBottom::
# 440 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	lockall
# 441 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_TEMP_1, 4
# 442 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene
# 443 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 444 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 445 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_LeaveOneIslandScene::
# 446 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_MALE
# 447 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_PIN
# 448 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_ExclamationMark
# 449 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 450 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillOhHeyPlayer
# 451 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 452 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_TEMP_1, 1, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillTop
# 453 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_TEMP_1, 2, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidTop
# 454 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_TEMP_1, 3, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidBottom
# 455 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	call_if_eq VAR_TEMP_1, 4, OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillBottom
# 456 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 10
# 457 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillWeGotItDone
# 458 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 459 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 460 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioJobWentQuick
# 461 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterDown
# 462 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 463 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterUp
# 464 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 465 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillYouveLearnedALot
# 466 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioOhReallyEhehe
# 467 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 468 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterLeft
# 469 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 470 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 10
# 471 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 472 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 473 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 15
# 474 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_BillWeShouldHeadBackToKanto
# 475 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 476 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, Common_Movement_WalkInPlaceFasterDown
# 477 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 478 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 15
# 479 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_CELIO, Common_Movement_WalkInPlaceFasterLeft
# 480 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 481 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 482 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 483 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	msgbox OneIsland_PokemonCenter_1F_Text_CelioPromiseIllShowYouAroundSometime
# 484 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	closemessage
# 485 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay 25
# 486 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerExit
# 487 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement LOCALID_BILL, OneIsland_PokemonCenter_1F_Movement_BillExit
# 488 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 489 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	playse SE_EXIT
# 490 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setflag FLAG_HIDE_ONE_ISLAND_POKECENTER_BILL
# 491 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_ONE_ISLAND_POKEMON_CENTER_1F, 3
# 492 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	clearflag FLAG_HIDE_CINNABAR_BILL
# 493 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND, 3
# 494 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_0x8004, SEAGALLOP_ONE_ISLAND
# 495 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	setvar VAR_0x8006, SEAGALLOP_CINNABAR_ISLAND
# 496 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	goto EventScript_SetSail
# 497 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	end
# 498 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 499 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillTop::
# 500 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillTop
# 501 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 502 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 503 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 504 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidTop::
# 505 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidTop
# 506 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 507 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 508 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 509 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillMidBottom::
# 510 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidBottom
# 511 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 512 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 513 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 514 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_EventScript_PlayerWalkToBillBottom::
# 515 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillBottom
# 516 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	waitmovement 0
# 517 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	return
# 518 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 519 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillTop::
# 520 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 521 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_down
# 522 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_right
# 523 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 524 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 525 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidTop::
# 526 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 527 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 528 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 529 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillMidBottom::
# 530 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 531 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 532 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_right
# 533 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 534 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 535 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerWalkToBillBottom::
# 536 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_right
# 537 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 538 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_up
# 539 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_right
# 540 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 541 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 542 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
@ Unused
# 543 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_DelayWalkInPlaceLeft::
# 544 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay_16
# 545 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay_16
# 546 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	delay_4
# 547 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_faster_left
# 548 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 549 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 550 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
@ Unused
# 551 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_WalkInPlaceDown::
# 552 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_in_place_fast_down
# 553 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 554 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 555 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_PlayerExit::
# 556 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 557 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 558 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 559 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 560 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_down
# 561 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_down
# 562 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end
# 563 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"

# 564 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
OneIsland_PokemonCenter_1F_Movement_BillExit::
# 565 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 566 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 567 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 568 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 569 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_left
# 570 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	walk_down
# 571 "data/maps/OneIsland_PokemonCenter_1F/scripts.pory"
	step_end

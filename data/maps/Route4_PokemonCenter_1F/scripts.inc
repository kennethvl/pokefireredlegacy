# 1 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 2 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
.equ MAGIKARP_PRICE, 500
# 3 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 4 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_MapScripts::
# 5 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_PokemonCenter_1F_OnTransition
# 6 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	.byte 0
# 7 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 8 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_OnTransition::
# 9 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call PokemonCenter_EventScript_UpdateMom
# 10 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	setworldmapflag FLAG_WORLD_MAP_ROUTE4_POKEMON_CENTER_1F
# 11 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	setrespawn SPAWN_ROUTE4
# 12 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 13 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 14 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Boy::
# 15 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_CanHaveSixMonsWithYou, MSGBOX_NPC
# 16 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 17 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 18 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 19 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Breeder::
# 20 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_BabyMons, MSGBOX_NPC
# 21 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 22 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 23 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 24 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Gentleman::
# 25 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	lock
# 26 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_TeamRocketAttacksCerulean
# 27 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 28 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 29 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 30 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_MagikarpSalesman::
# 31 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	lock
# 32 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	faceplayer
# 33 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_set FLAG_BOUGHT_MAGIKARP, Route4_PokemonCenter_1F_EventScript_AlreadyBoughtMagikarp
# 34 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	showmoneybox 0, 0
# 35 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	checkplayergender
# 36 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, Route4_PokemonCenter_1F_EventScript_AskBuyMagikarpMale
# 37 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, Route4_PokemonCenter_1F_EventScript_AskBuyMagikarpFemale
# 38 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 39 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 40 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_AskBuyMagikarpMale::
# 41 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_LaddieBuyMagikarpForJust500, MSGBOX_YESNO
# 42 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_TryBuyMagikarp
# 43 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 44 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 45 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_AskBuyMagikarpFemale::
# 46 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_SweetieBuyMagikarpForJust500, MSGBOX_YESNO
# 47 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_TryBuyMagikarp
# 48 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 49 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 50 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_TryBuyMagikarp::
# 51 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route4_PokemonCenter_1F_EventScript_DeclineMagikarp
# 52 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	checkmoney MAGIKARP_PRICE
# 53 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route4_PokemonCenter_1F_EventScript_NotEnoughMoney
# 54 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_NEUTRAL
# 55 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_MAGIKARP
# 56 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	givemon SPECIES_MAGIKARP, 5
# 57 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Route4_PokemonCenter_1F_EventScript_BuyMagikarpParty
# 58 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, 1, Route4_PokemonCenter_1F_EventScript_BuyMagikarpPC
# 59 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, 2, Route4_PokemonCenter_1F_EventScript_NoRoomForMagikarp
# 60 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 61 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 62 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_BuyMagikarpParty::
# 63 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call Route4_PokemonCenter_1F_EventScript_PayForMagikarp
# 64 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
# 65 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route4_PokemonCenter_1F_EventScript_EndPurchaseMagikarp
# 66 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call EventScript_GetGiftMonPartySlot
# 67 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	fadescreen FADE_TO_BLACK
# 68 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 69 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	special ChangePokemonNickname
# 70 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	waitstate
# 71 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_BoughtMagikarp
# 72 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 73 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 74 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_BuyMagikarpPC::
# 75 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call Route4_PokemonCenter_1F_EventScript_PayForMagikarp
# 76 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
# 77 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route4_PokemonCenter_1F_EventScript_TransferMagikarpCloseMoneyBox
# 78 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	fadescreen FADE_TO_BLACK
# 79 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 80 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	special ChangeBoxPokemonNickname
# 81 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	waitstate
# 82 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	lock
# 83 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	faceplayer
# 84 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_TransferMagikarp
# 85 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 86 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 87 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_TransferMagikarpCloseMoneyBox::
# 88 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call EventScript_TransferredToPC
# 89 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_EndPurchaseMagikarp
# 90 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 91 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 92 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_TransferMagikarp::
# 93 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call EventScript_TransferredToPC
# 94 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_BoughtMagikarp
# 95 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 96 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 97 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_EndPurchaseMagikarp::
# 98 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 99 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	goto Route4_PokemonCenter_1F_EventScript_BoughtMagikarp
# 100 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 101 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 102 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_BoughtMagikarp::
# 103 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	setflag FLAG_BOUGHT_MAGIKARP
# 104 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 105 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 106 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 107 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_PayForMagikarp::
# 108 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	removemoney MAGIKARP_PRICE
# 109 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	updatemoneybox
# 110 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 111 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	message Route4_PokemonCenter_1F_Text_PaidOutrageouslyForMagikarp
# 112 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	waitmessage
# 113 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	waitfanfare
# 114 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_MAGIKARP
# 115 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	return
# 116 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 117 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_DeclineMagikarp::
# 118 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_OnlyDoingThisAsFavorToYou
# 119 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 120 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 121 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 122 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 123 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_NotEnoughMoney::
# 124 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_YoullNeedMoreMoney
# 125 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 126 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 127 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 128 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 129 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_AlreadyBoughtMagikarp::
# 130 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_IDontGiveRefunds
# 131 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 132 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 133 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 134 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_NoRoomForMagikarp::
# 135 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	textcolor NPC_TEXT_COLOR_MALE
# 136 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_NoRoomForMorePokemon
# 137 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	hidemoneybox
# 138 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 139 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 140 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 141 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Nurse::
# 142 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	lock
# 143 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	faceplayer
# 144 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	call EventScript_PkmnCenterNurse
# 145 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 146 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 147 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 148 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Youngster::
# 149 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_ShouldStoreMonsUsingPC, MSGBOX_NPC
# 150 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end
# 151 "data/maps/Route4_PokemonCenter_1F/scripts.pory"

# 152 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
Route4_PokemonCenter_1F_EventScript_Newspaper::
# 153 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	lock
# 154 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	msgbox Route4_PokemonCenter_1F_Text_ItsANewspaper
# 155 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	release
# 156 "data/maps/Route4_PokemonCenter_1F/scripts.pory"
	end

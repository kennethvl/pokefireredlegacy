# 1 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 2 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_MapScripts::
# 3 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.byte 0
# 4 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 5 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_EventScript_UnusedNPC::
# 6 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_2F_Text_SuperRepelMorePowerfulRepel, MSGBOX_NPC
# 7 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 8 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 9 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_EventScript_Lass::
# 10 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_2F_Text_BuyReviveForLongOutings, MSGBOX_NPC
# 11 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 12 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 13 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_EventScript_FloorSign::
# 14 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_2F_Text_FloorSign, MSGBOX_SIGN
# 15 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 16 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 17 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_EventScript_ClerkItems::
# 18 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 19 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	lock
# 20 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	faceplayer
# 21 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	message Text_MayIHelpYou
# 22 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	waitmessage
# 23 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	pokemart CeladonCity_DepartmentStore_2F_Items
# 24 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 25 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	release
# 26 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 27 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 28 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.align 2
# 29 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_Items::
# 30 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_POKE_BALL
# 31 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 32 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 33 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 34 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_MOOMOO_MILK
# 35 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 36 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 37 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 38 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_NET_BALL
# 39 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 40 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_NEST_BALL
# 41 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 42 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 43 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 44 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 45 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 46 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_REVIVE
# 47 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 48 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 49 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_AWAKENING
# 50 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_BURN_HEAL
# 51 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_ICE_HEAL
# 52 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_SUPER_REPEL
# 53 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_MAX_REPEL
# 54 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_NONE
# 55 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	release
# 56 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 57 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 58 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_EventScript_ClerkTMs::
# 59 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 60 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	lock
# 61 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	faceplayer
# 62 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	message Text_MayIHelpYou
# 63 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	waitmessage
# 64 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	pokemart CeladonCity_DepartmentStore_2F_TMs
# 65 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 66 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	release
# 67 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end
# 68 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"

# 69 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.align 2
# 70 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
CeladonCity_DepartmentStore_2F_TMs::
# 71 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM01
# 72 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM02
# 73 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM03
# 74 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM04
# 75 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM05
# 76 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM06
# 77 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM07
# 78 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM08
# 79 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM09
# 80 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM10
# 81 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM11
# 82 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM12
# 83 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM13
# 84 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM14
# 85 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM15
# 86 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM16
# 87 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM17
# 88 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM18
# 89 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM19
# 90 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM20
# 91 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM21
# 92 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM22
# 93 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM23
# 94 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM24
# 95 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM25
# 96 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM26
# 97 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM27
# 98 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM28
# 99 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM29
# 100 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM30
# 101 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM31
# 102 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM32
# 103 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM33
# 104 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM34
# 105 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM35
# 106 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM36
# 107 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM37
# 108 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM38
# 109 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM39
# 110 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM40
# 111 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM41
# 112 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM42
# 113 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM43
# 114 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM44
# 115 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM45
# 116 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM46
# 117 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM47
# 118 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM48
# 119 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM49
# 120 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_TM50
# 121 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	.2byte ITEM_NONE
# 122 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	release
# 123 "data/maps/CeladonCity_DepartmentStore_2F/scripts.pory"
	end

# 1 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 2 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_MapScripts::
# 3 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.byte 0
# 4 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 5 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_EventScript_Man::
# 6 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_4F_Text_GettingPokeDollAsPresent, MSGBOX_NPC
# 7 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 8 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 9 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_EventScript_Youngster::
# 10 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_4F_Text_CanRunAwayWithPokeDoll, MSGBOX_NPC
# 11 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 12 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 13 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_EventScript_FloorSign::
# 14 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	msgbox CeladonCity_DepartmentStore_4F_Text_FloorSign, MSGBOX_SIGN
# 15 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 16 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 17 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_EventScript_Clerk::
# 18 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 19 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	lock
# 20 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	faceplayer
# 21 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	message Text_MayIHelpYou
# 22 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	waitmessage
# 23 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	pokemart CeladonCity_DepartmentStore_4F_Items
# 24 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 25 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	release
# 26 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 27 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 28 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.align 2
# 29 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_Items::
# 30 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_POKE_DOLL
# 31 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_RETRO_MAIL
# 32 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_SUN_STONE
# 33 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_MOON_STONE
# 34 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_FIRE_STONE
# 35 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_THUNDER_STONE
# 36 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_WATER_STONE
# 37 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_LEAF_STONE
# 38 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_DRAGON_SCALE
# 39 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_KINGS_ROCK
# 40 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_METAL_COAT
# 41 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_UP_GRADE
# 42 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_DEEP_SEA_SCALE
# 43 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_DEEP_SEA_TOOTH
# 44 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_BRICK_PIECE
# 45 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_BLUE_FLUTE
# 46 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_YELLOW_FLUTE
# 47 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_RED_FLUTE
# 48 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_NONE
# 49 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	release
# 50 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 51 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 52 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_EventScript_BerryClerk::
# 53 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 54 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	lock
# 55 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	faceplayer
# 56 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	message Text_MayIHelpYou
# 57 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	waitmessage
# 58 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	pokemart CeladonCity_DepartmentStore_4F_BerryItems
# 59 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	msgbox Text_PleaseComeAgain
# 60 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	release
# 61 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end
# 62 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"

# 63 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.align 2
# 64 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
CeladonCity_DepartmentStore_4F_BerryItems::
# 65 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_ORAN_BERRY
# 66 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_CHERI_BERRY
# 67 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_CHESTO_BERRY
# 68 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_PECHA_BERRY
# 69 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_RAWST_BERRY
# 70 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_ASPEAR_BERRY
# 71 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_PERSIM_BERRY
# 72 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_POMEG_BERRY
# 73 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
# 74 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_QUALOT_BERRY
# 75 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_HONDEW_BERRY
# 76 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_GREPA_BERRY
# 77 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_TAMATO_BERRY
# 78 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	.2byte ITEM_NONE
# 79 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	release
# 80 "data/maps/CeladonCity_DepartmentStore_4F/scripts.pory"
	end

# 1 "data/maps/SevenIsland_Mart/scripts.pory"

# 2 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_MapScripts::
# 3 "data/maps/SevenIsland_Mart/scripts.pory"
	.byte 0
# 4 "data/maps/SevenIsland_Mart/scripts.pory"

# 5 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_EventScript_Clerk::
# 6 "data/maps/SevenIsland_Mart/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 7 "data/maps/SevenIsland_Mart/scripts.pory"
	lock
# 8 "data/maps/SevenIsland_Mart/scripts.pory"
	faceplayer
# 9 "data/maps/SevenIsland_Mart/scripts.pory"
	message Text_MayIHelpYou
# 10 "data/maps/SevenIsland_Mart/scripts.pory"
	waitmessage
# 11 "data/maps/SevenIsland_Mart/scripts.pory"
	pokemart SevenIsland_Mart_Items
# 12 "data/maps/SevenIsland_Mart/scripts.pory"
	msgbox Text_PleaseComeAgain
# 13 "data/maps/SevenIsland_Mart/scripts.pory"
	release
# 14 "data/maps/SevenIsland_Mart/scripts.pory"
	end
# 15 "data/maps/SevenIsland_Mart/scripts.pory"

# 16 "data/maps/SevenIsland_Mart/scripts.pory"
	.align 2
# 17 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_Items::
# 18 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 19 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 20 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_FULL_RESTORE
# 21 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_MAX_POTION
# 22 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_HYPER_POTION
# 23 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_REVIVE
# 24 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_FULL_HEAL
# 25 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 26 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_MAX_REPEL
# 27 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_BLACK_BELT
# 28 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_TWISTED_SPOON
# 29 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_SPELL_TAG
# 30 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_BLACK_GLASSES
# 31 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_MAGNET
# 32 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 33 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 34 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 35 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_NET_BALL
# 36 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 37 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 38 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 39 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 40 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 41 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 42 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 43 "data/maps/SevenIsland_Mart/scripts.pory"
	.2byte ITEM_NONE
# 44 "data/maps/SevenIsland_Mart/scripts.pory"
	release
# 45 "data/maps/SevenIsland_Mart/scripts.pory"
	end
# 46 "data/maps/SevenIsland_Mart/scripts.pory"

# 47 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_EventScript_Lass::
# 48 "data/maps/SevenIsland_Mart/scripts.pory"
	msgbox SevenIsland_Mart_Text_MonHavePersonalitiesOfTheirOwn, MSGBOX_NPC
# 49 "data/maps/SevenIsland_Mart/scripts.pory"
	end
# 50 "data/maps/SevenIsland_Mart/scripts.pory"

# 51 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_EventScript_Hiker::
# 52 "data/maps/SevenIsland_Mart/scripts.pory"
	msgbox SevenIsland_Mart_Text_PreparationsCompleteForRuins, MSGBOX_NPC
# 53 "data/maps/SevenIsland_Mart/scripts.pory"
	end
# 54 "data/maps/SevenIsland_Mart/scripts.pory"

# 55 "data/maps/SevenIsland_Mart/scripts.pory"
SevenIsland_Mart_EventScript_Fisher::
# 56 "data/maps/SevenIsland_Mart/scripts.pory"
	msgbox SevenIsland_Mart_Text_NeedToFishOnSevenIsland, MSGBOX_NPC
# 57 "data/maps/SevenIsland_Mart/scripts.pory"
	end

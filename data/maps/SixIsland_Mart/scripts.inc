# 1 "data/maps/SixIsland_Mart/scripts.pory"

# 2 "data/maps/SixIsland_Mart/scripts.pory"
SixIsland_Mart_MapScripts::
# 3 "data/maps/SixIsland_Mart/scripts.pory"
	.byte 0
# 4 "data/maps/SixIsland_Mart/scripts.pory"

# 5 "data/maps/SixIsland_Mart/scripts.pory"
SixIsland_Mart_EventScript_Clerk::
# 6 "data/maps/SixIsland_Mart/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 7 "data/maps/SixIsland_Mart/scripts.pory"
	lock
# 8 "data/maps/SixIsland_Mart/scripts.pory"
	faceplayer
# 9 "data/maps/SixIsland_Mart/scripts.pory"
	message Text_MayIHelpYou
# 10 "data/maps/SixIsland_Mart/scripts.pory"
	waitmessage
# 11 "data/maps/SixIsland_Mart/scripts.pory"
	pokemart SixIsland_Mart_Items
# 12 "data/maps/SixIsland_Mart/scripts.pory"
	msgbox Text_PleaseComeAgain
# 13 "data/maps/SixIsland_Mart/scripts.pory"
	release
# 14 "data/maps/SixIsland_Mart/scripts.pory"
	end
# 15 "data/maps/SixIsland_Mart/scripts.pory"

# 16 "data/maps/SixIsland_Mart/scripts.pory"
	.align 2
# 17 "data/maps/SixIsland_Mart/scripts.pory"
SixIsland_Mart_Items::
# 18 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 19 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_FULL_RESTORE
# 20 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_MAX_POTION
# 21 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_REVIVE
# 22 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_FULL_HEAL
# 23 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 24 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_MAX_REPEL
# 25 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_DREAM_MAIL
# 26 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_HARD_STONE
# 27 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_SOFT_SAND
# 28 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_SHARP_BEAK
# 29 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_SILVER_POWDER
# 30 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_POISON_BARB
# 31 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 32 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 33 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 34 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 35 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_NET_BALL
# 36 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 37 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 38 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 39 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 40 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 41 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 42 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 43 "data/maps/SixIsland_Mart/scripts.pory"
	.2byte ITEM_NONE
# 44 "data/maps/SixIsland_Mart/scripts.pory"
	release
# 45 "data/maps/SixIsland_Mart/scripts.pory"
	end
# 46 "data/maps/SixIsland_Mart/scripts.pory"

# 47 "data/maps/SixIsland_Mart/scripts.pory"
SixIsland_Mart_EventScript_Picnicker::
# 48 "data/maps/SixIsland_Mart/scripts.pory"
	msgbox SixIsland_Mart_Text_ShouldBuyMailAndWriteLetter, MSGBOX_NPC
# 49 "data/maps/SixIsland_Mart/scripts.pory"
	end

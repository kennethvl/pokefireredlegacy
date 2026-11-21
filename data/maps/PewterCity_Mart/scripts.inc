# 1 "data/maps/PewterCity_Mart/scripts.pory"

# 2 "data/maps/PewterCity_Mart/scripts.pory"
PewterCity_Mart_MapScripts::
# 3 "data/maps/PewterCity_Mart/scripts.pory"
	.byte 0
# 4 "data/maps/PewterCity_Mart/scripts.pory"

# 5 "data/maps/PewterCity_Mart/scripts.pory"
PewterCity_Mart_EventScript_Youngster::
# 6 "data/maps/PewterCity_Mart/scripts.pory"
	msgbox PewterCity_Mart_Text_BoughtWeirdFishFromShadyGuy, MSGBOX_NPC
# 7 "data/maps/PewterCity_Mart/scripts.pory"
	end
# 8 "data/maps/PewterCity_Mart/scripts.pory"

# 9 "data/maps/PewterCity_Mart/scripts.pory"
PewterCity_Mart_EventScript_Boy::
# 10 "data/maps/PewterCity_Mart/scripts.pory"
	msgbox PewterCity_Mart_Text_GoodThingsIfRaiseMonsDiligently, MSGBOX_NPC
# 11 "data/maps/PewterCity_Mart/scripts.pory"
	end
# 12 "data/maps/PewterCity_Mart/scripts.pory"

# 13 "data/maps/PewterCity_Mart/scripts.pory"
PewterCity_Mart_EventScript_Clerk::
# 14 "data/maps/PewterCity_Mart/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 15 "data/maps/PewterCity_Mart/scripts.pory"
	lock
# 16 "data/maps/PewterCity_Mart/scripts.pory"
	faceplayer
# 17 "data/maps/PewterCity_Mart/scripts.pory"
	message Text_MayIHelpYou
# 18 "data/maps/PewterCity_Mart/scripts.pory"
	waitmessage
# 19 "data/maps/PewterCity_Mart/scripts.pory"
	pokemart PewterCity_Mart_Items
# 20 "data/maps/PewterCity_Mart/scripts.pory"
	msgbox Text_PleaseComeAgain
# 21 "data/maps/PewterCity_Mart/scripts.pory"
	release
# 22 "data/maps/PewterCity_Mart/scripts.pory"
	end
# 23 "data/maps/PewterCity_Mart/scripts.pory"

# 24 "data/maps/PewterCity_Mart/scripts.pory"
	.align 2
# 25 "data/maps/PewterCity_Mart/scripts.pory"
PewterCity_Mart_Items::
# 26 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 27 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 28 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 29 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 30 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 31 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_BURN_HEAL
# 32 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 33 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 34 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 35 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 36 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 37 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 38 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_NET_BALL
# 39 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 40 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 41 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 42 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 43 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 44 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 45 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 46 "data/maps/PewterCity_Mart/scripts.pory"
	.2byte ITEM_NONE
# 47 "data/maps/PewterCity_Mart/scripts.pory"
	release
# 48 "data/maps/PewterCity_Mart/scripts.pory"
	end

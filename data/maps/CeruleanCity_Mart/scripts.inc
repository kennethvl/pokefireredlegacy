# 1 "data/maps/CeruleanCity_Mart/scripts.pory"

# 2 "data/maps/CeruleanCity_Mart/scripts.pory"
CeruleanCity_Mart_MapScripts::
# 3 "data/maps/CeruleanCity_Mart/scripts.pory"
	.byte 0
# 4 "data/maps/CeruleanCity_Mart/scripts.pory"

# 5 "data/maps/CeruleanCity_Mart/scripts.pory"
CeruleanCity_Mart_EventScript_Youngster::
# 6 "data/maps/CeruleanCity_Mart/scripts.pory"
	msgbox CeruleanCity_Mart_Text_RepelWorksOnWeakMons, MSGBOX_NPC
# 7 "data/maps/CeruleanCity_Mart/scripts.pory"
	end
# 8 "data/maps/CeruleanCity_Mart/scripts.pory"

# 9 "data/maps/CeruleanCity_Mart/scripts.pory"
CeruleanCity_Mart_EventScript_Woman::
# 10 "data/maps/CeruleanCity_Mart/scripts.pory"
	msgbox CeruleanCity_Mart_Text_DoYouKnowAboutRareCandy, MSGBOX_NPC
# 11 "data/maps/CeruleanCity_Mart/scripts.pory"
	end
# 12 "data/maps/CeruleanCity_Mart/scripts.pory"

# 13 "data/maps/CeruleanCity_Mart/scripts.pory"
CeruleanCity_Mart_EventScript_Clerk::
# 14 "data/maps/CeruleanCity_Mart/scripts.pory"
	goto_if_questlog EventScript_ReleaseEnd
# 15 "data/maps/CeruleanCity_Mart/scripts.pory"
	lock
# 16 "data/maps/CeruleanCity_Mart/scripts.pory"
	faceplayer
# 17 "data/maps/CeruleanCity_Mart/scripts.pory"
	message Text_MayIHelpYou
# 18 "data/maps/CeruleanCity_Mart/scripts.pory"
	waitmessage
# 19 "data/maps/CeruleanCity_Mart/scripts.pory"
	pokemart CeruleanCity_Mart_Items
# 20 "data/maps/CeruleanCity_Mart/scripts.pory"
	msgbox Text_PleaseComeAgain
# 21 "data/maps/CeruleanCity_Mart/scripts.pory"
	release
# 22 "data/maps/CeruleanCity_Mart/scripts.pory"
	end
# 23 "data/maps/CeruleanCity_Mart/scripts.pory"

# 24 "data/maps/CeruleanCity_Mart/scripts.pory"
	.align 2
# 25 "data/maps/CeruleanCity_Mart/scripts.pory"
CeruleanCity_Mart_Items::
# 26 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 27 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 28 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 29 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 30 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 31 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 32 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_BURN_HEAL
# 33 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 34 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 35 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 36 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_ULTRA_BALL
# 37 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_MASTER_BALL
# 38 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_SAFARI_BALL
# 39 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_NET_BALL
# 40 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_DIVE_BALL
# 41 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_NEST_BALL
# 42 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 43 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 44 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_LUXURY_BALL
# 45 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_PREMIER_BALL
# 46 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_LUCKY_EGG
# 47 "data/maps/CeruleanCity_Mart/scripts.pory"
	.2byte ITEM_NONE
# 48 "data/maps/CeruleanCity_Mart/scripts.pory"
	release
# 49 "data/maps/CeruleanCity_Mart/scripts.pory"
	end

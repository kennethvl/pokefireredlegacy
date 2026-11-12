# 1 "data/scripts/pokemon_training.pory"

# 2 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Nature::
# 3 "data/scripts/pokemon_training.pory"
	lock
# 4 "data/scripts/pokemon_training.pory"
	faceplayer
# 5 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_NatureIntro, MSGBOX_YESNO
# 6 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, YES, PokemonTraining_EventScript_Goodbye
# 7 "data/scripts/pokemon_training.pory"
	setvar VAR_0x8006, TRAINING_NATURE
# 8 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_ChooseMon
# 9 "data/scripts/pokemon_training.pory"

# 10 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Ivs::
# 11 "data/scripts/pokemon_training.pory"
	lock
# 12 "data/scripts/pokemon_training.pory"
	faceplayer
# 13 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_IvIntro, MSGBOX_YESNO
# 14 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, YES, PokemonTraining_EventScript_Goodbye
# 15 "data/scripts/pokemon_training.pory"
	setvar VAR_0x8006, TRAINING_IV
# 16 "data/scripts/pokemon_training.pory"

# 17 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseMon::
# 18 "data/scripts/pokemon_training.pory"
	special ChoosePartyMon
# 19 "data/scripts/pokemon_training.pory"
	waitstate
# 20 "data/scripts/pokemon_training.pory"
	goto_if_ge VAR_0x8004, PARTY_SIZE, PokemonTraining_EventScript_Goodbye
# 21 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, GetPartyMonSpecies
# 22 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, SPECIES_EGG, PokemonTraining_EventScript_Invalid
# 23 "data/scripts/pokemon_training.pory"
	special BufferMonNickname
# 24 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_0x8006, TRAINING_IV, PokemonTraining_EventScript_ChooseIv
# 25 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseNature
# 26 "data/scripts/pokemon_training.pory"
	special ShowNatureTrainingMenu
# 27 "data/scripts/pokemon_training.pory"
	waitstate
# 28 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_Quote
# 29 "data/scripts/pokemon_training.pory"

# 30 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseIv::
# 31 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseIv
# 32 "data/scripts/pokemon_training.pory"
	special ShowIvTrainingMenu
# 33 "data/scripts/pokemon_training.pory"
	waitstate
# 34 "data/scripts/pokemon_training.pory"

# 35 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Quote::
# 36 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_CANCEL, PokemonTraining_EventScript_Goodbye
# 37 "data/scripts/pokemon_training.pory"
	copyvar VAR_0x8005, VAR_RESULT
# 38 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, QuotePokemonTraining
# 39 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_CHANGE, PokemonTraining_EventScript_NoChange
# 40 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, TRAINING_SUCCESS, PokemonTraining_EventScript_Invalid
# 41 "data/scripts/pokemon_training.pory"
	showmoneybox 0, 0
# 42 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Confirm, MSGBOX_YESNO
# 43 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, YES, PokemonTraining_EventScript_CancelPayment
# 44 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, ApplyPokemonTraining
# 45 "data/scripts/pokemon_training.pory"
	hidemoneybox
# 46 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_MONEY, PokemonTraining_EventScript_NoMoney
# 47 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_CHANGE, PokemonTraining_EventScript_NoChange
# 48 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, TRAINING_SUCCESS, PokemonTraining_EventScript_Invalid
# 49 "data/scripts/pokemon_training.pory"
	playse SE_SHOP
# 50 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Done
# 51 "data/scripts/pokemon_training.pory"
	release
# 52 "data/scripts/pokemon_training.pory"
	end
# 53 "data/scripts/pokemon_training.pory"

# 54 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_CancelPayment::
# 55 "data/scripts/pokemon_training.pory"
	hidemoneybox
# 56 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Goodbye::
# 57 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Goodbye
# 58 "data/scripts/pokemon_training.pory"
	release
# 59 "data/scripts/pokemon_training.pory"
	end
# 60 "data/scripts/pokemon_training.pory"

# 61 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_NoChange::
# 62 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_NoChange
# 63 "data/scripts/pokemon_training.pory"
	release
# 64 "data/scripts/pokemon_training.pory"
	end
# 65 "data/scripts/pokemon_training.pory"

# 66 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Invalid::
# 67 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Invalid
# 68 "data/scripts/pokemon_training.pory"
	release
# 69 "data/scripts/pokemon_training.pory"
	end
# 70 "data/scripts/pokemon_training.pory"

# 71 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_NoMoney::
# 72 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_NoMoney
# 73 "data/scripts/pokemon_training.pory"
	release
# 74 "data/scripts/pokemon_training.pory"
	end
# 75 "data/scripts/pokemon_training.pory"

# 76 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NatureIntro::
# 77 "data/scripts/pokemon_training.pory"
	.string "I can change a POKéMON's stat nature\n"
# 78 "data/scripts/pokemon_training.pory"
	.string "for ¥5,000. Its original nature stays\l"
# 79 "data/scripts/pokemon_training.pory"
	.string "the same for breeding.\p"
# 80 "data/scripts/pokemon_training.pory"
	.string "SYNCHRONIZE uses the stat nature, too.\n"
# 81 "data/scripts/pokemon_training.pory"
	.string "Would you like my help?$"
# 82 "data/scripts/pokemon_training.pory"

# 83 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_IvIntro::
# 84 "data/scripts/pokemon_training.pory"
	.string "I offer IV training for ¥5,000 per\n"
# 85 "data/scripts/pokemon_training.pory"
	.string "stat. Each chosen IV becomes 31.\p"
# 86 "data/scripts/pokemon_training.pory"
	.string "This also affects breeding and\n"
# 87 "data/scripts/pokemon_training.pory"
	.string "HIDDEN POWER. Shall we begin?$"
# 88 "data/scripts/pokemon_training.pory"

# 89 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseNature::
# 90 "data/scripts/pokemon_training.pory"
	.string "Choose {STR_VAR_1}'s stat nature.\n"
# 91 "data/scripts/pokemon_training.pory"
	.string "Use UP and DOWN to scroll the list.$"
# 92 "data/scripts/pokemon_training.pory"

# 93 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseIv::
# 94 "data/scripts/pokemon_training.pory"
	.string "Choose an IV for {STR_VAR_1}.\n"
# 95 "data/scripts/pokemon_training.pory"
	.string "MAX stats won't cost you anything.$"
# 96 "data/scripts/pokemon_training.pory"

# 97 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Confirm::
# 98 "data/scripts/pokemon_training.pory"
	.string "{STR_VAR_1}: {STR_VAR_3}\n"
# 99 "data/scripts/pokemon_training.pory"
	.string "The total is ¥{STR_VAR_2}. Proceed?$"
# 100 "data/scripts/pokemon_training.pory"

# 101 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Done::
# 102 "data/scripts/pokemon_training.pory"
	.string "All done!\n"
# 103 "data/scripts/pokemon_training.pory"
	.string "Take good care of {STR_VAR_1}!$"
# 104 "data/scripts/pokemon_training.pory"

# 105 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NoChange::
# 106 "data/scripts/pokemon_training.pory"
	.string "That choice needs no change.\n"
# 107 "data/scripts/pokemon_training.pory"
	.string "You haven't been charged.$"
# 108 "data/scripts/pokemon_training.pory"

# 109 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Invalid::
# 110 "data/scripts/pokemon_training.pory"
	.string "I can only train a POKéMON,\n"
# 111 "data/scripts/pokemon_training.pory"
	.string "not an EGG.$"
# 112 "data/scripts/pokemon_training.pory"

# 113 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NoMoney::
# 114 "data/scripts/pokemon_training.pory"
	.string "You don't have enough money.\n"
# 115 "data/scripts/pokemon_training.pory"
	.string "Nothing has been changed.$"
# 116 "data/scripts/pokemon_training.pory"

# 117 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Goodbye::
# 118 "data/scripts/pokemon_training.pory"
	.string "Come back whenever you like!$"

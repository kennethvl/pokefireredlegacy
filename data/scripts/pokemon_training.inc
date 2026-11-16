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
	special ShowPokemonTrainingServiceMenu
# 8 "data/scripts/pokemon_training.pory"
	waitstate
# 9 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_CANCEL, PokemonTraining_EventScript_Goodbye
# 10 "data/scripts/pokemon_training.pory"
	copyvar VAR_0x8006, VAR_RESULT
# 11 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_ChooseMon
# 12 "data/scripts/pokemon_training.pory"

# 13 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Ivs::
# 14 "data/scripts/pokemon_training.pory"
	lock
# 15 "data/scripts/pokemon_training.pory"
	faceplayer
# 16 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_IvIntro, MSGBOX_YESNO
# 17 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, YES, PokemonTraining_EventScript_Goodbye
# 18 "data/scripts/pokemon_training.pory"
	special ShowIvTrainingServiceMenu
# 19 "data/scripts/pokemon_training.pory"
	waitstate
# 20 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_CANCEL, PokemonTraining_EventScript_Goodbye
# 21 "data/scripts/pokemon_training.pory"
	copyvar VAR_0x8006, VAR_RESULT
# 22 "data/scripts/pokemon_training.pory"

# 23 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseMon::
# 24 "data/scripts/pokemon_training.pory"
	special ChoosePartyMon
# 25 "data/scripts/pokemon_training.pory"
	waitstate
# 26 "data/scripts/pokemon_training.pory"
	goto_if_ge VAR_0x8004, PARTY_SIZE, PokemonTraining_EventScript_Goodbye
# 27 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, GetPartyMonSpecies
# 28 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, SPECIES_EGG, PokemonTraining_EventScript_Invalid
# 29 "data/scripts/pokemon_training.pory"
	special BufferMonNickname
# 30 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_0x8006, TRAINING_IV, PokemonTraining_EventScript_ChooseIv
# 31 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_0x8006, TRAINING_ABILITY, PokemonTraining_EventScript_ChooseAbility
# 32 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_0x8006, TRAINING_HIDDEN_POWER, PokemonTraining_EventScript_ChooseHiddenPower
# 33 "data/scripts/pokemon_training.pory"
	special BufferPokemonTrainingNatures
# 34 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseNature
# 35 "data/scripts/pokemon_training.pory"
	special ShowNatureTrainingMenu
# 36 "data/scripts/pokemon_training.pory"
	waitstate
# 37 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_Quote
# 38 "data/scripts/pokemon_training.pory"

# 39 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseIv::
# 40 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseIv
# 41 "data/scripts/pokemon_training.pory"
	special ShowIvTrainingMenu
# 42 "data/scripts/pokemon_training.pory"
	waitstate
# 43 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_Quote
# 44 "data/scripts/pokemon_training.pory"

# 45 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseAbility::
# 46 "data/scripts/pokemon_training.pory"
	special BufferPokemonTrainingAbility
# 47 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseAbility
# 48 "data/scripts/pokemon_training.pory"
	special ShowAbilityTrainingMenu
# 49 "data/scripts/pokemon_training.pory"
	waitstate
# 50 "data/scripts/pokemon_training.pory"
	goto PokemonTraining_EventScript_Quote
# 51 "data/scripts/pokemon_training.pory"

# 52 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_ChooseHiddenPower::
# 53 "data/scripts/pokemon_training.pory"
	special BufferPokemonTrainingHiddenPower
# 54 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_ChooseHiddenPower
# 55 "data/scripts/pokemon_training.pory"
	special ShowHiddenPowerTrainingMenu
# 56 "data/scripts/pokemon_training.pory"
	waitstate
# 57 "data/scripts/pokemon_training.pory"

# 58 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Quote::
# 59 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_CANCEL, PokemonTraining_EventScript_Goodbye
# 60 "data/scripts/pokemon_training.pory"
	copyvar VAR_0x8005, VAR_RESULT
# 61 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, QuotePokemonTraining
# 62 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_CHANGE, PokemonTraining_EventScript_NoChange
# 63 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, TRAINING_SUCCESS, PokemonTraining_EventScript_Invalid
# 64 "data/scripts/pokemon_training.pory"
	showmoneybox 0, 0
# 65 "data/scripts/pokemon_training.pory"
	special BufferMonNickname
# 66 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Confirm, MSGBOX_YESNO
# 67 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, YES, PokemonTraining_EventScript_CancelPayment
# 68 "data/scripts/pokemon_training.pory"
	specialvar VAR_RESULT, ApplyPokemonTraining
# 69 "data/scripts/pokemon_training.pory"
	hidemoneybox
# 70 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_MONEY, PokemonTraining_EventScript_NoMoney
# 71 "data/scripts/pokemon_training.pory"
	goto_if_eq VAR_RESULT, TRAINING_NO_CHANGE, PokemonTraining_EventScript_NoChange
# 72 "data/scripts/pokemon_training.pory"
	goto_if_ne VAR_RESULT, TRAINING_SUCCESS, PokemonTraining_EventScript_Invalid
# 73 "data/scripts/pokemon_training.pory"
	playse SE_SHOP
# 74 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Done
# 75 "data/scripts/pokemon_training.pory"
	release
# 76 "data/scripts/pokemon_training.pory"
	end
# 77 "data/scripts/pokemon_training.pory"

# 78 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_CancelPayment::
# 79 "data/scripts/pokemon_training.pory"
	hidemoneybox
# 80 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Goodbye::
# 81 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Goodbye
# 82 "data/scripts/pokemon_training.pory"
	release
# 83 "data/scripts/pokemon_training.pory"
	end
# 84 "data/scripts/pokemon_training.pory"

# 85 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_NoChange::
# 86 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_NoChange
# 87 "data/scripts/pokemon_training.pory"
	release
# 88 "data/scripts/pokemon_training.pory"
	end
# 89 "data/scripts/pokemon_training.pory"

# 90 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_Invalid::
# 91 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_Invalid
# 92 "data/scripts/pokemon_training.pory"
	release
# 93 "data/scripts/pokemon_training.pory"
	end
# 94 "data/scripts/pokemon_training.pory"

# 95 "data/scripts/pokemon_training.pory"
PokemonTraining_EventScript_NoMoney::
# 96 "data/scripts/pokemon_training.pory"
	msgbox PokemonTraining_Text_NoMoney
# 97 "data/scripts/pokemon_training.pory"
	release
# 98 "data/scripts/pokemon_training.pory"
	end
# 99 "data/scripts/pokemon_training.pory"

# 100 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NatureIntro::
# 101 "data/scripts/pokemon_training.pory"
	.string "I can change a POKéMON's stat nature\n"
# 102 "data/scripts/pokemon_training.pory"
	.string "or ability for ¥50 per change.\p"
# 103 "data/scripts/pokemon_training.pory"
	.string "Its original nature stays the same\n"
# 104 "data/scripts/pokemon_training.pory"
	.string "for breeding.\p"
# 105 "data/scripts/pokemon_training.pory"
	.string "SYNCHRONIZE uses the stat nature, too.\n"
# 106 "data/scripts/pokemon_training.pory"
	.string "Would you like my help?$"
# 107 "data/scripts/pokemon_training.pory"

# 108 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_IvIntro::
# 109 "data/scripts/pokemon_training.pory"
	.string "I offer IV training for ¥50 per\n"
# 110 "data/scripts/pokemon_training.pory"
	.string "stat. Each chosen IV becomes 31.\p"
# 111 "data/scripts/pokemon_training.pory"
	.string "I can also change HIDDEN POWER's\n"
# 112 "data/scripts/pokemon_training.pory"
	.string "type for ¥50, keeping your IVs.\p"
# 113 "data/scripts/pokemon_training.pory"
	.string "IVs still determine its power.\n"
# 114 "data/scripts/pokemon_training.pory"
	.string "Shall we begin?$"
# 115 "data/scripts/pokemon_training.pory"

# 116 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseNature::
# 117 "data/scripts/pokemon_training.pory"
	.string "Original nature: {STR_VAR_2}\n"
# 118 "data/scripts/pokemon_training.pory"
	.string "Current stat nature: {STR_VAR_3}\p"
# 119 "data/scripts/pokemon_training.pory"
	.string "Choose {STR_VAR_1}'s stat nature.\n"
# 120 "data/scripts/pokemon_training.pory"
	.string "Use UP and DOWN to scroll the list.$"
# 121 "data/scripts/pokemon_training.pory"

# 122 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseIv::
# 123 "data/scripts/pokemon_training.pory"
	.string "Choose an IV for {STR_VAR_1}.\n"
# 124 "data/scripts/pokemon_training.pory"
	.string "MAX stats won't cost you anything.$"
# 125 "data/scripts/pokemon_training.pory"

# 126 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseAbility::
# 127 "data/scripts/pokemon_training.pory"
	.string "Current ability: {STR_VAR_2}\p"
# 128 "data/scripts/pokemon_training.pory"
	.string "Choose {STR_VAR_1}'s ability.\n"
# 129 "data/scripts/pokemon_training.pory"
	.string "Only its species' abilities are listed.$"
# 130 "data/scripts/pokemon_training.pory"

# 131 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_ChooseHiddenPower::
# 132 "data/scripts/pokemon_training.pory"
	.string "Current HIDDEN POWER: {STR_VAR_2}\p"
# 133 "data/scripts/pokemon_training.pory"
	.string "Choose {STR_VAR_1}'s new type.\n"
# 134 "data/scripts/pokemon_training.pory"
	.string "This overrides its IV-based type.$"
# 135 "data/scripts/pokemon_training.pory"

# 136 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Confirm::
# 137 "data/scripts/pokemon_training.pory"
	.string "{STR_VAR_1}: {STR_VAR_3}\n"
# 138 "data/scripts/pokemon_training.pory"
	.string "The total is ¥{STR_VAR_2}. Proceed?$"
# 139 "data/scripts/pokemon_training.pory"

# 140 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Done::
# 141 "data/scripts/pokemon_training.pory"
	.string "All done!\n"
# 142 "data/scripts/pokemon_training.pory"
	.string "Take good care of {STR_VAR_1}!$"
# 143 "data/scripts/pokemon_training.pory"

# 144 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NoChange::
# 145 "data/scripts/pokemon_training.pory"
	.string "That choice needs no change.\n"
# 146 "data/scripts/pokemon_training.pory"
	.string "You haven't been charged.$"
# 147 "data/scripts/pokemon_training.pory"

# 148 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Invalid::
# 149 "data/scripts/pokemon_training.pory"
	.string "I can only train a POKéMON,\n"
# 150 "data/scripts/pokemon_training.pory"
	.string "not an EGG.$"
# 151 "data/scripts/pokemon_training.pory"

# 152 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_NoMoney::
# 153 "data/scripts/pokemon_training.pory"
	.string "You don't have enough money.\n"
# 154 "data/scripts/pokemon_training.pory"
	.string "Nothing has been changed.$"
# 155 "data/scripts/pokemon_training.pory"

# 156 "data/scripts/pokemon_training.pory"
PokemonTraining_Text_Goodbye::
# 157 "data/scripts/pokemon_training.pory"
	.string "Come back whenever you like!$"

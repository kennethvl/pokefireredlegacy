EventScript_UseSurf::
	goto_if_questlog EventScript_UseSurfEnd
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_UseSurfEnd
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox Text_WantToSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_UseSurfRelease
	msgbox Text_UsedSurf
EventScript_StartSurf:
	dofieldeffect FLDEFF_USE_SURF
EventScript_UseSurfRelease:
	releaseall
EventScript_UseSurfEnd:
	end

EventScript_AutoSurf::
	goto_if_questlog EventScript_UseSurfEnd
	setfieldeffectargument 0, PARTY_SIZE
	lockall
	goto EventScript_StartSurf

EventScript_CurrentTooFast::
	lockall
	msgbox Text_CurrentTooFast
	releaseall
	end

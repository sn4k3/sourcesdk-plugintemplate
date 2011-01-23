//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#include "includes/default.h"
#include PLUGIN_MAIN_INCLUDE


PLUGIN_TIMERS_CLASS::PLUGIN_TIMERS_CLASS(){}
PLUGIN_TIMERS_CLASS::~PLUGIN_TIMERS_CLASS(){}

// Global timers callback, all timers triggers came to here
bool PLUGIN_TIMERS_CLASS::TimerCallback(const char *sender, void *Param0, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4)
{
	LIB_TIMERINFO_CLASS *timer = VAR_LIB_TIMER->GetTimer(sender);	// Timer class, NULL if not alive (Repeats ends)
	// From here treat other arguments as you need.
	// You can create your own functions and redirect from here
	if(LIB_STRING_CLASS::FStrEq(sender, "test"))
	{
		const char *arg1 = (const char *)Param0; // I know Param0 is a const char*, so lets convert it
		
		Msg("Lets see what plugin says: %s\n", arg1);
		if(timer != NULL)
			Msg("Repeats: %u of %u\n", timer->repeatsCount, timer->repeats);
		else
			Msg("Good bye for now.\n");
		return true;
	}
	if(LIB_STRING_CLASS::FStrEq(sender, "countdown"))
	{
		// Note: we simply can use repeats, but i will show you, now to use dynamic arguments.
		Msg("CountDown: %i\n", Param4);
		if(timer)
			timer->SetArguments(NULL, NULL, NULL, Param4-1);
		else
			Msg("COUNTDOWN ENDS.\n");
		return true;
	}
	return false;
}

PLUGIN_TIMERS_CLASS *VAR_PLUGIN_TIMERS = NULL;
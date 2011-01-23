#ifndef PLUGIN_TIMERS_H
#define PLUGIN_TIMERS_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

//=================================================================================
// Defines
//=================================================================================
#define PLUGIN_TIMERS_VERSION "1.0"
#define PLUGIN_TIMERS_CLASS CPluginTimers

//=================================================================================
// Class
//=================================================================================
class PLUGIN_TIMERS_CLASS : public LIB_TIMERIMPL_CLASS
{
public:
	PLUGIN_TIMERS_CLASS();
	~PLUGIN_TIMERS_CLASS();

	virtual bool TimerCallback(const char *sender, void *Param1, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4);
};

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_TIMERS_CLASS *VAR_PLUGIN_TIMERS;

#endif
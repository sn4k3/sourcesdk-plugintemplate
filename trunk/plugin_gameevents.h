#ifndef PLUGIN_GAMEEVENTS
#define PLUGIN_GAMEEVENTS
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
#define PLUGIN_GAMEEVENTS_VERSION "1.0"
#define PLUGIN_GAMEEVENTS_CLASS CPluginGameEvents

//=================================================================================
// Class
//=================================================================================
class PLUGIN_GAMEEVENTS_CLASS : public IGameEventListener2
{
public:
	PLUGIN_GAMEEVENTS_CLASS();
	~PLUGIN_GAMEEVENTS_CLASS();

	// IGameEventListener Interface
	virtual void FireGameEvent(IGameEvent * event);

	// Handle menuselect from MenuLib
	virtual void FireMenuHandle(const char *menu, edict_t *pEntity, unsigned int option, unsigned int page, void *arg);
};

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_GAMEEVENTS_CLASS *VAR_PLUGIN_GAMEEVENTS;

#endif
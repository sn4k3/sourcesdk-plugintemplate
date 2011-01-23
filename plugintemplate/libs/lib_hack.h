#ifndef LIB_HACK_H
#define LIB_HACK_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#include "plugin_hack.h"

//=================================================================================
// Defines
//=================================================================================
#define LIB_HACK_VERSION "1.0"
#define LIB_HACK_CLASS CHackLib

//=================================================================================
// Class
//=================================================================================
class LIB_HACK_CLASS
{
public:
	// Constructor
	LIB_HACK_CLASS();

	// Destructor
	~LIB_HACK_CLASS();

	// Return current game player
	inline const char *GetGamePlayer(){ return GamePlayer; }


public:
	// Props
	PLUGIN_PROP_CLASS *Props;

	// Virtual functions
	PLUGIN_VFUNCS_CLASS *VFuncs;

	// Sigscan
	PLUGIN_SIGSCAN_CLASS *SigScan;

	// Common game config
	KeyValues *commonConfig;

	// Game config
	KeyValues *gameConfig;

private:
	// Current gameplayer
	const char *GamePlayer;
};

//=================================================================================
// Extern global variable
//=================================================================================
extern LIB_HACK_CLASS *VAR_LIB_HACK;


#endif
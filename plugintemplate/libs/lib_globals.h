#ifndef LIB_GLOBALS_H
#define LIB_GLOBALS_H
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
#define LIB_GLOBALS_VERSION "1.0"
#define LIB_GLOBALS_CLASS CGlobalsLib

class LIB_GLOBALS_CLASS
{
public:
	// Constructor
	LIB_GLOBALS_CLASS();

	// Destructor
	~LIB_GLOBALS_CLASS();

	// Set all variables to NULL or 0
	void Invalidate();

	// Complete path to game folder
	char				szGameDir[1024];

	// Game folder ONLY (eg. cstrike)
	const		char	*szGameFolder;

	// Game name (eg. Counter-Strike: Source) from gamedll
	const		char	*szGameName;

	// Current map
	const		char	*szCurrentMap;

	// Last map played, NULL if server dont change map yet
	const		char	*szOldMap;

	// Is plugin loaded? always, true i think lol
	bool				bPluginLoaded;

	// Number of times, the server was change the levels
	unsigned	int		iLevelChanges;

	// Max clients server can accept
	unsigned	int		iMaxclients;
};

#endif
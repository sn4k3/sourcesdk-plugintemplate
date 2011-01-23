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
// Includes
//=================================================================================
#include "includes/default.h"


//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_HACK_CLASS::LIB_HACK_CLASS()
{
	Props = NULL;
	VFuncs = NULL;
	SigScan = NULL;
	commonConfig = NULL;
	gameConfig = NULL;
	GamePlayer = "CSSPlayer"; // Most used game cstrike
#ifdef PLUGIN_USE_GAMECONFIGS
	if(PLUGIN_USE_GAMECONFIGS)
	{
		char commonConfigFile[MAX_STR_LEN], gameConfigFile[MAX_STR_LEN];
		LIB_STRING_CLASS::UTIL_Format(commonConfigFile, MAX_STR_LEN, ""PLUGIN_DIR_GAMECONFIGS""PLUGIN_FILE_GAMECONFIGS_FORMAT"", "common");
		LIB_STRING_CLASS::UTIL_Format(gameConfigFile, MAX_STR_LEN, ""PLUGIN_DIR_GAMECONFIGS""PLUGIN_FILE_GAMECONFIGS_FORMAT"", VAR_PLUGIN_GLOBALS->szGameFolder);
		if(commonConfigFile)
		{
			if(VAR_IFACE_FILESYSTEM->FileExists(commonConfigFile, "MOD"))
			{
				commonConfig = new KeyValues("common");
				commonConfig->LoadFromFile(VAR_IFACE_FILESYSTEM, commonConfigFile, "MOD");
			}
		}
		if(gameConfigFile)
		{
			if(VAR_IFACE_FILESYSTEM->FileExists(gameConfigFile, "MOD"))
			{
				gameConfig = new KeyValues(VAR_PLUGIN_GLOBALS->szGameName);
				gameConfig->LoadFromFile(VAR_IFACE_FILESYSTEM, gameConfigFile, "MOD");
				GamePlayer = gameConfig->GetString("GamePlayer", "CSSPlayer");
			}
		}
	}
#endif

#ifdef USE_LIB_SOUND
	if(commonConfig)
		VAR_LIB_SOUND->Load(commonConfig->FindKey("Sounds"));
	if(gameConfig)
		VAR_LIB_SOUND->Load(gameConfig->FindKey("Sounds"));
#endif
#ifdef USE_LIB_PROP
	Props = new PLUGIN_PROP_CLASS();
	if(commonConfig)
		Props->Load(commonConfig->FindKey("Props"));
	if(gameConfig)
		Props->Load(gameConfig->FindKey("Props"));
#endif
#ifdef USE_LIB_VFUNCS
	VFuncs = new PLUGIN_VFUNCS_CLASS();
	if(commonConfig)
		VFuncs->Load(commonConfig->FindKey("VFuncs"));
	if(gameConfig)
		VFuncs->Load(gameConfig->FindKey("VFuncs"));
	VFuncs->GamePlayer = GamePlayer;
#endif
#ifdef USE_LIB_SIGSCAN
	SigScan = new PLUGIN_SIGSCAN_CLASS();
	if(commonConfig)
		SigScan->Load(commonConfig->FindKey("SigScan"));
	if(gameConfig)
		SigScan->Load(gameConfig->FindKey("SigScan"));
	SigScan->GamePlayer = GamePlayer;
#endif
}
LIB_HACK_CLASS::~LIB_HACK_CLASS()
{
	if(commonConfig)
		commonConfig->deleteThis();
	if(gameConfig)
		gameConfig->deleteThis();

	if(Props)
		Props->~PLUGIN_PROP_CLASS();
	if(VFuncs)
		VFuncs->~PLUGIN_VFUNCS_CLASS();
	if(SigScan)
		SigScan->~PLUGIN_SIGSCAN_CLASS();
}

LIB_HACK_CLASS *VAR_LIB_HACK = NULL;
#ifndef PLUGIN_CONVARS_H
#define PLUGIN_CONVARS_H
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
#define PLUGIN_CONVARS_VERSION "1.0"
#define PLUGIN_CONVARS_CLASS CPluginConVars

//=================================================================================
// Class
//=================================================================================
class PLUGIN_CONVARS_CLASS : public LIB_CONVAR_CLASS
{
public:
	PLUGIN_CONVARS_CLASS();
	~PLUGIN_CONVARS_CLASS();
	
	//virtual void Dump(bool dumpConvars = true, bool dumpConcommands = true);
	static CONVAR_CALLBACK(ConVarCallback);
};

//=================================================================================
// Extern all convars here, PLUGIN_EXTERN_CONVAR
//=================================================================================
PLUGIN_EXTERN_CONVAR(version)
PLUGIN_EXTERN_CONVAR(build_timestamp)
PLUGIN_EXTERN_CONVAR(build_date)
PLUGIN_EXTERN_CONVAR(build_time)

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_CONVARS_CLASS *VAR_PLUGIN_CONVARS;


#endif
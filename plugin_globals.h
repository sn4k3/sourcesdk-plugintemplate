#ifndef PLUGIN_GLOBALS_H
#define PLUGIN_GLOBALS_H
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
#define PLUGIN_GLOBALS_VERSION "1.0"
#define PLUGIN_GLOBALS_CLASS CPluginGlobals

//=================================================================================
// Externs, make globals here
//=================================================================================
extern const char *plugin_version;
extern const char *plugin_build_date;

//=================================================================================
// Class
//=================================================================================
class PLUGIN_GLOBALS_CLASS : public LIB_GLOBALS_CLASS
{
public:
	static bool InitInterfaces(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
};

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_GLOBALS_CLASS *VAR_PLUGIN_GLOBALS;

#endif
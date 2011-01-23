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


const char *plugin_version = PLUGIN_VERSION;
const char *pugin_build_date = __DATE__;

bool PLUGIN_GLOBALS_CLASS::InitInterfaces(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	return true;
}

//=================================================================================
// Extern global variable, never touch
//=================================================================================
PLUGIN_GLOBALS_CLASS *VAR_PLUGIN_GLOBALS = NULL;
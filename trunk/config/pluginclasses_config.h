#ifndef PLUGINCLASSES_CONFIG_H
#define PLUGINCLASSES_CONFIG_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
// Following Constans, define plugin classes and thier variables

// Define plugin classes variables to use on plugin
// Never change define name
#define VAR_PLUGIN_PYTHON		gpPython
#define VAR_PLUGIN_GLOBALS		gpGlobal
#define VAR_PLUGIN_CONVARS		gpConVars 
#define VAR_PLUGIN_TIMERS		gpTimers
//#define VAR_PLUGIN_PLAYER		gpPlayer
#define VAR_PLUGIN_GAMEEVENTS	gpGameEvents

// Short and nice typed re-defenitions from libraries variables
// You can change define name to your prefered name
// v = var, p = plugin
#define vpPython				VAR_PLUGIN_PYTHON
#define vpGlobal				VAR_PLUGIN_GLOBALS
#define vpConVars				VAR_PLUGIN_CONVARS
#define vpTimers				VAR_PLUGIN_TIMERS
//#define vpPlayer				VAR_PLUGIN_PLAYER
#define vpGameEvents			VAR_PLUGIN_GAMEEVENTS

#endif
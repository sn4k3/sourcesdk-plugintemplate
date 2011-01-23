#ifndef PLUGIN_CONFIG_H
#define PLUGIN_CONFIG_H
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
// Following Constans, define plugin information
//=================================================================================
// Two above defines goes to serverplugin_main
// Your main plugin interface
#define PLUGIN_CLASS	CPluginTemplate
#define PLUGIN_VAR		g_PluginTemplate


#define PLUGIN_MAIN_INCLUDE "includes/lotsofstuff.h"

#define PLUGIN_ACTOR		"Sn4k3"							// Set plugin actor/developer
#define PLUGIN_CONTACT		"Tiago_caza@hotmail.com"		// Set your contact if you want, NULL or comment to disable
#define PLUGIN_URL			"http://code.google.com/p/sourcesdk-plugintemplate/"		// Set your plugin URL/Forum/WebSite, NULL or comment to disable
#define PLUGIN_LICENSE		"http://creativecommons.org/licenses/by-nc-sa/3.0/us/"			// Set your plugin license // A License List Can Be Founded At: http://www.gnu.org/philosophy/license-list.html
#define PLUGIN_NAME			"Plugin Template"				// Set your plugin name
#define PLUGIN_SHORTNAME	"PT"							// Set your plugin shortname
#define PLUGIN_PREFIX		"pt_"							// Prefix used in ConVars, ConCommands, and other defenitions
#define PLUGIN_MSG_PREFIX	"PluginTemplate: "				// Prefix to add in Msg, Logs, Chat, etc
#define PLUGIN_DESCRIPTION	""PLUGIN_NAME", Version: "PLUGIN_VERSION", By "PLUGIN_ACTOR"" // No Touch, plugin_print
#define PLUGIN_ABOUT		"Provide a server plugin template to codders"	// About your plugin, what it does
#define PLUGIN_VERSION		"1.0"							// Set your plugin version
#define PLUGIN_USE_SOURCEHOOK								// If you use sourcehook in your VSP plugin, you must leave this line, no effect under MMS plugins. Otherwise comment this line.
#define PLUGIN_SOURCEHOOK_ID 1024							// A unique integer that identifies the library using SourceHook. This is used for removing all hooks a library is using.
#define PLUGIN_BUILDDATE	__DATE__						// When plugin got compiled for last time

//=================================================================================
// Plugin data paths
// Where we store plugin data
// All paths must end with /
//=================================================================================
#define PLUGIN_DIR				"addons/plugintemplate/"		// Your plugin data dir, to store files, events, data, admins, databases, etc
#define PLUGIN_DIR_BIN			""PLUGIN_DIR"bin/"				// Your plugin bin folder, where binnary files are (most common: bin)
#define PLUGIN_DIR_DATA			""PLUGIN_DIR"data/"				// Your plugin data folder, where we save some files like admins, events, plugin settings ...
#define PLUGIN_DIR_CFG			""PLUGIN_DIR"cfg/"				// Your plugin cfg folder, where to store configs
#define PLUGIN_DIR_GAMECONFIGS	""PLUGIN_DIR"games/"			// Folder where to load game configs, VFuncs, sigscan, props

//=================================================================================
// Game Configs
// Where we store VFuncs, sigscan, props, ....
//=================================================================================
#define PLUGIN_USE_GAMECONFIGS			true					// Allow plugin load common and game configs, false will cause vfuncs and sigscan not work, if you dont use them set to false or comment
#define PLUGIN_FILE_GAMECONFIGS_FORMAT "%s.txt"					// Your file format, %s will be replace by the game name, ie. "game.%s.txt"

// Plugin header message, used in messages, logs, etc
// Use empty "" if you dont wana use.
#define PLUGIN_HEADER \
"#########################\n\
#    Plugin Template    #\n\
#########################\n"


//=================================================================================
// ConVars and ConCommands prefix
//=================================================================================
// variable prefix
#define PLUGIN_CONVAR_PREFIX			cvar_pt_
#define PLUGIN_CONCOMMAND_PREFIX		cmd_pt_
// ConVars names
#define PLUGIN_CONVAR_NAME_PREFIX		"pt_"
#define PLUGIN_CONCOMMAND_NAME_PREFIX	"pt_"


#endif
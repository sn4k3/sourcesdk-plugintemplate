#ifndef LIBS_CONFIG_H
#define LIBS_CONFIG_H
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
// Following Constans, define what libs to use on the plugin and thier variables
// Allow disable or enable NO-STATIC Libraries from plugin.
// They will be always avaliable to use, but aren't pre defenied by plugintemplate
// Never change define name
// Comment to disable
//=================================================================================
#define USE_LIB_DOWNLOAD
#define USE_LIB_SOUND
#define USE_LIB_PLAYERMNGR
#define USE_LIB_TIMER
#define USE_LIB_PROFILING
#define USE_LIB_ADMIN
#define USE_LIB_EASYADMIN
#define USE_LIB_LANG
#define USE_LIB_MENU
#define USE_LIB_PROP
#define USE_LIB_VFUNCS
#define USE_LIB_SIGSCAN

//=================================================================================
// Define libraries variables to use on plugin
// Never change define name
// l = library
//=================================================================================
#define VAR_LIB_DOWNLOAD	glDownload
#define VAR_LIB_SOUND		glSound
#define VAR_LIB_PLAYERMNGR	glPlayerMngr
#define VAR_LIB_TIMER		glTimer
#define VAR_LIB_PROFILING	glProfiling
#define VAR_LIB_ADMIN		glAdmin
#define VAR_LIB_EASYADMIN	glEasyAdmin
#define VAR_LIB_LANG		glLang
#define VAR_LIB_MENU		glMenu
#define VAR_LIB_HACK		glHack
// Do not touch this three
#define VAR_LIB_PROP		VAR_LIB_HACK->Props
#define VAR_LIB_VFUNCS		VAR_LIB_HACK->VFuncs
#define VAR_LIB_SIGSCAN		VAR_LIB_HACK->SigScan

//=================================================================================
// Short and nice typed re-defenitions from libraries variables
// You can change define name to your prefered name
// v = var, l = library
//=================================================================================
#define vlDownload			VAR_LIB_DOWNLOAD
#define vlSound				VAR_LIB_SOUND
#define vlPlayerMngr		VAR_LIB_PLAYERMNGR
#define vlTimer				VAR_LIB_TIMER
#define vlProfiling			VAR_LIB_PROFILING
#define vlAdmin				VAR_LIB_ADMIN
#define vlEasyAdmin			VAR_LIB_EASYADMIN
#define vlLang				VAR_LIB_LANG
#define vlMenu				VAR_LIB_MENU
#define vlHack				VAR_LIB_HACK
#define vlProp				VAR_LIB_PROP
#define vlVFuncs			VAR_LIB_VFUNCS
#define vlVSigscan			VAR_LIB_SIGSCAN

//=================================================================================
// Settings
//=================================================================================
//=================================================================================
// Admin Lib
//=================================================================================
// Path to file where to store admins/clients
// Set to NULL if you want load file manualy
#define SETTING_LIB_ADMIN_CLIENTS_FILE ""PLUGIN_DIR_DATA""PLUGIN_PREFIX"clients.txt"

//=================================================================================
// Easy Admin Lib
//=================================================================================
// Path to file where to store admins/clients
// Set to NULL if you want load file manualy
#define SETTING_LIB_EASYADMIN_FILE ""PLUGIN_DIR_DATA""PLUGIN_PREFIX"simpleadmins.txt"

// If you want to automatic load admins from file, you must choose from from file, keyvalues or ini
// 0 = file, 1 = keyvalues, 2 = ini file
#define SETTING_LIB_EASYADMIN_LOADFROM 0

// Auto save admins to file if server shutsdown or plugin gets unloaded
// Use true or false
#define SETTING_LIB_EASYADMIN_AUTOSAVE true

//=================================================================================
// Lang Lib
//=================================================================================
// Files WildCard, search for files
// ie. *.phrases.txt
#define SETTING_LIB_LANG_WILDCARD "*.*"

// Directory to search for translation files
// Use a full path to file, to use a single file instead ie. ""PLUGIN_DIR"translations.txt"
#define SETTING_LIB_LANG_DIR ""PLUGIN_DIR"translations/"

#endif
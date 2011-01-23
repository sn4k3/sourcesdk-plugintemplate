#ifndef LIB_CONVAR_H
#define LIB_CONVAR_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_CONVAR_VERSION "1.0"
#define LIB_CONVAR_CLASS CConvarLib

#define PLUGIN_CONVAR0(name, defaultvalue) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, 0);

#define PLUGIN_CONVAR1(name, defaultvalue, flags) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, flags);

#define PLUGIN_CONVAR2(name, defaultvalue, flags, helpstring) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, flags, helpstring);

#define PLUGIN_CONVAR3(name, defaultvalue, flags, helpstring, bMin, fMin, bMax, fMax) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, flags, helpstring, bMin, fMin, bMax, fMax);

#define PLUGIN_CONVAR4(name, defaultvalue, flags, helpstring, callback) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, flags, helpstring, callback);

#define PLUGIN_CONVAR5(name, defaultvalue, flags, helpstring, bMin, fMin, bMax, fMax, callback) \
	ConVar PLUGIN_CONVAR_PREFIX##name(""PLUGIN_CONVAR_NAME_PREFIX""#name"", defaultvalue, flags, helpstring, bMin, fMin, bMax, fMax, FnChangeCallback_t callback);

#define PLUGIN_EXTERN_CONVAR(name) extern ConVar PLUGIN_CONVAR_PREFIX##name;
#define PLUGIN_CONVAR(name) PLUGIN_CONVAR_PREFIX##name;

class LIB_CONVAR_CLASS
{
public:	
	LIB_CONVAR_CLASS();
	~LIB_CONVAR_CLASS();

	// Find a ConVar and return it.
	// NULL if doesn't exists.
	ConVar *GetConvar(const char *name);

	// Keep a ConVar in a list, to fast access
	// i.e: sv_cheats
	bool AddOutsideConvar(const char *name);

	// Remove an convar from outside list.
	bool RemoveOutsideConvar(const char *name);

	// Get an convar from outside list.
	ConVar *GetOutsideConvar(const char *name);

	// Dump all variables to console
	virtual void Print(bool dumpConvars = true, bool dumpConcommands = true);
	 
	// Collection of ConVars.
	// Keep this for your plugin convars only
	CUtlVector<ConVar*> convars;

	// Collection of ConCommands.
	// Keep this for your plugin convars only
	CUtlVector<ConCommand*> concommands;

	CUtlVector<ConVar *> outsideConvars;
};

#endif
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
// Usefull macro
//=================================================================================
#define KEEP_CONVAR(name)\
	if(LIB_STRING_CLASS::FStrEq(varname,""PLUGIN_CONVAR_NAME_PREFIX""name""))\
	{\
		if(!LIB_STRING_CLASS::FStrEq(convar->GetDefault(), convar->GetString()))\
			convar->SetValue(convar->GetDefault());\
		return;\
	}

//=================================================================================
// Your plugin convars
// You should extern the convars in header
//=================================================================================
PLUGIN_CONVAR4(version, PLUGIN_VERSION, FCVAR_SPONLY | FCVAR_REPLICATED | FCVAR_NOTIFY, ""PLUGIN_NAME" Version.", &PLUGIN_CONVARS_CLASS::ConVarCallback)
PLUGIN_CONVAR4(build_timestamp, __TIMESTAMP__, FCVAR_SPONLY | FCVAR_REPLICATED | FCVAR_NOTIFY, "The date and time this binary was built.", &PLUGIN_CONVARS_CLASS::ConVarCallback)
PLUGIN_CONVAR4(build_date, __DATE__, FCVAR_SPONLY | FCVAR_REPLICATED | FCVAR_NOTIFY, "The date this binary was built.", &PLUGIN_CONVARS_CLASS::ConVarCallback)
PLUGIN_CONVAR4(build_time, __TIME__, FCVAR_SPONLY | FCVAR_REPLICATED | FCVAR_NOTIFY, "The time this binary was built.", &PLUGIN_CONVARS_CLASS::ConVarCallback)

//=================================================================================
// Class
// Constructor / Destructor
//=================================================================================
// Constructor
PLUGIN_CONVARS_CLASS::PLUGIN_CONVARS_CLASS()
{}
// Destructor
PLUGIN_CONVARS_CLASS::~PLUGIN_CONVARS_CLASS()
{
}

// Dump all variables to console
/*
void PLUGIN_CONVARS_CLASS::Print(bool dumpConvars, bool dumpConcommands)
{	Virtual function, uncomment to make your own Dump } */

//=================================================================================
// Simple static ConVar callback, you can use it for your vars
//=================================================================================
CONVAR_CALLBACK(PLUGIN_CONVARS_CLASS::ConVarCallback)
{
	const char *varname = var->GetName();
	ConVar *convar = VAR_IFACE_ICVAR->FindVar(varname);
	if(!convar)
		return;

	//KEEP_CONVAR dont let cvar change from a different value than default, 'varname' used
	KEEP_CONVAR("version")
	KEEP_CONVAR("build_timestamp")
	KEEP_CONVAR("build_date")
	KEEP_CONVAR("build_time")
}

//=================================================================================
// Extern global variable, never touch
//=================================================================================
PLUGIN_CONVARS_CLASS *VAR_PLUGIN_CONVARS = NULL;
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
//===================================================================================
//=================================================================================
// Includes
//=================================================================================
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_convar.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_CONVAR_CLASS::LIB_CONVAR_CLASS(){}
LIB_CONVAR_CLASS::~LIB_CONVAR_CLASS()
{
	convars.RemoveAll();
	concommands.RemoveAll();
	outsideConvars.RemoveAll();
}

// Find a ConVar and return it.
// NULL if doesn't exists.
ConVar *LIB_CONVAR_CLASS::GetConvar(const char *name)
{
	return VAR_IFACE_ICVAR->FindVar(name);
}

// Keep a ConVar in a list, to fast access
// i.e: sv_cheats
bool LIB_CONVAR_CLASS::AddOutsideConvar(const char *name)
{
	ConVar *var = VAR_IFACE_ICVAR->FindVar(name);
	if(!var)
		return false;
	if(outsideConvars.Find(var))
		return true;
	outsideConvars.AddToTail(var);
	return true;
}

// Remove an convar from outside list.
bool LIB_CONVAR_CLASS::RemoveOutsideConvar(const char *name)
{
	FOR_EACH_VEC(outsideConvars, i)
	{
		if(LIB_STRING_CLASS::FStrEq(outsideConvars[i]->GetName(), name))
		{
			outsideConvars.Remove(i);
			return true;
		}
	}
	return false;
}

// Get an convar from outside list.
ConVar *LIB_CONVAR_CLASS::GetOutsideConvar(const char *name)
{
	FOR_EACH_VEC(outsideConvars, i)
		if(LIB_STRING_CLASS::FStrEq(outsideConvars[i]->GetName(), name))
			return outsideConvars[i];
	return NULL;
}


// Dump all variables to console
void LIB_CONVAR_CLASS::Print(bool dumpConvars /*= true*/, bool dumpConcommands /*= true*/)
{
	Msg("\n"PLUGIN_HEADER"Show the list of convars/concommads for "PLUGIN_NAME":\n_____________________\n");
	if(dumpConvars)
	{
		unsigned int nconvar = convars.Count();
		Msg("  * Total ConVars: %u\n", nconvar);
		for(unsigned i = 0; i < nconvar; i++)
		{
			ConVar *var = convars[i];
			Msg("%s = \"%s\" : %s\n", var->GetName(), var->GetString(), var->GetHelpText());
		}
	}
	if(dumpConcommands)
	{
		unsigned int nconcommand = concommands.Count();
		Msg("  * Total ConCommads: %u\n", nconcommand);
		for(unsigned i = 0; i < nconcommand; i++)
		{
			ConCommand *cmd = concommands[i];
			Msg("%s : %s\n", cmd->GetName(), cmd->GetHelpText());
		}
	}
	Msg("_____________________\n \n");
}
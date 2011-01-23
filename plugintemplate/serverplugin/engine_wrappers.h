/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Metamod:Source Sample Plugin
 * Written by AlliedModders LLC.
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from 
 * the use of this software.
 *
 * This sample plugin is public domain.
 */

#ifndef _INCLUDE_SOURCE_ENGINE_WRAPPERS_
#define _INCLUDE_SOURCE_ENGINE_WRAPPERS_

#include <eiface.h>
#include "convar.h"

extern IVEngineServer *engine;
extern CGlobalVars *VAR_IFACE_GLOBALVARS;

#if SOURCE_ENGINE == SE_EPISODEONE && defined METAMOD_PLAPI_VERSION
#error "Metamod:Source 1.6 API is not supported on the old engine."
#endif

//#define ENGINE_CALL(func) SH_CALL(engine, &IVEngineServer::func)

/**
 * Wrap some API calls for legacy MM:S.
 */
#if !defined METAMOD_PLAPI_VERSION
#define GetEngineFactory engineFactory
#define GetServerFactory serverFactory
#define MM_Format snprintf
#define	GetCGlobals	pGlobals
#else
#define MM_Format g_SMAPI->Format
#endif

#if SOURCE_ENGINE <= SE_DARKMESSIAH
// Callbacks for ConVars
#define CONVAR_CALLBACK(_funcname) \
		void _funcname(ConVar *var, const char *pOldValue)

#define CONVAR_CALLBACK_REF(_funcname) \
	(FnChangeCallback_t) _funcname

// Fix StringTables dont require a bool param at begin
#define DOWNLOADABLES_ADDSTRING(_value, _length) AddString(_value, _length)

#define ENGINE_ClientCommand(_pEntity) ClientCommand(edict_t * _pEntity)
/**
 * Wrap the CCommand class so our code looks the same on all engines.
 */
class CCommand
{
public:
	const char *operator[](int index)
	{
		return Arg(index);
	}
	const char *ArgS()
	{
		return VAR_IFACE_ENGINE->Cmd_Args();
	}
	int ArgC()
	{
		return VAR_IFACE_ENGINE->Cmd_Argc();
	}

	const char *Arg(int index)
	{
		return VAR_IFACE_ENGINE->Cmd_Argv(index);
	}
};

extern CCommand args;

#define CVAR_INTERFACE_VERSION VENGINE_CVAR_INTERFACE_VERSION
#else
#define CONVAR_CALLBACK(funcname) \
		void funcname(IConVar *var, const char *pOldValue, float flOldValue)

#define CONVAR_CALLBACK_REF(_funcname) \
		_funcname


#define DOWNLOADABLES_ADDSTRING(_value, _length) AddString(true, _value, _length)

#define ENGINE_ClientCommand(_pEntity) ClientCommand(edict_t * _pEntity, const CCommand &args)
#endif

/**
 * Left 4 Dead engine removed these from IVEngineServer.
 */
#if SOURCE_ENGINE >= SE_LEFT4DEAD

inline int IndexOfEdict(const edict_t *pEdict)
{
	return (int)(pEdict - VAR_IFACE_GLOBALVARS->baseEdict);
}
inline edict_t *PEntityOfEntIndex(int iEntIndex)
{
	if (iEntIndex >= 0 && iEntIndex < VAR_IFACE_GLOBALVARS->maxEntities)
	{
		return (edict_t *)(VAR_IFACE_GLOBALVARS->baseEdict + iEntIndex);
	}
	return NULL;
}

#else

inline int IndexOfEdict(const edict_t *pEdict)
{
	return VAR_IFACE_ENGINE->IndexOfEdict(pEdict);
}
inline edict_t *PEntityOfEntIndex(int iEntIndex)
{
	return VAR_IFACE_ENGINE->PEntityOfEntIndex(iEntIndex);
}

#endif

#ifndef DEBUG
inline void DevMsg(const char *pMsg, ...)
{
	MULTIARGS(pMsg);
	Msg(string);
}
#else
inline void DevMsg(const char *pMsg, ...)
{
	// Do Nothing, its not debug.
	return ;
}
#endif

#endif //_INCLUDE_SOURCE_ENGINE_WRAPPERS_


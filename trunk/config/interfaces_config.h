#ifndef INTERFACES_CONFIG_H
#define INTERFACES_CONFIG_H
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
// Disable or enable interfaces from plugin.
// They will be always avaliable to use, but aren't pre defenied by plugintemplate
// Never change define name
// Comment to disable
//=================================================================================

#define USE_IFACE_BOTMANAGER			// (IBotManager)
#define USE_IFACE_VOICESERVER			// (IVoiceServer)
#define USE_IFACE_GAMEEVENTMANAGER		// (IGameEventManager2)
#define USE_IFACE_EFFECTS				// (IEffects)
#define USE_IFACE_ENGINETRACE			// (IEngineTrace)
#define USE_IFACE_SERVERGAMEENTS		// (IServerGameEnts)
#define USE_IFACE_SERVERCLIENTS			// (IServerGameClients)
#define USE_IFACE_RANDOMSTREAM			// (IUniformRandomStream)
#define USE_IFACE_SOUNDS				// (IEngineSound)
#define USE_IFACE_NETWORKSTRINGTABLE	// (NetworkStringTableContainer)


//=================================================================================
// Following Constans, define plugin interfaces variables names
// Methods under [] is where interface got used
//=================================================================================

#define VAR_IFACE_ENGINE				engine					// Must use (IVEngineServer)
#define VAR_IFACE_PLAYERINFOMANAGER		playerinfomanager		// Must use (IPlayerInfoManager)
#define VAR_IFACE_SERVERPLUGINHELPERS	helpers					// Must use (IServerPluginHelpers)
#define VAR_IFACE_ICVAR					icvar					// Must use (ICvar)
#define VAR_IFACE_SERVERGAMEDLL			servergamedll			// Must use (IServerGameDLL)
#define VAR_IFACE_FILESYSTEM			filesystem				// Must use (IFileSystem)
#define VAR_IFACE_GLOBALVARS			gpGlobals				// Must use (CGlobalVars)

#define VAR_IFACE_BOTMANAGER			botmanager				// Optional (IBotManager)
#define VAR_IFACE_VOICESERVER			voiceserver				// Optional (IVoiceServer)
#define VAR_IFACE_GAMEEVENTMANAGER		gameeventmanager		// Optional (IGameEventManager2)
#define VAR_IFACE_EFFECTS				effects					// Optional (IEffects)
#define VAR_IFACE_ENGINETRACE			enginetrace				// Optional (IEngineTrace)
#define VAR_IFACE_SERVERGAMEENTS		serverents				// Optional (IServerGameEnts) [GetEntityFromBaseEntity]
#define VAR_IFACE_SERVERCLIENTS			serverclients			// Optional (IServerGameClients) [GetPlayerStatefromEdict, metamod plugin hooks]
#define VAR_IFACE_RANDOMSTREAM			randomStr				// Optional (IUniformRandomStream) [GetEntityOfRandPlayer and GetIndexOfRandPlayer]
#define VAR_IFACE_SOUNDS				esounds					// Optional (IEngineSound) [EmitSound, PrecacheSound]
#define VAR_IFACE_NETWORKSTRINGTABLE	networkstringtable		// Optional (NetworkStringTableContainer) [Downloads]


//=================================================================================
// Short and nice typed re-defenitions from interfaces variables
// You can change define name to your prefered name
// v = var, i = interface
//=================================================================================

#define viEngine						VAR_IFACE_ENGINE
#define viPlayerinfomanager				VAR_IFACE_PLAYERINFOMANAGER
#define viHelpers						VAR_IFACE_SERVERPLUGINHELPERS
#define viICvar							VAR_IFACE_ICVAR
#define viServerdll						VAR_IFACE_SERVERGAMEDLL
#define viFilesystem					VAR_IFACE_FILESYSTEM
#define viGlobals						VAR_IFACE_GLOBALVARS

#define viBotmanager					VAR_IFACE_BOTMANAGER
#define viVoiceserver					VAR_IFACE_VOICESERVER
#define viGameeventmanager				VAR_IFACE_GAMEEVENTMANAGER
#define viEffects						VAR_IFACE_EFFECTS
#define viEnginetrace					VAR_IFACE_ENGINETRACE
#define viServerclients					VAR_IFACE_SERVERGAMEENTS
#define viRandomStr						VAR_IFACE_RANDOMSTREAM
#define viEsounds						VAR_IFACE_SOUNDS
#define viNetworkstringtable			VAR_IFACE_NETWORKSTRINGTABLE


#endif
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

// Interfaces from the engine
IVEngineServer					*VAR_IFACE_ENGINE				=	NULL; // helper functions (messaging clients, loading content, making entities, running commands, etc)
IGameEventManager2				*VAR_IFACE_GAMEEVENTMANAGER		=	NULL; // game events interface
IEffects						*VAR_IFACE_EFFECTS				=	NULL;
IPlayerInfoManager				*VAR_IFACE_PLAYERINFOMANAGER	=	NULL; // game dll interface to interact with players
IBotManager						*VAR_IFACE_BOTMANAGER			=	NULL; // game dll interface to interact with bots
IServerPluginHelpers			*VAR_IFACE_SERVERPLUGINHELPERS	=	NULL; // special 3rd party plugin helpers from the engine
IUniformRandomStream			*VAR_IFACE_RANDOMSTREAM			=	NULL; // Random
IFileSystem						*VAR_IFACE_FILESYSTEM			=	NULL; // File I/O
ICvar							*VAR_IFACE_ICVAR				=	NULL; // CVars
IVoiceServer					*VAR_IFACE_VOICESERVER			=	NULL; // Voice server
IEngineTrace					*VAR_IFACE_ENGINETRACE			=	NULL; // Engine trace
IServerGameClients				*VAR_IFACE_SERVERCLIENTS		=	NULL; // Server clients
IServerGameEnts					*VAR_IFACE_SERVERGAMEENTS		=	NULL; // Server entities
INetworkStringTableContainer	*VAR_IFACE_NETWORKSTRINGTABLE	=	NULL; // String tables
INetworkStringTable				*downloadablestable				=	NULL; // Downloads
IServerGameDLL					*VAR_IFACE_GAMESERVERDLL		=	NULL; // Game server dll
IEngineSound					*VAR_IFACE_SOUNDS				=	NULL; // sound

CGlobalVars						*VAR_IFACE_GLOBALVARS			=	NULL; // Globals

#ifdef WIN32
#pragma warning( disable : 4706 ) //C4706: assignment within conditional expression
#endif

#ifdef SOURCEMM
#ifdef SM_HOOK_PLUGINCALLBACK_SERVERACTIVATE
SH_DECL_HOOK3_void(IServerGameDLL, ServerActivate, SH_NOATTRIB, 0, edict_t *, int, int);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_GAMEFRAME
SH_DECL_HOOK1_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool);
#endif
#ifdef USE_IFACE_SERVERCLIENTS
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTACTIVE 
SH_DECL_HOOK2_void(IServerGameClients, ClientActive, SH_NOATTRIB, 0, edict_t *, bool);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTDISCONNECT
SH_DECL_HOOK1_void(IServerGameClients, ClientDisconnect, SH_NOATTRIB, 0, edict_t *);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTPUTINSERVER
SH_DECL_HOOK2_void(IServerGameClients, ClientPutInServer, SH_NOATTRIB, 0, edict_t *, char const *);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_SETCOMMANDCLIENT
SH_DECL_HOOK1_void(IServerGameClients, SetCommandClient, SH_NOATTRIB, 0, int);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTSETTINGSCHANGED
SH_DECL_HOOK1_void(IServerGameClients, ClientSettingsChanged, SH_NOATTRIB, 0, edict_t *);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCONNECT
SH_DECL_HOOK5(IServerGameClients, ClientConnect, SH_NOATTRIB, 0, bool, edict_t *, const char*, const char *, char *, int);
#endif

#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCOMMAND
#if SOURCE_ENGINE >= SE_ORANGEBOX
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *, const CCommand &);
#else
SH_DECL_HOOK1_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, edict_t *);
#endif
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_NETWORKIDVALIDATED
SH_DECL_HOOK2_void(IServerGameClients, NetworkIDValidated, SH_NOATTRIB, 0, const char *, const char *);
#endif
#endif
#endif

/** 
 * Something like this is needed to register cvars/CON_COMMANDs.
 */
class BaseAccessor : public IConCommandBaseAccessor
{
public:
	bool RegisterConCommandBase(ConCommandBase *pCommandBase)
	{
		const char *name = pCommandBase->GetName();
		unsigned int len = strlen(name);
		if(len > 0)
		{
			if(pCommandBase->IsCommand())
			{
				if(LIB_STRING_CLASS::StrLeftEq(name, PLUGIN_CONCOMMAND_NAME_PREFIX))
				{
					//unsigned int prefixlen = strlen(PLUGIN_CONCOMMAND_NAME_PREFIX);
					//prefixedname = CStringLib::SubStr(name, prefixlen, len);
					VAR_PLUGIN_CONVARS->concommands.AddToTail((ConCommand*)pCommandBase);
				}			
			}
			else
			{
				if(LIB_STRING_CLASS::StrLeftEq(name, PLUGIN_CONVAR_NAME_PREFIX))
				{
					//unsigned int prefixlen = strlen(PLUGIN_CONVAR_NAME_PREFIX);
					//prefixedname = CStringLib::SubStr(name, prefixlen, len);
					VAR_PLUGIN_CONVARS->convars.AddToTail((ConVar*)pCommandBase);
				}	
			}
		}
#ifdef SOURCEMM
		/* Always call META_REGCVAR instead of going through the engine. */
		return META_REGCVAR(pCommandBase);
#else
#if SOURCE_ENGINE <= SE_DARKMESSIAH
		pCommandBase->AddFlags( FCVAR_PLUGIN );
#endif
		// Unlink from plugin only list
		pCommandBase->SetNext(NULL);

		//Msg("CONVAR: %s\n", pCommandBase->GetName());
		
		// Link to engine's list instead
#if SOURCE_ENGINE <= SE_DARKMESSIAH
		VAR_IFACE_ICVAR->RegisterConCommandBase( pCommandBase );
#else
		VAR_IFACE_ICVAR->RegisterConCommand( pCommandBase );
#endif
#endif
		return true;
	}
} s_BaseAccessor;

//---------------------------------------------------------------------------------
// Purpose: constructor/destructor
//---------------------------------------------------------------------------------
SERVERPLUGIN_ENGINE_CLASS::SERVERPLUGIN_ENGINE_CLASS()
{
	m_iClientCommandIndex = 0;
}

SERVERPLUGIN_ENGINE_CLASS::~SERVERPLUGIN_ENGINE_CLASS()
{
}

#ifdef SOURCEMM
void SERVERPLUGIN_ENGINE_CLASS::OnVSPListening(IServerPluginCallbacks *iface)
{
	SERVERPLUGIN_CALLBACKS_VAR = iface;
}
/**
 * @brief Called when all plugins have been loaded.  
 *
 * This is called after DLLInit(), and thus the mod has been mostly initialized. 
 * It is also safe to assume that all other (automatically loaded) plugins are now 
 * ready to start interacting, because they are all loaded.
 * MMS ONLY
 */
void SERVERPLUGIN_ENGINE_CLASS::AllPluginsLoaded()
{

}
#endif

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
bool SERVERPLUGIN_ENGINE_CLASS::Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlength, bool late)
#else
bool SERVERPLUGIN_ENGINE_CLASS::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
#endif
{
#ifdef SOURCEMM
	PLUGIN_SAVEVARS();

	CreateInterfaceFn interfaceFactory = ismm->GetEngineFactory();
	CreateInterfaceFn gameServerFactory = ismm->GetServerFactory();
#endif

	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_ENGINE, IVEngineServer, INTERFACEVERSION_VENGINESERVER)
	PLUGIN_GET_INTERFACE_CURRENT(gameServerFactory, VAR_IFACE_PLAYERINFOMANAGER, IPlayerInfoManager, INTERFACEVERSION_PLAYERINFOMANAGER)
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_SERVERPLUGINHELPERS, IServerPluginHelpers, INTERFACEVERSION_ISERVERPLUGINHELPERS)
#if SOURCE_ENGINE <= SE_DARKMESSIAH
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_FILESYSTEM, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_ICVAR, ICvar, CVAR_INTERFACE_VERSION);
#endif
	
#ifdef USE_IFACE_BOTMANAGER
	PLUGIN_GET_INTERFACE_CURRENT(gameServerFactory, VAR_IFACE_BOTMANAGER, IBotManager, INTERFACEVERSION_PLAYERBOTMANAGER);
#endif
#ifdef USE_IFACE_VOICESERVER
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_VOICESERVER, IVoiceServer, INTERFACEVERSION_VOICESERVER);
#endif
#ifdef USE_IFACE_GAMEEVENTMANAGER
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_GAMEEVENTMANAGER, IGameEventManager2, INTERFACEVERSION_GAMEEVENTSMANAGER2)
#endif
#ifdef USE_IFACE_EFFECTS
	PLUGIN_GET_INTERFACE_ANY(gameServerFactory, VAR_IFACE_EFFECTS, IEffects, IEFFECTS_INTERFACE_VERSION)
#endif
#ifdef USE_IFACE_RANDOMSTREAM
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_RANDOMSTREAM, IUniformRandomStream, VENGINE_SERVER_RANDOM_INTERFACE_VERSION)
#endif
#ifdef USE_IFACE_ENGINETRACE
	PLUGIN_GET_INTERFACE_ANY(interfaceFactory, VAR_IFACE_ENGINETRACE, IEngineTrace, INTERFACEVERSION_ENGINETRACE_SERVER)
#endif
#ifdef USE_IFACE_SERVERCLIENTS
	PLUGIN_GET_INTERFACE_ANY(gameServerFactory, VAR_IFACE_SERVERCLIENTS, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS)
#endif
#ifdef USE_IFACE_SERVERGAMEENTS
	PLUGIN_GET_INTERFACE_ANY(gameServerFactory, VAR_IFACE_SERVERGAMEENTS, IServerGameEnts, INTERFACEVERSION_SERVERGAMEENTS)
#endif
	PLUGIN_GET_INTERFACE_ANY(gameServerFactory, VAR_IFACE_GAMESERVERDLL, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL) /*"ServerGameDLL006"*/
#ifdef USE_IFACE_NETWORKSTRINGTABLE
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_NETWORKSTRINGTABLE, INetworkStringTableContainer, INTERFACENAME_NETWORKSTRINGTABLESERVER)
#endif
#ifdef USE_IFACE_SOUNDS
	PLUGIN_GET_INTERFACE_CURRENT(interfaceFactory, VAR_IFACE_SOUNDS, IEngineSound, IENGINESOUND_SERVER_INTERFACE_VERSION)
#endif

#if SOURCE_ENGINE >= SE_ORANGEBOX
	ConnectTier1Libraries( &interfaceFactory, 1 );
	ConnectTier2Libraries( &interfaceFactory, 1 );
	VAR_IFACE_ICVAR = g_pCVar;
	VAR_IFACE_FILESYSTEM = g_pFullFileSystem;
#else
	g_pCVar = VAR_IFACE_ICVAR;
#endif


#ifdef SOURCEMM
	/* Load the VSP listener.  This is usually needed for IServerPluginHelpers. */
	if ((SERVERPLUGIN_CALLBACKS_VAR = ismm->GetVSPInfo(NULL)) == NULL)
	{
		ismm->AddListener(this, this);
		ismm->EnableVSPListener();
	}

	VAR_IFACE_GLOBALVARS = ismm->GetCGlobals();

#ifdef SM_HOOK_PLUGINCALLBACK_SERVERACTIVATE
	SH_ADD_HOOK_MEMFUNC(IServerGameDLL, ServerActivate, VAR_IFACE_GAMESERVERDLL, this, &SERVERPLUGIN_ENGINE_CLASS::ServerActivate, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_GAMEFRAME
	SH_ADD_HOOK_MEMFUNC(IServerGameDLL, GameFrame, VAR_IFACE_GAMESERVERDLL, this, &SERVERPLUGIN_ENGINE_CLASS::GameFrame, true);
#endif 
#ifdef USE_IFACE_SERVERCLIENTS
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTACTIVE
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientActive, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientActive, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTDISCONNECT
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientDisconnect, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTPUTINSERVER
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientPutInServer, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_SETCOMMANDCLIENT
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, SetCommandClient, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::SetCommandClient, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTSETTINGSCHANGED
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientSettingsChanged, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientSettingsChanged, false);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCONNECT
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientConnect, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientConnect, false);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCOMMAND
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, ClientCommand, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::ClientCommand, false);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_NETWORKIDVALIDATED
	SH_ADD_HOOK_MEMFUNC(IServerGameClients, NetworkIDValidated, VAR_IFACE_SERVERCLIENTS, this, &SERVERPLUGIN_ENGINE_CLASS::NetworkIDValidated, true);
#endif
#endif
#else
	SERVERPLUGIN_CALLBACKS_VAR = this;
	VAR_IFACE_GLOBALVARS = VAR_IFACE_PLAYERINFOMANAGER->GetGlobalVars();
#endif

	// Assign classes
	if(!PLUGIN_GLOBALS_CLASS::InitInterfaces(interfaceFactory, gameServerFactory))
		return false;
	// Assign classes
	LIB_LIBRARIES_CLASS::Assign();
	
	// Set some globals
	VAR_PLUGIN_GLOBALS->iMaxclients = VAR_IFACE_GLOBALVARS->maxClients;
	VAR_IFACE_ENGINE->GetGameDir(VAR_PLUGIN_GLOBALS->szGameDir, 1024);
	VAR_PLUGIN_GLOBALS->szGameFolder = LIB_STRING_CLASS::StrGetLastPath(VAR_PLUGIN_GLOBALS->szGameDir);
	VAR_PLUGIN_GLOBALS->szGameName = VAR_IFACE_GAMESERVERDLL->GetGameDescription();

	MathLib_Init( 2.2f, 2.2f, 0.0f, 2 );


#if SOURCE_ENGINE >= SE_ORANGEBOX
	ConVar_Register(0, &s_BaseAccessor);
#else
	ConCommandBaseMgr::OneTimeInit(&s_BaseAccessor);
#endif
	VAR_PLUGIN_GLOBALS->bPluginLoaded = true;

#ifdef PYTHON
	isPythonEnabled = EnablePython();
	VAR_PLUGIN_PYTHON->OnPythonLoad(isPythonEnabled);
#ifdef PYTHON_DIE_ON_FAIL
	if(PYTHON_DIE_ON_FAIL && !isPythonEnabled)
		return false;
#endif
#endif
	return PLUGIN_VAR->Load(interfaceFactory, gameServerFactory);
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
bool SERVERPLUGIN_ENGINE_CLASS::Unload(char *error, size_t maxlen)
#else
void SERVERPLUGIN_ENGINE_CLASS::Unload( void )
#endif
{
	//gameeventmanager->RemoveListener( this ); // make sure we are unloaded from the event system
#ifdef SOURCEMM
#ifdef SM_HOOK_PLUGINCALLBACK_SERVERACTIVATE
	SH_REMOVE_HOOK_MEMFUNC(IServerGameDLL, ServerActivate, VAR_IFACE_GAMESERVERDLL, this, &SERVERPLUGIN_ENGINE_CLASS::ServerActivate, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_GAMEFRAME
	SH_REMOVE_HOOK_MEMFUNC(IServerGameDLL, GameFrame, VAR_IFACE_GAMESERVERDLL, this, &SERVERPLUGIN_ENGINE_CLASS::GameFrame, true);
#endif 
#ifdef USE_IFACE_SERVERCLIENTS
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTACTIVE
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientActive, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientActive, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTDISCONNECT
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientDisconnect, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientDisconnect, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTPUTINSERVER
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientPutInServer, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientPutInServer, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_SETCOMMANDCLIENT
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, SetCommandClient, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::SetCommandClient, true);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTSETTINGSCHANGED
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientSettingsChanged, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientSettingsChanged, false);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCONNECT
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientConnect, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientConnect, false);
#endif 
#ifdef SM_HOOK_PLUGINCALLBACK_CLIENTCOMMAND
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, ClientCommand, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::ClientCommand, false);
#endif
#ifdef SM_HOOK_PLUGINCALLBACK_NETWORKIDVALIDATED
	SH_REMOVE_HOOK_MEMFUNC(IServerGameClients, NetworkIDValidated, serverclients, this, &SERVERPLUGIN_ENGINE_CLASS::NetworkIDValidated, false);
#endif
#endif
#endif

#ifdef USE_LIB_EASYADMIN
#ifdef SETTING_LIB_EASYADMIN_FILE
#ifdef SETTING_LIB_EASYADMIN_LOADFROM
#ifdef SETTING_LIB_EASYADMIN_AUTOSAVE
	if(SETTING_LIB_EASYADMIN_FILE && SETTING_LIB_EASYADMIN_AUTOSAVE)
	{
		switch(SETTING_LIB_EASYADMIN_LOADFROM)
		{
		case LIB_EASYADMIN_CLASS::TextFile:
			VAR_LIB_EASYADMIN->SaveToFile(SETTING_LIB_EASYADMIN_FILE);
			break;
		case LIB_EASYADMIN_CLASS::Keyvalues:
			VAR_LIB_EASYADMIN->SaveToKeyvalue(SETTING_LIB_EASYADMIN_FILE);
			break;
		case LIB_EASYADMIN_CLASS::IniFile:
			VAR_LIB_EASYADMIN->SaveToIni(SETTING_LIB_EASYADMIN_FILE);
			break;
		}
	}
#endif
#endif
#endif
#endif

	PLUGIN_VAR->Unload();
	
#if SOURCE_ENGINE >= SE_ORANGEBOX
	ConVar_Unregister( );
	DisconnectTier2Libraries( );
	DisconnectTier1Libraries( );
#endif

	LIB_LIBRARIES_CLASS::UnAssign();
	CMD_PAUSE;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is paused (i.e should stop running but isn't unloaded)
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
bool SERVERPLUGIN_ENGINE_CLASS::Pause(char *error, size_t maxlen)
#else
void SERVERPLUGIN_ENGINE_CLASS::Pause( void )
#endif
{
	PLUGIN_VAR->Pause();
	CMD_PAUSE;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unpaused (i.e should start executing again)
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
bool SERVERPLUGIN_ENGINE_CLASS::Unpause(char *error, size_t maxlen)
#else
void SERVERPLUGIN_ENGINE_CLASS::UnPause( void )
#endif
{
	PLUGIN_VAR->UnPause();
	CMD_PAUSE;
}

//---------------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
const char *SERVERPLUGIN_ENGINE_CLASS::GetDescription()
#else
const char *SERVERPLUGIN_ENGINE_CLASS::GetPluginDescription( void )
#endif
{
	#ifdef SOURCEMM
	return PLUGIN_ABOUT;
	#endif
	return PLUGIN_DESCRIPTION;
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
void SERVERPLUGIN_ENGINE_CLASS::OnLevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background)
#else
void SERVERPLUGIN_ENGINE_CLASS::LevelInit(char const *pMapName)
#endif
{
	VAR_PLUGIN_GLOBALS->szCurrentMap = pMapName;
	VAR_PLUGIN_GLOBALS->iLevelChanges++;
#ifdef USE_LIB_DOWNLOAD
	VAR_LIB_DOWNLOAD->DispatchDownloads();
#endif
	if(VAR_LIB_PLAYERMNGR)
		VAR_LIB_PLAYERMNGR->Reset();
#ifdef USE_LIB_TIMER
	VAR_LIB_TIMER->Reset();
#endif
	PLUGIN_VAR->LevelInit(pMapName, VAR_PLUGIN_GLOBALS->szOldMap);
}

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	PLUGIN_VAR->ServerActivate(pEdictList, edictCount, clientMax);
}

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::GameFrame(bool simulating)
{
	#ifdef USE_LIB_TIMER
	VAR_LIB_TIMER->CheckTimers();
	#endif
	PLUGIN_VAR->GameFrame(simulating);
}

//---------------------------------------------------------------------------------
// Purpose: called on level end (as the server is shutting down or going to a new map)
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
void SERVERPLUGIN_ENGINE_CLASS::OnLevelShutdown()
#else
void SERVERPLUGIN_ENGINE_CLASS::LevelShutdown( void ) // !!!!this can get called multiple times per map change
#endif
{
#ifdef USE_IFACE_GAMEEVENTMANAGER
	if(VAR_IFACE_GAMEEVENTMANAGER)
		VAR_IFACE_GAMEEVENTMANAGER->RemoveListener(VAR_PLUGIN_GAMEEVENTS);
#endif
	if(VAR_PLUGIN_GLOBALS->szCurrentMap)
		VAR_PLUGIN_GLOBALS->szOldMap = LIB_STRING_CLASS::StrNew(VAR_PLUGIN_GLOBALS->szCurrentMap);
	PLUGIN_VAR->LevelShutdown();
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
void SERVERPLUGIN_ENGINE_CLASS::ClientActive(edict_t *pEntity, bool bLoadGame)
#else
void SERVERPLUGIN_ENGINE_CLASS::ClientActive(edict_t *pEntity)
#endif
{
	if(VAR_LIB_PLAYERMNGR)
		VAR_LIB_PLAYERMNGR->AddClient(pEntity);

	PLUGIN_VAR->ClientActive(pEntity);
}

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::ClientDisconnect(edict_t *pEntity)
{
	if(VAR_LIB_PLAYERMNGR)
		VAR_LIB_PLAYERMNGR->RemoveClient(pEntity);
	PLUGIN_VAR->ClientDisconnect(pEntity);
}

//---------------------------------------------------------------------------------
// Purpose: called on 
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::ClientPutInServer(edict_t *pEntity, char const *playername)
{
	PLUGIN_VAR->ClientPutInServer(pEntity, playername);
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::SetCommandClient(int index)
{
	m_iClientCommandIndex = index;
	PLUGIN_VAR->SetCommandClient(index);
}

//---------------------------------------------------------------------------------
// Purpose: called when the client change a setting (i.e name)
//---------------------------------------------------------------------------------
void SERVERPLUGIN_ENGINE_CLASS::ClientSettingsChanged(edict_t *pEdict)
{
	PLUGIN_VAR->ClientSettingsChanged(pEdict);
}

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
#ifdef SOURCEMM
bool SERVERPLUGIN_ENGINE_CLASS::ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
#else
PLUGIN_RESULT SERVERPLUGIN_ENGINE_CLASS::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
#endif
{
#ifdef SOURCEMM
	bool *bAllowConnect = (bool*)true;
	PLUGIN_RESULT result = PLUGIN_VAR->ClientConnect(bAllowConnect, pEntity, pszName, pszAddress, reject, maxrejectlen);
	if(result == PLUGIN_STOP)
		return false;
	return true;
#else
	return PLUGIN_VAR->ClientConnect(bAllowConnect, pEntity, pszName, pszAddress, reject, maxrejectlen);
#endif
}

//---------------------------------------------------------------------------------
// Purpose: called when a client types in a command (only a subset of commands however, not CON_COMMAND's)
//---------------------------------------------------------------------------------
CMD_PLUGIN_RESULT SERVERPLUGIN_ENGINE_CLASS::ENGINE_ClientCommand(pEntity)
{
	if (!pEntity || pEntity->IsFree()) 
		CMD_CONTINUE;
#ifdef USE_LIB_MENU
	if(LIB_STRING_CLASS::FStrEq(args.Arg(0), "menuselect"))
	{
		if(VAR_LIB_MENU->ClientCommand_MenuSelected(pEntity, atoi(args.Arg(1))))
			CMD_OVERRIDE;
	}
#endif
#ifndef SOURCEMM
	return
#endif
#if SOURCE_ENGINE <= SE_DARKMESSIAH
	PLUGIN_VAR->ClientCommand(pEntity);
#else
	PLUGIN_VAR->ClientCommand(pEntity, args);
#endif
}

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
CMD_PLUGIN_RESULT SERVERPLUGIN_ENGINE_CLASS::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	#ifndef SOURCEMM
	return
	#endif
		PLUGIN_VAR->NetworkIDValidated(pszUserName, pszNetworkID);
}

//---------------------------------------------------------------------------------
// Purpose: called when a cvar value query is finished
//---------------------------------------------------------------------------------
#if SOURCE_ENGINE >= SE_ORANGEBOX
void SERVERPLUGIN_ENGINE_CLASS::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
	//Msg( "Cvar query (cookie: %d, status: %d) - name: %s, value: %s\n", iCookie, eStatus, pCvarName, pCvarValue );
	PLUGIN_VAR->OnQueryCvarValueFinished(iCookie, pPlayerEntity, eStatus, pCvarName, pCvarValue);
}
#endif

//---------------------------------------------------------------------------------
// Purpose: called when an event is fired
//---------------------------------------------------------------------------------
/*void SERVERPLUGIN_ENGINE_CLASS::FireGameEvent( IGameEvent *event )
{
	const char * name = event->GetName();
}*/
const char *SERVERPLUGIN_ENGINE_CLASS::GetName()
{
	return PLUGIN_NAME;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetVersion()
{
	return PLUGIN_VERSION;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetAuthor()
{
	return PLUGIN_ACTOR;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetURL()
{
	return PLUGIN_URL;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetLicense()
{
	return PLUGIN_LICENSE;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetDate()
{
	return __DATE__;
}

const char *SERVERPLUGIN_ENGINE_CLASS::GetLogTag()
{
	return PLUGIN_NAME;
}
// 
// The plugin is a static singleton that is exported as an interface
//
SERVERPLUGIN_ENGINE_CLASS SERVERPLUGIN_ENGINE_VAR;
#ifdef SOURCEMM
PLUGIN_EXPOSE(SERVERPLUGIN_ENGINE_CLASS, SERVERPLUGIN_ENGINE_VAR);
#else
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(SERVERPLUGIN_ENGINE_CLASS, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, SERVERPLUGIN_ENGINE_VAR);
#if SOURCE_ENGINE >= SE_ORANGEBOX
#ifdef PLUGIN_USE_SOURCEHOOK
	SourceHook::Impl::CSourceHookImpl g_SourceHook;
#endif
#else
#ifdef PLUGIN_USE_SOURCEHOOK
	SourceHook::CSourceHookImpl g_SourceHook;
#endif
#endif
#ifdef PLUGIN_USE_SOURCEHOOK
	SourceHook::ISourceHook *g_SHPtr = &g_SourceHook;
	int g_PLID = PLUGIN_SOURCEHOOK_ID;
#endif
#endif

IServerPluginCallbacks *SERVERPLUGIN_CALLBACKS_VAR = NULL;

int SERVERPLUGIN_ENGINE_CLASS::FormatIface(char iface[], unsigned int maxlength) // From metamod
{
	int length = (int)strlen(iface);
	int i;
	int num = 0;

	for (i = length - 1; i >= 0; i--)
	{
		if (!isdigit(iface[i]))
		{
			if (i != length - 1)
			{
				num = 1;
			}
			break;
		}
	}

	if ( (num && ((int)maxlength <= length)) || (!num && ((int)maxlength <= length + 3)) )
	{
		return -1;
	}

	if (i != length - 1)
	{
		num = atoi(&(iface[++i]));
	}

	num++;

	snprintf(&(iface[i]), 4, "%03d", num);

	return num;
}

void *SERVERPLUGIN_ENGINE_CLASS::InterfaceSearch(CreateInterfaceFn fn, const char *iface, int max, int *ret) // From metamod
{
	char _if[256];	/* assume no interface goes beyond this */
	size_t len = strlen(iface);
	int num = 0;
	void *pf = NULL;

	if (max > IFACE_MAXNUM)
	{
		max = IFACE_MAXNUM;
	}

	if (len + 4 > sizeof(_if))
	{
		if (ret)
		{
			*ret = IFACE_FAILED;
		}
		return NULL;
	}

	strcpy(_if, iface);

	do
	{
		if ((pf = (fn)(_if, ret)) != NULL)
		{
			break;
		}
		if (num > max)
		{
			break;
		}
	} while ((num = FormatIface(_if, len+1)));

	return pf;
}

void *SERVERPLUGIN_ENGINE_CLASS::VInterfaceMatch(CreateInterfaceFn fn, const char *iface, int min) // From metamod
{
	char buffer[256];	/* assume no interface will go beyond this */
	size_t len = strlen(iface);
	int ret;			/* just in case something doesn't handle NULL properly */

	if (len > sizeof(buffer) - 4)
	{
		return NULL;
	}

	strcpy(buffer, iface);

	if (min != -1)
	{
		char *ptr = &buffer[len - 1];
		int digits = 0;
		while (isdigit(*ptr) && digits <=3)
		{
			*ptr = '\0';
			digits++;
			ptr--;
		}
		if (digits != 3)
		{
			/* for now, assume this is an error */
			strcpy(buffer, iface);
		}
		else
		{
			char num[4];
			min = (min == 0) ? 1 : min;
			snprintf(num, sizeof(num), "%03d", min);
			strcat(buffer, num);
		}
	}

	return InterfaceSearch(fn, buffer, IFACE_MAXNUM, &ret);
}
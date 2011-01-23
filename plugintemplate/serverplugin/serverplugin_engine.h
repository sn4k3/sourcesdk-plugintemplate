#ifndef SERVERPLUGIN_ENGINE_H
#define SERVERPLUGIN_ENGINE_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define SERVERPLUGIN_ENGINE_VERSION "1.0"
#define SERVERPLUGIN_ENGINE_CLASS CServerEngine
#define SERVERPLUGIN_ENGINE_VAR g_ServerEngine

#define SERVERPLUGIN_CALLBACKS_VAR vsp_callbacks

#ifdef SOURCEMM
#define PLUGIN_VERSION_ENGINE ""PLUGIN_VERSION" MMS"
#define CMD_CONTINUE return
#define CMD_OVERRIDE RETURN_META(MRES_SUPERCEDE)
#define CMD_PAUSE return true
#define CMD_PLUGIN_RESULT void
#include "ISmmPlugin.h"

class SERVERPLUGIN_ENGINE_CLASS : public ISmmPlugin, public IMetamodListener
{
public:
	SERVERPLUGIN_ENGINE_CLASS();
	~SERVERPLUGIN_ENGINE_CLASS();

	// Overrides
	void			AllPluginsLoaded();
	void			OnVSPListening(IServerPluginCallbacks *iface);
	bool			Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlength, bool late);
	bool			Unload(char *error, size_t maxlen);
	bool			Pause(char *error, size_t maxlen);
	bool			Unpause(char *error, size_t maxlen);
	const char *	GetDescription();
	void			OnLevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background);
	void			OnLevelShutdown();

	// Hooks
	void			ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
	void			GameFrame(bool simulating);
	void			ClientActive(edict_t *pEntity, bool bLoadGame);
	void			ClientDisconnect(edict_t *pEntity);
	void			ClientPutInServer(edict_t *pEntity, char const *playername);
	void			SetCommandClient(int index);
	void			ClientSettingsChanged(edict_t *pEdict);
	bool			ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen);
	void			ENGINE_ClientCommand(pEntity);
	void			NetworkIDValidated(const char *pszUserName, const char *pszNetworkID);
#if SOURCE_ENGINE >= SE_ORANGEBOX
	void			OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue);
#endif

	const char *GetName();
	const char *GetVersion();
	const char *GetAuthor();
	const char *GetURL();
	const char *GetLicense();
	const char *GetDate();
	const char *GetLogTag();

	virtual int GetCommandIndex() { return m_iClientCommandIndex; }


	static int FormatIface(char iface[], unsigned int maxlength);
	static void *InterfaceSearch(CreateInterfaceFn fn, const char *iface, int max, int *ret);
	static void *VInterfaceMatch(CreateInterfaceFn fn, const char *iface, int min = -1);
private:
	int m_iClientCommandIndex;
};

PLUGIN_GLOBALVARS();

#else
#define PLUGIN_VERSION_ENGINE ""PLUGIN_VERSION" VSP"
#define CMD_CONTINUE return PLUGIN_CONTINUE
#define CMD_OVERRIDE return PLUGIN_STOP
#define CMD_PAUSE return 
#define CMD_PLUGIN_RESULT PLUGIN_RESULT
#include "engine/iserverplugin.h"


//---------------------------------------------------------------------------------
// Purpose: a sample 3rd party plugin class
//---------------------------------------------------------------------------------
class SERVERPLUGIN_ENGINE_CLASS : public IServerPluginCallbacks //, public IGameEventListener2
{
public:
	SERVERPLUGIN_ENGINE_CLASS();
	~SERVERPLUGIN_ENGINE_CLASS();

	// IServerPluginCallbacks methods
	virtual bool			Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	virtual void			Unload( void );
	virtual void			Pause( void );
	virtual void			UnPause( void );
	virtual const char     *GetPluginDescription( void );      
	virtual void			LevelInit( char const *pMapName );
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax );
	virtual void			GameFrame( bool simulating );
	virtual void			LevelShutdown( void );
	virtual void			ClientActive( edict_t *pEntity );
	virtual void			ClientDisconnect( edict_t *pEntity );
	virtual void			ClientPutInServer( edict_t *pEntity, char const *playername );
	virtual void			SetCommandClient( int index );
	virtual void			ClientSettingsChanged( edict_t *pEdict );
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen );
	virtual PLUGIN_RESULT	ENGINE_ClientCommand(pEntity);
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID );

#if SOURCE_ENGINE >= SE_ORANGEBOX
	virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue );
#endif

	// IGameEventListener Interface
	//virtual void FireGameEvent( IGameEvent * event );

	virtual int GetCommandIndex() { return m_iClientCommandIndex; }

	const char *GetName();
	const char *GetVersion();
	const char *GetAuthor();
	const char *GetURL();
	const char *GetLicense();
	const char *GetDate();
	const char *GetLogTag();

		static int FormatIface(char iface[], unsigned int maxlength);
	static void *InterfaceSearch(CreateInterfaceFn fn, const char *iface, int max, int *ret);
	static void *VInterfaceMatch(CreateInterfaceFn fn, const char *iface, int min = -1);
private:
	int m_iClientCommandIndex;
};
#ifdef PLUGIN_USE_SOURCEHOOK
extern SourceHook::ISourceHook *g_SHPtr;
extern int g_PLID;
#endif
#endif

extern SERVERPLUGIN_ENGINE_CLASS SERVERPLUGIN_ENGINE_VAR;

extern IServerPluginCallbacks *SERVERPLUGIN_CALLBACKS_VAR;

#ifndef IFACE_MAXNUM
#define IFACE_MAXNUM			999						/**< Maximum interface version */
#endif

/**
 * @brief Macro for automatically getting a current or newer Valve interface.
 *
 * @param v_factory		Factory method to use from ISmmAPI (such as engineFactory).
 * @param v_var			Variable name to store into.
 * @param v_type		Interface type (do not include the pointer/asterisk).
 * @param v_name		Interface name.
 */
#define PLUGIN_GET_INTERFACE_CURRENT(v_factory, v_var, v_type, v_name) \
	v_var = (v_type *)SERVERPLUGIN_ENGINE_CLASS::VInterfaceMatch(v_factory, v_name); \
	if (!v_var) \
	{ \
		Warning("Could not find interface: %s\n", v_name); \
		return false; \
	}

 /**
  * @brief Same as GET_V_IFACE, except searches for any.
  *
  * @param v_factory	Factory method to use from ISmmAPI (such as engineFactory).
  * @param v_var		Variable name to store into.
  * @param v_type		Interface type (do not include the pointer/asterisk).
  * @param v_name		Interface name.
  */
#define PLUGIN_GET_INTERFACE_ANY(v_factory, v_var, v_type, v_name) \
	v_var = (v_type *)SERVERPLUGIN_ENGINE_CLASS::VInterfaceMatch(v_factory, v_name, 0); \
	if (!v_var) \
	{ \
		Warning("Could not find interface: %s\n", v_name); \
		return false; \
	}

extern IVEngineServer						*VAR_IFACE_ENGINE;
extern IGameEventManager2					*VAR_IFACE_GAMEEVENTMANAGER;
extern IPlayerInfoManager					*VAR_IFACE_PLAYERINFOMANAGER;
extern IBotManager							*VAR_IFACE_BOTMANAGER;
extern IEffects								*VAR_IFACE_EFFECTS;
extern IServerPluginHelpers					*VAR_IFACE_SERVERPLUGINHELPERS;
extern IUniformRandomStream					*VAR_IFACE_RANDOMSTREAM;
extern IEngineTrace							*VAR_IFACE_ENGINETRACE;
extern IFileSystem							*VAR_IFACE_FILESYSTEM;
extern ICvar								*VAR_IFACE_ICVAR;
extern IVoiceServer							*VAR_IFACE_VOICESERVER;
extern IServerGameClients					*VAR_IFACE_SERVERCLIENTS;
extern IServerGameEnts						*VAR_IFACE_SERVERGAMEENTS;
extern INetworkStringTableContainer			*VAR_IFACE_NETWORKSTRINGTABLE;
extern INetworkStringTable					*downloadablestable;
extern IServerGameDLL						*VAR_IFACE_GAMESERVERDLL;
extern IEngineSound							*VAR_IFACE_SOUNDS;

extern CGlobalVars							*VAR_IFACE_GLOBALVARS;

#endif
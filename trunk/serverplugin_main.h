#ifndef SERVERPLUGIN_MAIN_H
#define SERVERPLUGIN_MAIN_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

class PLUGIN_CLASS
{
public:
	PLUGIN_CLASS();
	~PLUGIN_CLASS();

	// IServerPluginCallbacks methods
	void			OnVSPListening(IServerPluginCallbacks *iface);
	bool			Load(	CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	void			Unload( void );
	void			Pause( void );
	void			UnPause( void );
	void			LevelInit( char const *pMapName, const char *pOldMapName );
	void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax );
	void			GameFrame( bool simulating );
	void			LevelShutdown( void );
	void			ClientActive( edict_t *pEntity );
	void			ClientDisconnect( edict_t *pEntity );
	void			ClientPutInServer( edict_t *pEntity, char const *playername );
	void			SetCommandClient( int index );
	void			ClientSettingsChanged( edict_t *pEdict );
	PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen );
	CMD_PLUGIN_RESULT	ENGINE_ClientCommand(pEntity);
	CMD_PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID );
	void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue );

	int GetCommandIndex() { return SERVERPLUGIN_ENGINE_VAR.GetCommandIndex(); }
};

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_CLASS *PLUGIN_VAR;

#endif
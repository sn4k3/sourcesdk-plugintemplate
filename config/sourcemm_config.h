#ifndef SOURCEMM_CONFIG_H
#define SOURCEMM_CONFIG_H
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
// The following settings is only applied to SourceMM plugin based
// In SourceMM we can choose what plugin callbacks we need, by hook
// Comment the define to disable the callback
//=================================================================================

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
// void	ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
#define SM_HOOK_PLUGINCALLBACK_SERVERACTIVATE

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
// void GameFrame(bool simulating);
#define SM_HOOK_PLUGINCALLBACK_GAMEFRAME

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
// void	ClientActive(edict_t *pEntity, bool bLoadGame);
#define SM_HOOK_PLUGINCALLBACK_CLIENTACTIVE

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
// void ClientDisconnect(edict_t *pEntity);
#define SM_HOOK_PLUGINCALLBACK_CLIENTDISCONNECT

//---------------------------------------------------------------------------------
// Purpose: called on 
//---------------------------------------------------------------------------------
// void ClientPutInServer(edict_t *pEntity, char const *playername);
#define SM_HOOK_PLUGINCALLBACK_CLIENTPUTINSERVER

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
// void SetCommandClient(int index);
#define SM_HOOK_PLUGINCALLBACK_SETCOMMANDCLIENT

//---------------------------------------------------------------------------------
// Purpose: called when the client change a setting (i.e name)
//---------------------------------------------------------------------------------
//void ClientSettingsChanged(edict_t *pEdict);
#define SM_HOOK_PLUGINCALLBACK_CLIENTSETTINGSCHANGED

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
// bool ClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen);
#define SM_HOOK_PLUGINCALLBACK_CLIENTCONNECT

//---------------------------------------------------------------------------------
// Purpose: called when a client types in a command (only a subset of commands however, not CON_COMMAND's)
//---------------------------------------------------------------------------------
// void ClientCommand(edict_t *pEntity); - Orange Box
// void ClientCommand(edict_t *pEntity, const CCommand &args); - Original
#define SM_HOOK_PLUGINCALLBACK_CLIENTCOMMAND

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
// void NetworkIDValidated(const char *pszUserName, const char *pszNetworkID);
#define SM_HOOK_PLUGINCALLBACK_NETWORKIDVALIDATED

#endif
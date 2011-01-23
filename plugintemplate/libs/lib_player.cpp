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
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_player.h"
#include "libs/lib_lang.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_PLAYER_CLASS::LIB_PLAYER_CLASS()
{
	Reset();
}

// Constructor, when used a valid userid, index got ignored
LIB_PLAYER_CLASS::LIB_PLAYER_CLASS(int index, int userid /*= 0*/)
{
	if(userid > 0)
	{
		FindPlayerByUserID(userid);
		return;
	}
	FindPlayer(index);
}

// Constructor
LIB_PLAYER_CLASS::LIB_PLAYER_CLASS(edict_t *pEdict)
{
	FindPlayer(pEdict);
}

// Destructor
LIB_PLAYER_CLASS::~LIB_PLAYER_CLASS()
{
	Reset();
}

// Invalidate class
void LIB_PLAYER_CLASS::Reset()
{
	b_isvalid = false;
	m_iIndex = 0;
	m_iUserid = 0;
	m_hEdict = NULL;
	m_iPlayerinfo = NULL;
	m_iCBaseEntity = NULL;
	m_iNetChannelInfo = NULL;
	m_szSteamid = NULL;
}

// Return true if this class is valid, otherwise false (invalid player, entity, ...)
bool LIB_PLAYER_CLASS::IsValid()
{
	return b_isvalid ? LIB_ENTITY_CLASS::IsEntitySafe(m_hEdict) : false;
}

//=================================================================================
// Find Player
//=================================================================================
// Find a player and initalize this class with founded player
// Class will invalidate if player was not found
bool LIB_PLAYER_CLASS::FindPlayer(int playerindex)
{
	Reset();
	if(playerindex < 1 || playerindex > VAR_IFACE_GLOBALVARS->maxClients)
		return false;
	return FindPlayer(PEntityOfEntIndex(playerindex));
}

// Find a player and initalize this class with founded player
// Class will invalidate if player was not found
bool LIB_PLAYER_CLASS::FindPlayer(edict_t *pEdict)
{
	Reset();
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEdict))
		return false;
	int playerindex = IndexOfEdict(pEdict);
	if(playerindex < 1) return false;
	IPlayerInfo *info = IsPlayer(pEdict);
	if(!info) return false;
	
	this->m_iIndex = playerindex;
	this->m_iUserid = info->GetUserID();
	this->m_hEdict = pEdict;
	this->m_iPlayerinfo = info;
	this->m_iCBaseEntity = LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEdict);
	this->m_iNetChannelInfo = VAR_IFACE_ENGINE->GetPlayerNetInfo(playerindex);


	this->m_szSteamid = info->GetNetworkIDString();
	b_isvalid = true;
	return true;
	//return FindPlayer(IndexOfEdict(pEdict));
}

// Find a player and initalize this class with founded player
// Class will invalidate if player was not found
bool LIB_PLAYER_CLASS::FindPlayerByUserID(int userid)
{
	return FindPlayer(LIB_ENTITY_CLASS::GetIndexFromUserID(userid));
}

//=================================================================================
// Is Methods
//=================================================================================
// Is player alive?
bool LIB_PLAYER_CLASS::IsAlive()
{
	if(!IsValid()) return false;
	return !this->m_iPlayerinfo->IsDead();
}

// Is player a Bot?
bool LIB_PLAYER_CLASS::IsBot()
{
	if(!IsValid()) return false;
	return this->m_iPlayerinfo->IsFakeClient();
}

// Check if the player is within a radius of vector target
bool LIB_PLAYER_CLASS::IsWithinRadius(Vector vecTarget, float fRadius)
{
	if(!IsValid()) return false;
	return LIB_ENTITY_CLASS::IsWithinRadius(m_iPlayerinfo->GetAbsOrigin(), vecTarget, fRadius);
}

//=================================================================================
// Get Methods
//=================================================================================
// Get a translation based in the player game language
// If safe is true, returns the DEFAULT if the language was not translated
// Require Lang Lib
const char *LIB_PLAYER_CLASS::GetTranslation(const char *nameSpace, const char *phrase, bool safe /*= true*/)
{
#ifndef USE_LIB_LANG
	return NULL;
#endif
	return VAR_LIB_LANG->GetLangStr(m_hEdict, nameSpace, phrase, safe);
}

//=================================================================================
// Functions
//=================================================================================
void LIB_PLAYER_CLASS::Kill()
{
	if(!IsValid()) return ;
	Sexec(m_hEdict, "kill");
}

// Disconnect a player with a reason
bool LIB_PLAYER_CLASS::Disconnect(const char *reason)
{
	if(!IsValid()) return false;
	if(IsBot() || !m_iNetChannelInfo)
	{
		char kick_cmd[512];
		snprintf( kick_cmd, sizeof(kick_cmd), "kickid %i\n", m_iUserid);
		engine->ServerCommand(kick_cmd);
		engine->ServerExecute();
		return true;
	}
	INetChannel *pNetChan = static_cast<INetChannel *>(m_iNetChannelInfo);
	IClient *pClient = static_cast<IClient *>(pNetChan->GetMsgHandler());
	if(!pClient) return false;
	if ( !reason || reason[0] == 0 )
		pClient->Disconnect("Kicked by Console");
	else
		pClient->Disconnect("%s", reason);
	return true;
}

// Force client to reconnect without droping the netchannel
bool LIB_PLAYER_CLASS::Reconnect()
{
	if(!IsValid()) return false;
	if(IsBot() || !m_iNetChannelInfo)
		return false;
	INetChannel *pNetChan = static_cast<INetChannel *>(m_iNetChannelInfo);
	IClient *pClient = static_cast<IClient *>(pNetChan->GetMsgHandler());
	if(!pClient) return false;
	pClient->Reconnect();
	return true;
}

//=================================================================================
//									Static Methods
//=================================================================================

//=================================================================================
// Is Methods
//=================================================================================
// Check if entity is a valid player, and return IPlayerInfo*, NULL if not
IPlayerInfo *LIB_PLAYER_CLASS::IsPlayer(edict_t *pEdict, bool onlyHumans /*= false*/)
{
	IPlayerInfo *info = LIB_ENTITY_CLASS::GetPlayerinfoFromEntity(pEdict);
    if (!info)
		return NULL;
	if(onlyHumans)
		if(info->IsFakeClient())
			return NULL;
	return info;
}


// Is player alive?
bool LIB_PLAYER_CLASS::IsAlive(edict_t *pEntity)
{
	/*return (bool)!(*((char*)((char*)pEntity->GetUnknown()+m_Off_LifeState)));
	CPlayerState *pPlayerState = GetPlayerStatefromEdict(pEntity);
	if(!pPlayerState)
		return false;

	if(!pPlayerState->deadflag) return true;*/
	IPlayerInfo *info = LIB_PLAYER_CLASS::IsPlayer(pEntity);
	if(!info) return false;
	return !info->IsDead();
	return false;
}

//=================================================================================
// Functions
//=================================================================================
// Disconnect a player with a reason
bool LIB_PLAYER_CLASS::Disconnect(edict_t *pEntity, const char *reason)
{
	IPlayerInfo *info = LIB_PLAYER_CLASS::IsPlayer(pEntity);
	if(!info) return false;
	INetChannelInfo *nci = VAR_IFACE_ENGINE->GetPlayerNetInfo(IndexOfEdict(pEntity));
	if(info->IsFakeClient() || !nci)
	{
		char kick_cmd[512];
		snprintf( kick_cmd, sizeof(kick_cmd), "kickid %i\n", info->GetUserID());
		engine->ServerCommand(kick_cmd);
		engine->ServerExecute();
		return true;
	}
	INetChannel *pNetChan = static_cast<INetChannel *>(nci);
	IClient *pClient = static_cast<IClient *>(pNetChan->GetMsgHandler());
	if(!pClient) return false;
	if ( !reason || reason[0] == 0 )
		pClient->Disconnect("Kicked by Console");
	else
		pClient->Disconnect("%s", reason);
	return true;
}

// Force client to reconnect without droping the netchannel
bool LIB_PLAYER_CLASS::Reconnect(edict_t *pEntity)
{
	IPlayerInfo *info = LIB_PLAYER_CLASS::IsPlayer(pEntity);
	if(!info) return false;
	INetChannelInfo *nci = VAR_IFACE_ENGINE->GetPlayerNetInfo(IndexOfEdict(pEntity));
	if(info->IsFakeClient() || !nci)
		return false;
	INetChannel *pNetChan = static_cast<INetChannel *>(nci);
	IClient *pClient = static_cast<IClient *>(pNetChan->GetMsgHandler());
	if(!pClient) return false;
	pClient->Reconnect();
	return true;
}

// Execute a command on client.
// Filters allowed
bool LIB_PLAYER_CLASS::Cexec(const char *players, const char *command, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	MULTIARGS(command);

	for(int i = 0; i < mrf.GetRecipientCount(); i++)
		VAR_IFACE_ENGINE->ClientCommand(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), string);

	return true;
}

// Execute a command on client.
bool LIB_PLAYER_CLASS::Cexec(edict_t *pEntity, const char *command, ...)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	MULTIARGS(command);
	VAR_IFACE_ENGINE->ClientCommand(pEntity, string);
	return true;
}

// Execute a command on client.
// Filters allowed
bool LIB_PLAYER_CLASS::Sexec(const char *players, const char *command, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	MULTIARGS(command);

	for(int i = 0; i < mrf.GetRecipientCount(); i++)
		VAR_IFACE_SERVERPLUGINHELPERS->ClientCommand(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), string);

	return true;
}

// Execute a command on client.
bool LIB_PLAYER_CLASS::Sexec(edict_t *pEntity, const char *command, ...)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	MULTIARGS(command);
	VAR_IFACE_SERVERPLUGINHELPERS->ClientCommand(pEntity, string);
	return true;
}

//=================================================================================
// Get Methods
//=================================================================================
// Convert STEAMID to Steam Community ID
// Thanks to voogru, http://forums.alliedmods.net/showthread.php?t=60899
__int64 LIB_PLAYER_CLASS::GetCommunityID(const char *pszAuthID)
{
    if(!pszAuthID)
        return 0;

    int iServer = 0;
    int iAuthID = 0;

    char szAuthID[64];
    strcpy(szAuthID, pszAuthID);
    szAuthID[64] = '\n';

    char *szTmp = strtok(szAuthID, ":");
	szTmp = strtok(NULL, ":");
    while(szTmp)
    {
        char *szTmp2 = strtok(NULL, ":");
        if(szTmp2)
        {
            iServer = atoi(szTmp);
            iAuthID = atoi(szTmp2);
        }
		szTmp = strtok(NULL, ":");
    }

    if(iAuthID == 0)
        return 0;

    __int64 i64friendID = (__int64)iAuthID * 2;

    //Friend ID's with even numbers are the 0 auth server.
    //Friend ID's with odd numbers are the 1 auth server.
    i64friendID += 76561197960265728 + iServer; 

    return i64friendID;
}  

//=================================================================================
//									LIB_PLAYERMNGR_CLASS
//=================================================================================
//=================================================================================
// Operators
//=================================================================================
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::operator [](int playerindex)
{
	return GetPlayer(playerindex);
}

PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::operator [](edict_t *pEntity)
{
	return GetPlayer(pEntity);
}

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_PLAYERMNGR_CLASS::LIB_PLAYERMNGR_CLASS()
{
	vec_players.EnsureCapacity(VAR_IFACE_GLOBALVARS->maxClients);
}

LIB_PLAYERMNGR_CLASS::~LIB_PLAYERMNGR_CLASS()
{
	Reset();
}

// Remove all players from list
void LIB_PLAYERMNGR_CLASS::Reset()
{
	vec_players.PurgeAndDeleteElements();
}

//=================================================================================
// Add Clients
//=================================================================================
// Add a client to list from player index
bool LIB_PLAYERMNGR_CLASS::AddClient(int playerindex)
{
	PLUGIN_PLAYER_CLASS *player = GetPlayer(playerindex);
	if(player) return false;
	player = new PLUGIN_PLAYER_CLASS();
	if(!player->FindPlayer(playerindex))
		return false;
	vec_players.AddToTail(player);
	return true;
}

// Add a client to list from player edict
bool LIB_PLAYERMNGR_CLASS::AddClient(edict_t *pEntity)
{
	PLUGIN_PLAYER_CLASS *player = GetPlayer(pEntity);
	if(player) return false;
	player = new PLUGIN_PLAYER_CLASS();
	if(!player->FindPlayer(pEntity))
		return false;
	vec_players.AddToTail(player);
	return true;
}

// Add a client to list from player userid
bool LIB_PLAYERMNGR_CLASS::AddClientByUserID(int userid)
{
	PLUGIN_PLAYER_CLASS *player = GetPlayerByUserID(userid);
	if(player) return false;
	player = new PLUGIN_PLAYER_CLASS();
	if(!player->FindPlayerByUserID(userid))
		return false;
	vec_players.AddToTail(player);
	return true;
}

//=================================================================================
// Remove Clients
//=================================================================================
// Remove a client to list from player index
bool LIB_PLAYERMNGR_CLASS::RemoveClient(int playerindex)
{
	FOR_EACH_VEC(vec_players, i)
	{
		if(playerindex == vec_players[i]->Index())
		{
			delete vec_players[i];
			vec_players.Remove(i);
			return true;
		}
	}
	return false;
}

// Remove a client to list from player edict
bool LIB_PLAYERMNGR_CLASS::RemoveClient(edict_t *pEntity)
{
	FOR_EACH_VEC(vec_players, i)
	{
		if(pEntity == vec_players[i]->Edict())
		{
			delete vec_players[i];
			vec_players.Remove(i);
			return true;
		}
	}
	return false;
}

// Remove a client to list from player userid
bool LIB_PLAYERMNGR_CLASS::RemoveClientByUserID(int userid)
{
	FOR_EACH_VEC(vec_players, i)
	{
		if(userid == vec_players[i]->UserID())
		{
			delete vec_players[i];
			vec_players.Remove(i);
			return true;
		}
	}
	return false;
}

//=================================================================================
// Remove Client
//=================================================================================

//=================================================================================
// Get Player
//=================================================================================
// Get player by his index
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::GetPlayer(int playerindex)
{
	if(playerindex < 1 || playerindex > VAR_IFACE_GLOBALVARS->maxClients)
		return NULL;
	FOR_EACH_VEC(vec_players, i)
	{
		if(vec_players[i]->Index() == playerindex)
			return vec_players[i];
	}
	return NULL;
}

// Get player by edict
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::GetPlayer(edict_t *pEntity)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return NULL;
	FOR_EACH_VEC(vec_players, i)
	{
		if(vec_players[i]->Edict() == pEntity)
			return vec_players[i];
	}
	return NULL;
}

// Get player by userid
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::GetPlayerByUserID(int userid)
{
	if(userid < 2) return NULL;
	FOR_EACH_VEC(vec_players, i)
	{
		if(vec_players[i]->UserID() == userid)
			return vec_players[i];
	}
	return NULL;
}

// Get player by steamid
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::GetPlayerBySteamID(const char *steamid)
{
	if(!steamid) return NULL;
	FOR_EACH_VEC(vec_players, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_players[i]->SteamID(), steamid))
			return vec_players[i];
	}
	return NULL;
}

// Get player by name
PLUGIN_PLAYER_CLASS *LIB_PLAYERMNGR_CLASS::GetPlayerByName(const char *name)
{
	if(!name) return NULL;
	FOR_EACH_VEC(vec_players, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_players[i]->PlayerInfo()->GetName(), name))
			return vec_players[i];
	}
	return NULL;
}

//=================================================================================
// Utilities
//=================================================================================
// Get players count on the list
int LIB_PLAYERMNGR_CLASS::Count()
{
	return vec_players.Count();
}

// Print all players on the list to console
void LIB_PLAYERMNGR_CLASS::PrintPlayers()
{
	Msg("\nPlayers List\nTotal Players: %i\n\n-----------------------------\n", vec_players.Count());
	FOR_EACH_VEC(vec_players, i)
	{
		Msg("I:%i U:%i E:%i \"%s\" %s\n", vec_players[i]->Index(), vec_players[i]->UserID(), vec_players[i]->Edict(), vec_players[i]->PlayerInfo()->GetName(), vec_players[i]->SteamID());
	} 
	Msg("-----------------------------\n");
}

//=================================================================================
// Global variable
//=================================================================================
LIB_PLAYERMNGR_CLASS *VAR_LIB_PLAYERMNGR = NULL;

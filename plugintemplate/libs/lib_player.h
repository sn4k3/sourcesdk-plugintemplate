#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H
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
// Defines
//=================================================================================
#define LIB_PLAYER_VERSION "1.0"
#define LIB_PLAYER_CLASS CPlayer

//=================================================================================
// Class
//=================================================================================
class LIB_PLAYER_CLASS
{
public:
	// Constructor
	LIB_PLAYER_CLASS();

	// Constructor, when used a valid userid, index got ignored
	LIB_PLAYER_CLASS(int index, int userid = 0);

	// Constructor
	LIB_PLAYER_CLASS(edict_t *pEdict);

	// Destructor
	~LIB_PLAYER_CLASS();

	// Invalidate class
	void Reset();

	// Return true if this class is valid, otherwise false (invalid player, entity, ...)
	virtual bool IsValid();

	// Find a player and initalize this class with founded player
	// Class will invalidate if player was not found
	bool FindPlayer(int playerindex);

	// Find a player and initalize this class with founded player
	// Class will invalidate if player was not found
	bool FindPlayer(edict_t *pEdict);

	// Find a player and initalize this class with founded player
	// Class will invalidate if player was not found
	bool FindPlayerByUserID(int userid);

	// Is player a Bot?
	bool IsBot();

	// Check if the player is within a radius of vector target
	bool IsWithinRadius(Vector vecTarget, float fRadius);

	// Is player alive?
	bool IsAlive();

	// Get a translation based in the player game language
	// If safe is true, returns the DEFAULT if the language was not translated
	// Require Lang Lib
	const char *GetTranslation(const char *nameSpace, const char *phrase, bool safe = true);

	// Kill player.
	virtual void Kill();

	// Disconnect a player with a reason
	virtual bool Disconnect(const char *reason);

	// Force client to reconnect without droping the netchannel
	virtual bool Reconnect();

	// Check if entity is a valid player, and return IPlayerInfo*, NULL if not
	static IPlayerInfo *IsPlayer(edict_t *pEdict, bool onlyHumans = false);

	// Is player alive?
	static bool IsAlive(edict_t *pEntity);

	// Disconnect a player with a reason
	static bool Disconnect(edict_t *pEntity, const char *reason);

	// Force client to reconnect without droping the netchannel
	static bool Reconnect(edict_t *pEntity);

	// Execute a command on client.
	// Filters allowed
	static bool Cexec(const char *players, const char *command, ...);

	// Execute a command on client.
	static bool Cexec(edict_t *pEntity, const char *command, ...);

	// Execute a command on client.
	// Filters allowed
	static bool Sexec(const char *players, const char *command, ...);

	// Execute a command on client.
	static bool Sexec(edict_t *pEntity, const char *command, ...);

	// Convert STEAMID to Steam Community ID
	// Thanks to voogru, http://forums.alliedmods.net/showthread.php?t=60899
	static __int64 GetCommunityID(const char *pszAuthID);

	// Private Accessors

	// Player index
	inline int				Index()				const {return m_iIndex;} 

	// Player userid
	inline int				UserID()			const {return m_iUserid;}

	// Player edict
	inline edict_t			*Edict()			const {return m_hEdict;} 

	// Player info
	inline IPlayerInfo		*PlayerInfo()		const {return m_iPlayerinfo;} 

	// Player baseentity
	inline CBaseEntity		*BaseEntity()		const {return m_iCBaseEntity;} 

	// Player net channel info, ie. ping, ip ...
	// Note: Dont work on BOTS!!!!! NULL
	inline INetChannelInfo	*NetChannelInfo()	const {return m_iNetChannelInfo;} 

	// Player steamid
	inline const char		*SteamID()			const {return m_szSteamid;} 



private:
	int m_iIndex;
	int m_iUserid;
	edict_t* m_hEdict;
	IPlayerInfo *m_iPlayerinfo;
	CBaseEntity *m_iCBaseEntity;
	INetChannelInfo *m_iNetChannelInfo;

	const char *m_szSteamid;

	bool b_isvalid;
};

//=================================================================================
// Includes
//=================================================================================
#include "plugin_player.h"

//=================================================================================
// Defines
//=================================================================================
#define LIB_PLAYERMNGR_VERSION "1.0"
#define LIB_PLAYERMNGR_CLASS CPlayerMngr

//=================================================================================
// Class
//=================================================================================
class LIB_PLAYERMNGR_CLASS
{
public:
	PLUGIN_PLAYER_CLASS *operator [](int playerindex);
	PLUGIN_PLAYER_CLASS *operator [](edict_t *pEntity);

	LIB_PLAYERMNGR_CLASS();
	~LIB_PLAYERMNGR_CLASS();

	// Remove all players from list
	void Reset();

	// Add a client to list from player index
	bool AddClient(int playerindex);

	// Add a client to list from player edict
	bool AddClient(edict_t *pEntity);

	// Add a client to list from player userid
	bool AddClientByUserID(int userid);

	// Remove a client to list from player index
	bool RemoveClient(int playerindex);

	// Remove a client to list from player edict
	bool RemoveClient(edict_t *pEntity);

	// Remove a client to list from player userid
	bool RemoveClientByUserID(int userid);

	// Get player by his index
	PLUGIN_PLAYER_CLASS *GetPlayer(int playerindex);

	// Get player by edict
	PLUGIN_PLAYER_CLASS *GetPlayer(edict_t *pEntity);

	// Get player by userid
	PLUGIN_PLAYER_CLASS *GetPlayerByUserID(int userid);

	// Get player by steamid
	PLUGIN_PLAYER_CLASS *GetPlayerBySteamID(const char *steamid);

	// Get player by name
	PLUGIN_PLAYER_CLASS *GetPlayerByName(const char *name);

	// Get players count on the list
	int Count();

	// Print all players on the list to console
	virtual void PrintPlayers();
	
	// Players list
	// Use to loop only
	CUtlVector<PLUGIN_PLAYER_CLASS *> vec_players;
};

//=================================================================================
// extern global variable
//=================================================================================
extern LIB_PLAYERMNGR_CLASS *VAR_LIB_PLAYERMNGR;

#endif
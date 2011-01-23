#ifndef _MRECIPIENT_FILTER_H 
#define _MRECIPIENT_FILTER_H 
#include "irecipientfilter.h"
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_MRECIPIENTFILTER_VERSION "1.0"
#define LIB_MRECIPIENTFILTER_CLASS MRecipientFilter

enum PlayerState { Unas, Spec, Terror, Countert, All, Bot, Human, Live, Dead, ERROR_s };
class LIB_MRECIPIENTFILTER_CLASS : 
   public IRecipientFilter 
{ 
public: 
	// MRecipientFilter Constructors.
	LIB_MRECIPIENTFILTER_CLASS(void);

	// Delete MRecipientFilter.
	~LIB_MRECIPIENTFILTER_CLASS(void);

	// Is reliable.
	// Not used.
	virtual bool IsReliable( void ) const; 

	// Is init message
	// Not used.
	virtual bool IsInitMessage( void ) const; 

	// Get players count.
	virtual int GetRecipientCount( void ) const; 

	// Get recipient index.
	// Player Index.
	virtual int GetRecipientIndex( int slot ) const; 

	// Get pEntity from recipient index.
	edict_t *GetRecipientEdict(int slot);

	// Get CBaseEntity from recipient index.
	CBaseEntity *GetRecipientBaseEntity(int slot);

	// Add players by filter.
	// # for begin a player filter.
	// ! for remove a player filter.
	// a = All players.
	// u or 0 = Unsigned Team.
	// s or 1 = Spectator Team.
	// t or 2 = Terrorist Team (Team 2)
	// c or 3 = Countert-Terrorist Team (Team 3)
	// b = Bots
	// h = humman players.
	// l = Living players.
	// d = Dead players.
	//
	// if '|' is the first char on the filter string, partial will be activated (set to true)
	// Set 'forceDisablePartial' to true for disable so, (filter string can't activate partial '|' itself)
	//
	// Also support player names, userid, steamid with multi players.
	// "2 3 4 playername STEAM_1:1:25416446" OR "2" OR "STEAM_0:0:1111" OR "nameonly"
	// Multi players are only recomendate for Userids and SteamIds, players name sometimes have spaces.
	//
	// 'Partial' allow you add players by steam or by name with partial name eg
	// eg. true player name: "my name is player" in partial can be "my " or "my name" ...
	//
	// Return player count.
	int AddByFilter(const char *filter, bool partial = true, bool forceDisablePartial = false); 

	// Add all players.
	void AddAllPlayers(); 

	// Add add dead players.
	void AddAllDeadPlayers();

	// Add all alive players.
	void AddAllAlivePlayers();

	// Add all humans players
	void AddAllHumans(); 

	// Add all Humans by team.
	void AddAllTeamHumans(int TeamIndex);

	// Add all players within a radius
	void AddWithinRadius(Vector vecTarget, float fRadius);

	// Add player.
	bool AddRecipient (int iPlayer);

	// Add by player slot.
	void AddBySlot(int slot);

	// Add by player Entity.
	bool AddByEntity(edict_t *pEntity);

	// Remove all saved players.
	void RemoveAll();

private: 

	// Is Reliable
	bool m_bReliable; 

   // Init Message
   bool m_bInitMessage; 

   // Filters Enum
   PlayerState TeamToEnum(char teamselection);

   // Player data
   CUtlVector<int> m_Recipients; 
}; 

#endif 


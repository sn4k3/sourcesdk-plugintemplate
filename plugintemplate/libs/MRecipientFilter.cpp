//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_string.h"
#include "libs/lib_entity.h"
#include "libs/MRecipientFilter.h"

//extern IPlayerInfoManager *VAR_IFACE_PLAYERINFOMANAGER;

PlayerState LIB_MRECIPIENTFILTER_CLASS::TeamToEnum(char teamselection)
{
	teamselection = toupper(teamselection);
	if(teamselection == 'A')
	return All;
	if(teamselection == '0')
	return Unas;
	if(teamselection == '1')
	return Spec;
	if(teamselection == '2')
	return Terror;
	if(teamselection == '3')
	return Countert;
	if(teamselection == 'T')
	return Terror;
	if(teamselection == 'C')
	return Countert;
	if(teamselection == 'S')
	return Spec;
	if(teamselection == 'U')
	return Unas;
	if(teamselection == 'B')
	return Bot;
	if(teamselection == 'H')
	return Human;
	if(teamselection == 'L')
	return Live;
	if(teamselection == 'D')
	return Dead;
	return ERROR_s;
}


LIB_MRECIPIENTFILTER_CLASS::LIB_MRECIPIENTFILTER_CLASS(void) 
{ 
} 

LIB_MRECIPIENTFILTER_CLASS::~LIB_MRECIPIENTFILTER_CLASS(void) 
{
	RemoveAll();
	m_Recipients.~CUtlVector();
} 

int LIB_MRECIPIENTFILTER_CLASS::GetRecipientCount() const 
{ 
	return m_Recipients.Count(); 
} 

int LIB_MRECIPIENTFILTER_CLASS::GetRecipientIndex(int slot) const 
{ 
   if ( slot < 0 || slot >= GetRecipientCount() ) 
      return -1; 

   return m_Recipients[ slot ]; 
}

edict_t *LIB_MRECIPIENTFILTER_CLASS::GetRecipientEdict(int slot) 
{ 
   if ( slot < 0 || slot >= GetRecipientCount() ) 
      return NULL; 

   return PEntityOfEntIndex(m_Recipients[slot]); 
}

CBaseEntity *LIB_MRECIPIENTFILTER_CLASS::GetRecipientBaseEntity(int slot) 
{ 
	return LIB_ENTITY_CLASS::GetBaseEntityfromEntity(GetRecipientEdict(slot));
}

bool LIB_MRECIPIENTFILTER_CLASS::IsInitMessage() const 
{ 
   return false; 
} 

bool LIB_MRECIPIENTFILTER_CLASS::IsReliable() const 
{ 
   return false; 
} 

int LIB_MRECIPIENTFILTER_CLASS::AddByFilter(const char *filter, bool partial /*= true*/, bool forceDisablePartial /*= false*/) 
{ 
	m_Recipients.RemoveAll(); 
	edict_t *pEntity;
	IPlayerInfo *playerinfo;
	int slot;
	bool addT = false;
	bool addCT = false;
	bool addUnas = false;
	bool addSpec = false;
	bool addDead = false;
	bool addAlive = false;
	bool addHuman = false;
	bool addBots = false;

	unsigned int filterlen = strlen(filter);
	if (filter[0] == '#') // Get By Filter
	{
		for(unsigned int i = 1; i < filterlen; i++) {
			if(filter[i] == '!') continue;

			if(filter[i-1] == '!')
			{
				if (TeamToEnum(filter[i]) == All){ addT = false; addCT = false; addUnas = false; addSpec = false; addDead = false; addAlive = false; addHuman = false; addBots = false; }
				else if (TeamToEnum(filter[i]) == Unas){ addUnas = false; }
				else if (TeamToEnum(filter[i]) == Spec){ addSpec = false; }
				else if (TeamToEnum(filter[i]) == Terror){ addT = false; }
				else if (TeamToEnum(filter[i]) == Countert){ addCT = false; }
				else if (TeamToEnum(filter[i]) == Bot){ addBots = false; }
				else if (TeamToEnum(filter[i]) == Human){ addHuman = false; }
				else if (TeamToEnum(filter[i]) == Live){ addAlive = false; }
				else if (TeamToEnum(filter[i]) == Dead){ addDead = false; }
				else if (TeamToEnum(filter[i]) == ERROR_s){ Msg("Unknown Group Selection \"%c\"\n", filter[i]); }
				//i++;
				if(filter[i] != '\0' && filter[i] != ' ')
					break;
			}else{
				if (TeamToEnum(filter[i]) == All){ addT = true; addCT = true; addUnas = true; addSpec = true; addDead = true; addAlive = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Unas){ addUnas = true; addDead = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Spec){ addSpec = true; addDead = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Terror){ addT = true; addCT = false; addDead = true; addAlive = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Countert){ addT = false; addCT = true; addDead = true; addAlive = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Bot){ addT = true; addCT = true; addUnas = true; addSpec = true; addDead = true; addAlive = true; addHuman = false; addBots = true; }
				else if (TeamToEnum(filter[i]) == Human){ addT = true; addCT = true; addUnas = true; addSpec = true; addDead = true; addAlive = true; addHuman = true; addBots = false; }
				else if (TeamToEnum(filter[i]) == Live){ addT = true; addCT = true; addAlive = true; addDead = false; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == Dead){ addT = true; addCT = true; addUnas = true; addSpec = true; addAlive = false; addDead = true; addHuman = true; addBots = true; }
				else if (TeamToEnum(filter[i]) == ERROR_s){ Msg("Unknown Group Selection \"%c\"\n", filter[i]); }
			}
			if (!addT && !addCT && !addSpec && !addDead && !addAlive && !addHuman && !addBots)
				return 0;
		}
		for (slot=1; slot<= VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
		{ 
			edict_t *pEntity = PEntityOfEntIndex(slot); 
			IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
			if ( !pEntity || pEntity->IsFree() || !playerinfo || !playerinfo->IsPlayer() || !playerinfo->IsConnected()) { 
				continue; 
			} 
			if(!addUnas && playerinfo->GetTeamIndex() == 0){ continue; }
			if(!addSpec && playerinfo->GetTeamIndex() == 1){ continue; }
			if(!addT && playerinfo->GetTeamIndex() == 2){ continue; }
			if(!addCT && playerinfo->GetTeamIndex() == 3){ continue; }
			if(!addDead && playerinfo->IsDead()){ continue; }
			if(!addAlive && !playerinfo->IsDead()){ continue; }
			if(!addHuman && !playerinfo->IsFakeClient()){ continue; }
			if(!addBots && playerinfo->IsFakeClient()){ continue; }
			AddRecipient(slot);
	   }
		return m_Recipients.Count();
	}

	if(filter[0] == '|') // Activate Partial
	{
		if(filterlen > 1)
		{
			filter = LIB_STRING_CLASS::SubStr(filter, 1, filterlen);
			if(!forceDisablePartial) // | char cant activate partial :(
				partial = true;
		}
	}
	CUtlVector<const char *>* tokens = LIB_STRING_CLASS::StrSplit(filter, ' ');
	if(tokens->Count() == 0)
		return m_Recipients.Count();

	for(int i = 0; i < tokens->Count(); i++)
	{
		const char *token = tokens->Element(i);
		if(LIB_STRING_CLASS::StrIsInt(token))  // Get by userid
		{

			int userid = atoi(token);
			for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
			{
				pEntity = PEntityOfEntIndex(slot);
				if(!pEntity || pEntity->IsFree()) continue;
				playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
				if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;

				if(playerinfo->GetUserID()!=userid) continue;

				AddRecipient(slot); 
				break;
			}
			continue;
		}
		if(!strnicmp(token, "STEAM_", 6) || stricmp(token, "BOT") == 0) // Get By STEAM_
		{
			const char *steamid = LIB_STRING_CLASS::StrToUpper(token);
			for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
			{
				pEntity = PEntityOfEntIndex(slot);
				if(!pEntity || pEntity->IsFree()) continue;
				playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
				if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;
				if(!partial)
				{
					if(strcmp(steamid, playerinfo->GetNetworkIDString())) continue;
				} else {
					//if(!strstr(steamid, playerinfo->GetNetworkIDString())) continue;
					if(strnicmp(playerinfo->GetNetworkIDString(), steamid, strlen(steamid))) continue;
				}
				m_Recipients.AddToTail(slot);
			}
			continue;
		}
		// Finally get by name
		for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
		{
			pEntity = PEntityOfEntIndex(slot);
			if(!pEntity || pEntity->IsFree()) continue;
			playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
			if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;

			if(!partial)
			{
				if(strcmp(playerinfo->GetName(), token)) continue;
			} else {
				if(!strstr(playerinfo->GetName(), token)) continue;
			}

			AddRecipient(slot); 
		}
		continue;
	}

	// OLD WAY
	/*char parttoken[1024];
	filter = (char *)LIB_ENTITY_CLASS::StrNextToken(parttoken, filter, ' ');
	while(strlen(parttoken) > 0)
	{
		if(LIB_ENTITY_CLASS::StrIsInt(parttoken))  // Get by userid
		{

			int userid = atoi(parttoken);
			for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
			{
				pEntity = PEntityOfEntIndex(slot);
				if(!pEntity || pEntity->IsFree()) continue;
				playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
				if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;

				if(playerinfo->GetUserID()!=userid) continue;

				AddRecipient(slot); 
				break;
			}
			filter = (char *)LIB_ENTITY_CLASS::StrNextToken(parttoken, filter, ' ');
			continue;
		}
		if(!strnicmp(parttoken, "STEAM_", 6) || stricmp(parttoken, "BOT") == 0) // Get By STEAM_
		{
			strncpy(parttoken, LIB_ENTITY_CLASS::StrToUpper(parttoken), 1024);
			for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
			{
				pEntity = PEntityOfEntIndex(slot);
				if(!pEntity || pEntity->IsFree()) continue;
				playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
				if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;
				if(!partial)
				{
					if(strcmp(parttoken, playerinfo->GetNetworkIDString())) continue;
				} else {
					if(!strstr(parttoken, playerinfo->GetNetworkIDString())) continue;
				}
				m_Recipients.AddToTail(slot);
			}
			filter = (char *)LIB_ENTITY_CLASS::StrNextToken(parttoken, filter, ' ');
			continue;
		}
		// Get By Name
		for(slot=1; slot <= VAR_IFACE_GLOBALVARS->maxClients; slot++)
		{
			pEntity = PEntityOfEntIndex(slot);
			if(!pEntity || pEntity->IsFree()) continue;
			playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
			if(!playerinfo || !playerinfo->IsConnected() || !playerinfo->IsPlayer()) continue;

			if(!partial)
			{
				if(strcmp(playerinfo->GetName(), parttoken)) continue;
			} else {
				if(!strstr(playerinfo->GetName(), parttoken)) continue;
			}

			AddRecipient(slot); 
		}
		filter = (char *)LIB_ENTITY_CLASS::StrNextToken(parttoken, filter, ' ');
		continue;
	}*/
	return m_Recipients.Count();
} 

void LIB_MRECIPIENTFILTER_CLASS::AddAllPlayers() 
{ 
   m_Recipients.RemoveAll(); 
   int slot; 
   for (slot=1; slot<= VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
   { 
      edict_t *pEntity = PEntityOfEntIndex(slot); 
      IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
      if ( !pEntity || pEntity->IsFree() || !playerinfo || !playerinfo->IsPlayer() \
		  || !playerinfo->IsConnected() ) {
         continue; 
      } 
      //AddRecipient( pPlayer ); 
      m_Recipients.AddToTail(slot); 
   } 
} 

void LIB_MRECIPIENTFILTER_CLASS::AddAllDeadPlayers() 
{ 
   m_Recipients.RemoveAll(); 
   int slot; 
   for (slot=1; slot<=VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
   { 
      edict_t *pEntity = PEntityOfEntIndex(slot); 
      IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
      if ( !pEntity || pEntity->IsFree() || !playerinfo->IsDead() || !playerinfo || !playerinfo->IsPlayer() \
		  || !playerinfo->IsConnected() ) {
         continue; 
      } 
      //AddRecipient( pPlayer ); 
      m_Recipients.AddToTail(slot); 
   } 
} 

void LIB_MRECIPIENTFILTER_CLASS::AddAllAlivePlayers() 
{ 
   m_Recipients.RemoveAll(); 
   int slot; 
   for (slot=1; slot<=VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
   { 
      edict_t *pEntity = PEntityOfEntIndex(slot); 
      IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
      if ( !pEntity || pEntity->IsFree() || playerinfo->IsDead() || !playerinfo || !playerinfo->IsPlayer() \
		  || !playerinfo->IsConnected() ) {
         continue; 
      } 
      //AddRecipient( pPlayer ); 
      m_Recipients.AddToTail(slot); 
   } 
} 

void LIB_MRECIPIENTFILTER_CLASS::AddAllHumans() 
{ 
   m_Recipients.RemoveAll(); 
   int slot; 
   for (slot=1; slot<=VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
   { 
      edict_t *pEntity = PEntityOfEntIndex(slot); 
      IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
      if ( !pEntity || pEntity->IsFree() || !playerinfo || !playerinfo->IsPlayer() \
		  || !playerinfo->IsConnected() || playerinfo->IsFakeClient()) { 
         continue; 
      } 
      //AddRecipient( pPlayer ); 
      m_Recipients.AddToTail(slot); 
   }
} 

void LIB_MRECIPIENTFILTER_CLASS::AddAllTeamHumans(int TeamIndex) 
{ 
   m_Recipients.RemoveAll(); 
   int slot; 
   for (slot=1; slot<=VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
   { 
      edict_t *pEntity = PEntityOfEntIndex(slot); 
      IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
      if ( !pEntity || pEntity->IsFree() || !playerinfo || !playerinfo->IsPlayer() \
		  || playerinfo->GetTeamIndex() == TeamIndex || !playerinfo->IsConnected() || playerinfo->IsFakeClient()) { 
         continue; 
      } 
      //AddRecipient( pPlayer ); 
      m_Recipients.AddToTail(slot); 
   } 
}

void LIB_MRECIPIENTFILTER_CLASS::AddWithinRadius(Vector vecTarget, float fRadius)
{
	m_Recipients.RemoveAll(); 
	Vector vecResult;
	for (int slot=1; slot<=VAR_IFACE_GLOBALVARS->maxClients; slot++ ) 
	{ 
	  edict_t *pEntity = PEntityOfEntIndex(slot); 
	  IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
	  if (!pEntity || pEntity->IsFree() || !playerinfo || !playerinfo->IsPlayer() || !playerinfo->IsConnected())
         continue; 
	  if (LIB_ENTITY_CLASS::IsWithinRadius(playerinfo->GetAbsOrigin(), vecTarget, fRadius))
	 	  m_Recipients.AddToTail(slot); 
	} 
}

void LIB_MRECIPIENTFILTER_CLASS::AddBySlot(int slot)
{
	// calling code needs to make sure that no duplicates are inserted
	// and that the slot is valid
	m_Recipients.AddToTail(slot);
}

bool LIB_MRECIPIENTFILTER_CLASS::AddByEntity(edict_t *pEntity)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	return AddRecipient(IndexOfEdict(pEntity));
}

bool LIB_MRECIPIENTFILTER_CLASS::AddRecipient(int iPlayer)
{
   // Already in list
	if ( m_Recipients.Find(iPlayer) != m_Recipients.InvalidIndex() )
      return false;

   m_Recipients.AddToTail( iPlayer );
   return true;
}

void LIB_MRECIPIENTFILTER_CLASS::RemoveAll()
{
	m_Recipients.RemoveAll();
	return;
}
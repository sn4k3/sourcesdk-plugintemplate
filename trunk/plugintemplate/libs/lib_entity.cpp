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
#include "libs/lib_entity.h"
#include "tier0/memdbgon.h"

// Get entity index from userid
int LIB_ENTITY_CLASS::GetIndexFromUserID(int userid)
{
   edict_t *pEntity;
   IPlayerInfo *info;
   for(int i = 1; i <= VAR_IFACE_GLOBALVARS->maxClients; i++)
   {
      pEntity = PEntityOfEntIndex(i);
      if (!IsEntitySafe(pEntity)) continue;

      info = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);

      if(info->GetUserID() == userid)
         return i;
   }
   return 0;
}

// Get entity from userid
edict_t *LIB_ENTITY_CLASS::GetEntityFromUserID(int userid)
{
   edict_t *pEntity;
   IPlayerInfo *info;
   for(int i = 1; i <= VAR_IFACE_GLOBALVARS->maxClients; i++)
   {
      pEntity = PEntityOfEntIndex(i);
      if (!IsEntitySafe(pEntity)) continue;

      info = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);

      if(info->GetUserID() == userid)
         return pEntity;
   }
   return NULL;
}

// Get pEntity from CBaseEntity.
edict_t *LIB_ENTITY_CLASS::GetEntityFromBaseEntity(CBaseEntity *cbe)
{
	
#ifdef USE_IFACE_SERVERGAMEENTS
	if(!cbe) return NULL;
	if(!VAR_IFACE_SERVERGAMEENTS) return NULL;
	return VAR_IFACE_SERVERGAMEENTS->BaseEntityToEdict(cbe);
#else
	Msg("[WARNING] IServerGameEnts interface is disabled!\n");
	return NULL;
#endif	
}

// Get IPlayerinfo from pEntity.
IPlayerInfo *LIB_ENTITY_CLASS::GetPlayerinfoFromEntity(edict_t *pEntity)
{
	if (!IsEntitySafe(pEntity)) return NULL;
	IPlayerInfo *playerinfo = VAR_IFACE_PLAYERINFOMANAGER->GetPlayerInfo(pEntity);
	if(!playerinfo)
		return NULL;
	if(!playerinfo->IsPlayer())
		return NULL;
	if(!playerinfo->IsConnected())
		return NULL;
	return playerinfo;
}

// Get CBaseEntity from pEntity.
CBaseEntity *LIB_ENTITY_CLASS::GetBaseEntityfromEntity(edict_t *pEntity)
{
	if (!IsEntitySafe(pEntity)) return NULL;
#ifdef USE_IFACE_SERVERGAMEENTS
	if(VAR_IFACE_SERVERGAMEENTS) return VAR_IFACE_SERVERGAMEENTS->EdictToBaseEntity(pEntity);
#endif
	return pEntity->GetUnknown()->GetBaseEntity();
}

// Get edict_t from a Handle
edict_t *LIB_ENTITY_CLASS::GetEntityFromEHandle(const CBaseHandle& handle)
{
	edict_t *pEntity = PEntityOfEntIndex(handle.GetEntryIndex());
	if (!IsEntitySafe(pEntity)) return NULL;
	return pEntity;
}

// Get CBaseEntity from a Handle
CBaseEntity *LIB_ENTITY_CLASS::GetBaseEntityFromEHandle(const CBaseHandle& handle)
{
	return GetBaseEntityfromEntity(PEntityOfEntIndex(handle.GetEntryIndex()));	
}

// Get CPlayerState from pEntity.
CPlayerState *LIB_ENTITY_CLASS::GetPlayerStatefromEdict(edict_t *pEntity)
{
#ifdef USE_IFACE_SERVERCLIENTS
	if (!IsEntitySafe(pEntity)) return NULL;
	if(!VAR_IFACE_SERVERCLIENTS) return NULL;
	return serverclients->GetPlayerState(pEntity);
#else
	Msg("[WARNING] IServerGameClients interface is disabled!\n");
	return NULL;
#endif
}

// Get random player entity
// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
edict_t *LIB_ENTITY_CLASS::GetEntityOfRandPlayer(const char *players, bool partial /*= false*/)
{
#ifndef USE_IFACE_RANDOMSTREAM
	Msg("[WARNING] IUniformRandomStream interface is disabled!\n");
	return NULL;
#else
	if(!VAR_IFACE_RANDOMSTREAM) return NULL;
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return NULL;
	return PEntityOfEntIndex(mrf.GetRecipientIndex(VAR_IFACE_RANDOMSTREAM->RandomInt(0, mrf.GetRecipientCount()-1)));
#endif
}

// Get random player index
// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
int LIB_ENTITY_CLASS::GetIndexOfRandPlayer(const char *players, bool partial /*= false*/)
{
#ifndef USE_IFACE_RANDOMSTREAM
	Msg("[WARNING] IUniformRandomStream interface is disabled!\n");
	return -1;
#else
	if(!VAR_IFACE_RANDOMSTREAM)
		return -1;
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return 0;
	return mrf.GetRecipientIndex(VAR_IFACE_RANDOMSTREAM->RandomInt(0, mrf.GetRecipientCount()-1));
#endif
}

// Get players count.
// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
unsigned int LIB_ENTITY_CLASS::GetPlayerCount(const char *players, bool partial /*= false*/)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	return mrf.AddByFilter(players, partial);
}


// Convert CBaseCombatWeapon to string
/*char *CEntityLib::GetBaseCombatWeaponToStr(CBaseCombatWeapon *weapon)
{
	if (!weapon) return NULL;

	edict_t *pEntity = gameents->BaseEntityToEdict(weapon);
	if (!IsEntitySafe(pEntity)) return NULL;

	return const_cast<char*>(pEntity->GetClassName());
}*/



// Get the first entity found match a name.
edict_t *LIB_ENTITY_CLASS::GetFirstEntity(const char *pszName)
{
	edict_t *pEntity;

	for(int x = 0; x < VAR_IFACE_ENGINE->GetEntityCount(); x++)
	{
		pEntity = PEntityOfEntIndex(x);
		if(!pEntity) continue;

		if(LIB_STRING_CLASS::FStrEq(pEntity->GetClassName(), pszName))
			return pEntity;
	}
	return NULL;
}

// Get a list of entitys found match a name.
CUtlVector<edict_t *>* LIB_ENTITY_CLASS::GetEntitys(const char *pszName)
{
	CUtlVector<edict_t *>* vec = new CUtlVector<edict_t *>;
	edict_t *pEntity;

	for(int x = 0; x < VAR_IFACE_ENGINE->GetEntityCount(); x++)
	{
		pEntity = PEntityOfEntIndex(x);
		if(!pEntity) continue;

		if(LIB_STRING_CLASS::FStrEq(pEntity->GetClassName(), pszName))
			vec->AddToTail(pEntity);
	}
	return vec;
}

// Get the count of entitys found match a name.
unsigned int LIB_ENTITY_CLASS::GetEntityCount(const char *pszName)
{
	edict_t *pEntity;
	unsigned int i = 0;
	for(int x = 0; x < VAR_IFACE_ENGINE->GetEntityCount(); x++)
	{
		pEntity = PEntityOfEntIndex(x);
		if(!pEntity) continue;

		if(LIB_STRING_CLASS::FStrEq(pEntity->GetClassName(), pszName))
			i++;
	}
	return i;
}

// Check if the vector dest is within a radius of vector target
bool LIB_ENTITY_CLASS::IsWithinRadius(Vector vecDest, Vector vecTarget, float fRadius)
{
	 Vector vecResult = vecDest-vecTarget;
	 return (vecResult.Length() < fRadius);
}

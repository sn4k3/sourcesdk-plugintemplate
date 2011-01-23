#ifndef LIB_ENTITY_H
#define LIB_ENTITY_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_ENTITY_VERSION "1.0"
#define LIB_ENTITY_CLASS CEntityLib

class LIB_ENTITY_CLASS
{
public:
	// Is a entity safe?
	static inline bool IsEntitySafe(edict_t *pEntity)
	{
		if(pEntity)
			if(!pEntity->IsFree())
				if(pEntity->GetUnknown())
					return true;
		return false;
	}

	// Get entity index from userid.
	static int GetIndexFromUserID(int userid);

	// Get entity from userid
	static edict_t *GetEntityFromUserID(int userid);

	// Get pEntity from CBaseEntity.
	static edict_t *GetEntityFromBaseEntity(CBaseEntity *cbe);

	// Get IPlayerinfo from pEntity.
	static IPlayerInfo *GetPlayerinfoFromEntity(edict_t *pEntity);

	// Get CBaseEntity from pEntity.
	static CBaseEntity *GetBaseEntityfromEntity(edict_t *pEntity);

	// Get edict_t from a Handle
	static edict_t *GetEntityFromEHandle(const CBaseHandle& handle);

	// Get CBaseEntity from a Handle
	static CBaseEntity *GetBaseEntityFromEHandle(const CBaseHandle& handle);

	// Get CPlayerState from pEntity.
	static CPlayerState *GetPlayerStatefromEdict(edict_t *pEntity);

	// Get random player entity
	// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
	static edict_t *GetEntityOfRandPlayer(const char *players, bool partial = false);

	// Get random player index
	// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
	static int GetIndexOfRandPlayer(const char *players, bool partial = false);

	// Get players count.
	// Use Filters format: #a, #t, #c, #a!d, #a!b!d, ... STEAM_ ... USERID .... playernames 
	static unsigned int GetPlayerCount(const char *players, bool partial = false);
	
	// Convert CBaseCombatWeapon to string
	/*char *GetBaseCombatWeaponToStr(CBaseCombatWeapon *weapon);*/

	// Is player entity alive?
	static bool IsAlive(edict_t *pEntity);

	// Get the first entity found match a name.
	static edict_t *GetFirstEntity(const char *pszName);

	// Get a list of entitys found match a name
	static CUtlVector<edict_t *>* GetEntitys(const char *pszName);

	// Get the count of entitys found match a name.
	static unsigned int GetEntityCount(const char *pszName);

	// Check if the vector dest is within a radius of vector target
	static bool IsWithinRadius(Vector vecDest, Vector vecTarget, float fRadius);


};

#endif
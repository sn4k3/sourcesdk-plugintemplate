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
#include "libs/lib_vfuncs.h"

// Load vfuncs names and offsets from a KeyValue
bool LIB_VFUNCS_CLASS::Load(KeyValues *kvVFuncs)
{
	if(!kvVFuncs) return false;
	if(kvVFuncs->IsEmpty())
	{
		//kvVFuncs->deleteThis();
		return true;
	}
	KeyValues *kvLoop;
	for(kvLoop = kvVFuncs->GetFirstSubKey(); kvLoop; kvLoop = kvLoop->GetNextKey())
	{
		if(kvLoop->GetInt("enable", 1) <= 0) continue; // Not enabled
		const char *name = kvLoop->GetName();
		if(!name) continue; // No Name

#ifdef WIN32
		int offset = kvLoop->GetInt("windows", -1);
		if(offset == -1) 
		{
			DevMsg("[WARNING] VFuncs: %s got no offset, skip this\n", name);
			continue; // No Offset
		}
		AddOrReplace(name, offset);
#else
		bool isWindowsOffset = false;
		int offset = kvLoop->GetInt("linux", -1);
		if(offset == -1)
		{
			offset = kvLoop->GetInt("windows", -1);
			if(offset == -1) 
			{
				DevMsg("[WARNING] VFuncs: %s got no offset, skip this\n", name);
				continue; // No Offset
			}
			isWindowsOffset = true;
		}
		AddOrReplace(name, offset, isWindowsOffset);
#endif
		//kvLoop->deleteThis();
	}
	//kvVFuncs->deleteThis();
	return true;
}

bool LIB_VFUNCS_CLASS::Add(const char *name, int offset, bool offsetFromWindow /*= true*/)
{
	if(GetIndex(name) != -1)
		return false;
#ifndef WIN32
	if(offsetFromWindow)
		offset++;
#endif
	VFunc_t vfunc;
	vfunc.Name = name;
	vfunc.Offset = offset;
	vec_vfuncs.AddToTail(vfunc);
	DevMsg("VFunc: Adding %s to list, with %i as offset\n", name, offset);
	return true;
}

bool LIB_VFUNCS_CLASS::AddOrReplace(const char *name, int offset, bool offsetFromWindow /*= true*/)
{
	if(!Add(name, offset, offsetFromWindow))
		return ReplaceOffset(name, offset, offsetFromWindow);
	return true;
}

// Replace old offset for a new one
bool LIB_VFUNCS_CLASS::ReplaceOffset(const char *name, int newoffset, bool offsetFromWindow /*= true*/)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
#ifndef WIN32
	if(offsetFromWindow)
		newoffset++;
#endif
	vec_vfuncs[index].Offset = newoffset;
	return true;
}

bool LIB_VFUNCS_CLASS::Remove(const char *name)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
	vec_vfuncs.Remove(index);
	return true;
}

// Get the index of a named vfunc
int LIB_VFUNCS_CLASS::GetIndex(const char *name, ...)
{
	MULTIARGS(name);
	FOR_EACH_VEC(vec_vfuncs, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_vfuncs[i].Name, string))
			return i;
	}
	return -1;
}

// Get the offset of a named VFunc
int LIB_VFUNCS_CLASS::GetOffset(const char *name, ...)
{
	MULTIARGS(name);
	FOR_EACH_VEC(vec_vfuncs, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_vfuncs[i].Name, string))
			return vec_vfuncs[i].Offset;
	}
	return -1;
}

// Get how many VFuncs exists on the list
int LIB_VFUNCS_CLASS::GetCount() const
{
	return vec_vfuncs.Count();
}

/*********
  VFuncs
*********/

#ifdef WIN32
#pragma warning( disable : 4172 ) //warning C4172: returning address of local variable or temporary
#endif

// Get player eye angles
// virtual const QAngle &EyeAngles( void );
const QAngle &LIB_VFUNCS_CLASS::CBaseEntity_EyeAngles(edict_t *pEntity, const char *addressName /*= "CBaseEntity::EyeAngles"*/)
{
	return CBaseEntity_EyeAngles(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), addressName);
}

// Get player eye angles
// virtual const QAngle &EyeAngles( void );
const QAngle &LIB_VFUNCS_CLASS::CBaseEntity_EyeAngles(CBaseEntity *pBase, const char *addressName /*= "CBaseEntity::EyeAngles"*/)
{
	VFUNC_ASSERT_FUNCTION("CBaseEntity::EyeAngles", QAngle())
	VFUNC_0(pBase, iOffset, return, const QAngle &)
}


// Teleports a entity
// virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
bool LIB_VFUNCS_CLASS::CBaseEntity_Teleport(edict_t *pEntity, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName /*= "CBaseEntity::Teleport"*/)
{
	return CBaseEntity_Teleport(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), newPosition, newAngles, newVelocity, addressName);
}

// Teleports a entity
// virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
bool LIB_VFUNCS_CLASS::CBaseEntity_Teleport(CBaseEntity *pBase, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName /*= "CBaseEntity::Teleport"*/)
{
	VFUNC_ASSERT_FUNCTION("CBaseEntity::Teleport", false)
	VFUNC_3(pBase, iOffset, , void, const Vector *, newPosition, const QAngle *, newAngles, const Vector *, newVelocity)
	return true;
}

datamap_t *LIB_VFUNCS_CLASS::CBaseEntity_GetDataDescMap(edict_t *pEntity, const char *addressName /*= "CBaseEntity::GetDataDescMap"*/)
{
	return CBaseEntity_GetDataDescMap(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity));
}

datamap_t *LIB_VFUNCS_CLASS::CBaseEntity_GetDataDescMap(CBaseEntity *pBase, const char *addressName /*= "CBaseEntity::GetDataDescMap"*/)
{
	VFUNC_ASSERT_FUNCTION("CBaseEntity::GetDataDescMap", NULL);
	VFUNC_0(pBase, iOffset, return, datamap_t *); 
}
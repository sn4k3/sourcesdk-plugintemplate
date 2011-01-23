#ifndef LIB_VFUNCS_H
#define LIB_VFUNCS_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#define VFUNC_ASSERT_FUNCTION(_address, _return) \
	if(!pBase) return _return; \
	if(!addressName) \
		addressName = _address; \
	int iOffset = GetOffset(addressName, GamePlayer); \
	if (iOffset == -1) return _return;

#ifdef WIN32
	#define VFUNC_MAIN \
		void *addr; } u; u.addr = func;
#else
	#define VFUNC_MAIN \
		struct { void *addr; intptr_t adjustor; } s; } u; \
		u.s.addr = func; u.s.adjustor = 0;
#endif

#define VFUNC_BEGIN(p, o) \
	void **ptr = *(void ***)&p; \
	void **vtable = *(void ***)p; \
	void *func = vtable[o];

#define VFUNC_0(p, o, r1, r2) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(void); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)();

#define VFUNC_1(p, o, r1, r2, t1, v1) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1);

#define VFUNC_2(p, o, r1, r2, t1, v1, t2, v2) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2);

#define VFUNC_3(p, o, r1, r2, t1, v1, t2, v2, t3, v3) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3);

#define VFUNC_4(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4);

#define VFUNC_5(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5);

#define VFUNC_6(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5, v6);

#define VFUNC_7(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7);

#define VFUNC_8(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8);

#define VFUNC_9(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8, t9); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8, v9);

#define VFUNC_10(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) \
	VFUNC_BEGIN(p, o) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10); \
	VFUNC_MAIN \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(ptr)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);

#define LIB_VFUNCS_VERSION "1.0"
#define LIB_VFUNCS_CLASS CVFuncsLib
class LIB_VFUNCS_CLASS
{
public:
	// VFunc data, name and offset
	struct VFunc_t
	{
		const char *Name;
		int Offset;
	};

	// Load vfuncs names and offsets from KeyValue file
	virtual bool Load(KeyValues *kvVFuncs);

	// Adds a vfunc data to list
	// Under linux if offsetFromWindow is true, offset will be equal to: offset+1
	bool Add(const char *name, int offset, bool offsetFromWindow = true);

	// Try to add first, if vfunc already exist on the list, offset will be updated
	bool AddOrReplace(const char *name, int offset, bool offsetFromWindow = true);

	// Replace old offset for a new one
	bool ReplaceOffset(const char *name, int newoffset, bool offsetFromWindow = true);

	// Remove a vfunc from list
	bool Remove(const char *name);

	// Get the index of a named vfunc
	int GetIndex(const char *name, ...);

	// Get the offset of a named VFunc
	int GetOffset(const char *name, ...);

	// Get how many VFuncs exists on the list
	int GetCount() const;

	// VFUNCS

	// Get player eye angles
	// virtual const QAngle &EyeAngles( void );
	virtual const QAngle &CBaseEntity_EyeAngles(edict_t *pEntity, const char *addressName = "CBaseEntity::EyeAngles");

	// Get player eye angles
	// virtual const QAngle &EyeAngles( void );
	virtual const QAngle &CBaseEntity_EyeAngles(CBaseEntity *pBase, const char *addressName = "CBaseEntity::EyeAngles");
	
	// Teleports a entity
	// virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
	virtual bool CBaseEntity_Teleport(edict_t *pEntity, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName = "CBaseEntity::Teleport");

	// Teleports a entity
	// virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
	virtual bool CBaseEntity_Teleport(CBaseEntity *pBase, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName = "CBaseEntity::Teleport");

	virtual datamap_t *CBaseEntity_GetDataDescMap(edict_t *pEntity, const char *addressName = "CBaseEntity::GetDataDescMap");

	virtual datamap_t *CBaseEntity_GetDataDescMap(CBaseEntity *pBase, const char *addressName = "CBaseEntity::GetDataDescMap");

	// Holds all vfuncs
	// Use only to loop
	CUtlVector<VFunc_t> vec_vfuncs;

	const char *GamePlayer;
};

#endif

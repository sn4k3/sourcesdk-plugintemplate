#ifndef LIB_SIGSCAN_H
#define LIB_SIGSCAN_H
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
#ifndef WIN32
#include "lib_linuxutils.h"
#endif

//=================================================================================
// Defines
//=================================================================================
#define LIB_SIGSCAN_VERSION "1.0"
#define LIB_SIGSCAN_CLASS CSigScanLib

//=================================================================================
// Macros
//=================================================================================

#define SIGSCAN_ASSERT_FUNCTION(_address, _return) \
	if(!pBase) return _return; \
	if(!addressName) \
		addressName = _address; \
	void *pAddr = GetFunction(addressName, GamePlayer); \
	if (!pAddr) return _return;

#ifdef WIN32 /* GCC's member function pointers all contain a this pointer adjustor. You'd probably set it to 0 */
	#define SIGSCAN_END(o) \
		void *addr;	} u; 	u.addr = o;	
#else 
	#define SIGSCAN_END(o) \
		struct {void *addr; intptr_t adjustor;} s; } u; u.s.addr = o; u.s.adjustor = 0;
#endif


#define SIGSCAN_0(p, o, r1, r2) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(void); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)();

#define SIGSCAN_1(p, o, r1, r2, t1, v1) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1);

#define SIGSCAN_2(p, o, r1, r2, t1, v1, t2, v2) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2);

#define SIGSCAN_3(p, o, r1, r2, t1, v1, t2, v2, t3, v3) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3);

#define SIGSCAN_4(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4);

#define SIGSCAN_5(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5);

#define SIGSCAN_6(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5, v6);

#define SIGSCAN_7(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7);

#define SIGSCAN_8(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8);

#define SIGSCAN_9(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8, t9); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8, v9);

#define SIGSCAN_10(p, o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) \
	union { r2(CPlugin_EmptyClass::*mfpnew)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10); \
	SIGSCAN_END(o) \
	r1 (r2) (reinterpret_cast<CPlugin_EmptyClass*>(p)->*u.mfpnew)(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);

#define SIGSCAN_STATIC_0(o, r1, r2) \
	typedef r2 (*func)(); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc();

#define SIGSCAN_STATIC_1(o, r1, r2, t1, v1) \
	typedef r2 (*func)(t1); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1);

#define SIGSCAN_STATIC_2(o, r1, r2, t1, v1, t2, v2) \
	typedef r2 (*func)(t1, t2); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2);

#define SIGSCAN_STATIC_3(o, r1, r2, t1, v1, t2, v2, t3, v3) \
	typedef r2 (*func)(t1, t2, t3); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3);

#define SIGSCAN_STATIC_4(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4) \
	typedef r2 (*func)(t1, t2, t3, t4); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4);

#define SIGSCAN_STATIC_5(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
	typedef r2 (*func)(t1, t2, t3, t4, t5); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5);

#define SIGSCAN_STATIC_6(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) \
	typedef r2 (*func)(t1, t2, t3, t4, t5, t6); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5, v6);

#define SIGSCAN_STATIC_7(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) \
	typedef r2 (*func)(t1, t2, t3, t4, t5, t6, t7); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5, v6, v7);

#define SIGSCAN_STATIC_8(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) \
	typedef r2 (*func)(t1, t2, t3, t4, t5, t6, t7, t8); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5, v6, v7, v8);

#define SIGSCAN_STATIC_9(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) \
	typedef r2 (*func)(t1, t2, t3, t4, t5, t6, t7, t8, t9); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5, v6, v7, v8, v9);

#define SIGSCAN_STATIC_10(o, r1, r2, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) \
	typedef r2 (*func)(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10); \
	func thisfunc = (func)o; \
	r1 (r2) thisfunc(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);

//=================================================================================
// Class
//=================================================================================
class LIB_SIGSCAN_CLASS
{
public:
	// SigsScan Function
	struct SigScan_t
	{
		const char *Name;
		const char *Signature;	// Windows
		const char *Symbol;		// Linux
		void *pFunction;		// Address to function
	};

	LIB_SIGSCAN_CLASS();
	~LIB_SIGSCAN_CLASS();

	// Load signature configs from a KeyValues file
	bool Load(KeyValues *kvSigscan);

	// Add signature to list, but never write to file
	bool Add(const char *name, const char *signature, const char *symbol, void *pFunction);

	// Add or Replace a signature to list, but never write to file
	bool AddOrReplace(const char *name, const char *signature, const char *symbol, void *pFunction);

	// Replace a signature from list, but never write to file
	bool Replace(const char *name, const char *signature, const char *symbol, void *pFunction);

	// Remove a signature from list, but never write to file
	bool Remove(const char *name);

	// Get the index from list of a sigscan stored on the game configs ie. common.txt and cstrike.txt
	int GetIndex(const char *name, ...);

	// Get the sigscan function address
	void *GetFunction(const char *name, ...);

/************************************************************************************
									SigScan Functions
*************************************************************************************/

	// Get Advanced Effects
	ITempEntsSystem *GetTempEnts(const char *addressName /*= "te"*/);

	// Switch a player to other team (CSS)
	// void SwitchTeam(int team_index);
	bool CSSPlayer_SwitchTeam(edict_t *pEntity, int team_index, const char *addressName /*= "CSSPlayer::SwitchTeam"*/);

	// Switch a player to other team (CSS)
	// void SwitchTeam(int team_index);
	bool CSSPlayer_SwitchTeam(CBaseEntity *pBase, int team_index, const char *addressName /*= "CSSPlayer::SwitchTeam"*/);

	// Respawn a player (CSS)
	// void RoundRespawn(void);
	bool CSSPlayer_RoundRespawn(edict_t *pEntity, const char *addressName /*= "CSSPlayer::RoundRespawn"*/);

	// Respawn a player (CSS)
	// void RoundRespawn(void);
	bool CSSPlayer_RoundRespawn(CBaseEntity *pBase, const char *addressName /*= "CSSPlayer::RoundRespawn"*/);

/************************************************************************************
									Static Methods
*************************************************************************************/

#ifdef WIN32
	static bool GetDllMemInfo(void *pAddr, unsigned char **base_addr, size_t *base_len);
	static void *FindSignature(unsigned char *pBaseAddress, size_t baseLength, unsigned char *pSignature);
#endif

	// Holds all signatures
	// Use only to loop
	CUtlVector<SigScan_t> vec_sigscan;

	// Current game player
	const char *GamePlayer;
	
};



#endif
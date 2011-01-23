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
#include "serverplugin/serverplugin_engine.h"
#include "libs/lib_string.h"
#include "libs/lib_entity.h"
#include "libs/lib_sigscan.h"

//=================================================================================
// Utilities
//=================================================================================
static unsigned char HexToBin(char hex_char)
{
	char upper_char = toupper(hex_char);
	return ((upper_char >= '0' && upper_char <= '9') ? upper_char - 48:upper_char - 55);
}

static bool ValidHexChar(char hex_char)
{
	char upper_char = toupper(hex_char);
	return ((upper_char >= '0' && upper_char <= '9') || (upper_char >= 'A' && upper_char <= 'F'));
}

LIB_SIGSCAN_CLASS::LIB_SIGSCAN_CLASS()
{
#ifndef WIN32
	LIB_LINUXUTILS_CLASS::GetLinuxBins();
#endif
}

LIB_SIGSCAN_CLASS::~LIB_SIGSCAN_CLASS()
{

}

//=================================================================================
// Functions
//=================================================================================
// Load signature configs from a KeyValues file
bool LIB_SIGSCAN_CLASS::Load(KeyValues *kvSigscan)
{
	if(!kvSigscan) return false;
	if(kvSigscan->IsEmpty())
	{
		//kvSigscan->deleteThis();
		return true;
	}
	KeyValues *kvLoop;
	bool success = false;
#ifdef WIN32
	unsigned char *base = 0;
	size_t len = 0;
	success = GetDllMemInfo(VAR_IFACE_GAMESERVERDLL, &base, &len);
	if(!success) return false;
#else
	LIB_LINUXUTILS_CLASS *linux_sym_ptr;
	linux_sym_ptr = new LIB_LINUXUTILS_CLASS;
	success = linux_sym_ptr->GetLib(linux_game_bin);
	if (!success)
	{
		DevMsg("Failed to open [%s]\n", linux_game_bin);
		return false;
	}
#endif
	for(kvLoop = kvSigscan->GetFirstSubKey(); kvLoop; kvLoop = kvLoop->GetNextKey())
	{
		if(kvLoop->GetInt("enable", 1) <= 0) continue; // Not enabled
		const char *name = kvLoop->GetName();
		if(!name) continue;
		const char *signature = kvLoop->GetString("signature", NULL);
		const char *symbol = kvLoop->GetString("symbol", NULL);
		void *pFunction = NULL;
#ifdef WIN32
		if(!signature)
		{
			DevMsg("[WARNING] SigScan: %s got no signature, skip this\n", name);
			continue;
		}
		pFunction = FindSignature(base, len, (unsigned char *)signature);
#else
		if(!symbol)
		{
			DevMsg("[WARNING] SigScan: %s got no symbol, skip this\n", name);
			continue;
		}
		pFunction = linux_sym_ptr->FindAddress((char *)symbol);
#endif
		if(!pFunction) 
		{
			Warning("[WARNING] SigScan: Unable to find %s address.\n", name);
			continue;
		}
		AddOrReplace(name, signature, symbol, pFunction);
		DevMsg("SigScan: %s got address @ %p\n", name, pFunction);
		AddOrReplace(name, signature, symbol, pFunction);
	}
#ifdef WIN32
	//delete sig_util_ptr;
#else
	delete linux_sym_ptr;
#endif
	return true;
}

// Add signature to list, but never write to file
bool LIB_SIGSCAN_CLASS::Add(const char *name, const char *signature, const char *symbol, void *pFunction)
{
	if(GetIndex(name) != -1)
		return false;
	SigScan_t sigscan;
	sigscan.Name = name;
	sigscan.Signature = signature;
	sigscan.Symbol = symbol;
	sigscan.pFunction = pFunction;
	vec_sigscan.AddToTail(sigscan);
	return true;
}

// Add or Replace a signature to list, but never write to file
bool LIB_SIGSCAN_CLASS::AddOrReplace(const char *name, const char *signature, const char *symbol, void *pFunction)
{
	if(!Add(name, signature, symbol, pFunction))
		return Replace(name, signature, symbol, pFunction);
	return true;
}

// Replace a signature from list, but never write to file
bool LIB_SIGSCAN_CLASS::Replace(const char *name, const char *signature, const char *symbol, void *pFunction)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
	vec_sigscan[index].Signature = signature;
	vec_sigscan[index].Symbol = symbol;
	vec_sigscan[index].pFunction = pFunction;
	return true;
}

// Remove a signature from list, but never write to file
bool LIB_SIGSCAN_CLASS::Remove(const char *name)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
	vec_sigscan.Remove(index);
	return true;
}

// Get the index from list of a sigscan stored on the game configs ie. common.txt and cstrike.txt
int LIB_SIGSCAN_CLASS::GetIndex(const char *name, ...)
{
	MULTIARGS(name)
	FOR_EACH_VEC(vec_sigscan, i)
		if(LIB_STRING_CLASS::FStrEq(vec_sigscan[i].Name, string))
			return i;
	return -1;
}

// Get the sigscan function address
void *LIB_SIGSCAN_CLASS::GetFunction(const char *name, ...)
{
	MULTIARGS(name)
	FOR_EACH_VEC(vec_sigscan, i)
		if(LIB_STRING_CLASS::FStrEq(vec_sigscan[i].Name, string))
			return vec_sigscan[i].pFunction;
	return NULL;
}

//=================================================================================
// Sigscan Functions
//=================================================================================

// Get Advanced Effects
ITempEntsSystem *LIB_SIGSCAN_CLASS::GetTempEnts(const char *addressName /*= "te"*/) 
{
	if(!addressName) addressName = "te";
	void *pAddr = GetFunction(addressName);
	if(!pAddr) return NULL;
	ITempEntsSystem *pTempEnts = NULL; 
#ifdef WIN32 
	memcpy(&pTempEnts, pAddr, sizeof(char *)); 
	int *ptr = *((int **)(pTempEnts)); 
	pTempEnts = (ITempEntsSystem *)ptr; 
#else 
	pTempEnts = *(ITempEntsSystem **)pAddr; 
#endif 
	return pTempEnts;
   /*
#ifdef WIN32
	te = **(ITempEntsSystem***)(VFN(effects, 3) + 107);
#else
	void *pHandle, *pAddr;

	if((pHandle = dlopen(UTIL_VarArgs("%s/bin/server_i486.so", m_szGameDir), RTLD_NOW)))
	{
		if((pAddr = dlsym(pHandle, "te"))) te = *(ITempEntsSystem **)pAddr;
		dlclose(pHandle);
	}
#endif
	return te;*/
}

// Switch a player to other team (CSS)
// void SwitchTeam(int team_index);
bool LIB_SIGSCAN_CLASS::CSSPlayer_SwitchTeam(edict_t *pEntity, int team_index, const char *addressName /*= "CSSPlayer::SwitchTeam"*/)
{
	return CSSPlayer_SwitchTeam(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), team_index, addressName);
}

// Switch a player to other team (CSS)
// void SwitchTeam(int team_index);
bool LIB_SIGSCAN_CLASS::CSSPlayer_SwitchTeam(CBaseEntity *pBase, int team_index, const char *addressName /*= "CSSPlayer::SwitchTeam"*/)
{
	SIGSCAN_ASSERT_FUNCTION("CSSPlayer::SwitchTeam", false)
	SIGSCAN_1(pBase, pAddr, , void, int, team_index);
	return true;
}

// Respawn a player (CSS)
// void RoundRespawn(void);
bool LIB_SIGSCAN_CLASS::CSSPlayer_RoundRespawn(edict_t *pEntity, const char *addressName /*= "CSSPlayer::RoundRespawn"*/)
{
	return CSSPlayer_RoundRespawn(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), addressName);
}

// Respawn a player (CSS)
// void RoundRespawn(void);
bool LIB_SIGSCAN_CLASS::CSSPlayer_RoundRespawn(CBaseEntity *pBase, const char *addressName /*= "CSSPlayer::RoundRespawn"*/)
{
	SIGSCAN_ASSERT_FUNCTION("CSSPlayer::RoundRespawn", false)
	SIGSCAN_0(pBase, pAddr, , void);
	return true;
}

//=================================================================================
// Static Methods
//=================================================================================

#ifdef WIN32
bool LIB_SIGSCAN_CLASS::GetDllMemInfo(void *pAddr, unsigned char **base_addr, size_t *base_len)
{
	MEMORY_BASIC_INFORMATION mem;

	if(!pAddr)
		return false; // GetDllMemInfo failed: !pAddr

	if(!VirtualQuery(pAddr, &mem, sizeof(mem)))
		return false;

	*base_addr = (unsigned char *)mem.AllocationBase;

	IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER*)mem.AllocationBase;
	IMAGE_NT_HEADERS *pe = (IMAGE_NT_HEADERS*)((unsigned long)dos+(unsigned long)dos->e_lfanew);

	if(pe->Signature != IMAGE_NT_SIGNATURE) {
		base_addr = 0;
		return false; // GetDllMemInfo failed: pe points to a bad location
	}

	*base_len = (size_t)pe->OptionalHeader.SizeOfImage;
	//DevMsg("Found base %p and length %i [%p]\n", base_addr, base_len, base_addr + base_len);

	return true;
}

// Find signature
void *LIB_SIGSCAN_CLASS::FindSignature(unsigned char *pBaseAddress, size_t baseLength, unsigned char *pSignature)
{
	unsigned char *pBasePtr = pBaseAddress;
	unsigned char *pEndPtr = pBaseAddress + baseLength;	

	unsigned char	sigscan[128];
	bool			sigscan_wildcard[128];
	unsigned int	scan_length = 0;
	int				str_index = 0;

	while(1)
	{
		if (pSignature[str_index] == ' ')
		{
			str_index++;
			continue;
		}

		if (pSignature[str_index] == '\0')
		{
			break;
		}

		if (pSignature[str_index] == '?')
		{
			sigscan_wildcard[scan_length++] = true;
			str_index ++;
			continue;
		}

		if (pSignature[str_index + 1] == '\0' || 
			pSignature[str_index + 1] == '?' || 
			pSignature[str_index + 1] == ' ')
		{
			Msg("Failed to decode [%s], single digit hex code\n", pSignature);
			return (void *) NULL;
		}

		// We are expecting a two digit hex code
		char upper_case1 = toupper(pSignature[str_index]);
		if (!ValidHexChar(upper_case1))
		{
			Msg("Failed to decode [%s], bad hex code\n", pSignature);
			return NULL;
		}

		char upper_case2 = toupper(pSignature[str_index + 1]);
		if (!ValidHexChar(upper_case2))
		{
			Msg("Failed to decode [%s], bad hex code\n", pSignature);
			return NULL;
		}

		// Generate our byte code
		unsigned char byte = (HexToBin(upper_case1) << 4) + HexToBin(upper_case2);
		str_index += 2;
		sigscan_wildcard[scan_length] = false;
		sigscan[scan_length] = byte;
		scan_length ++;
		if (scan_length == sizeof(sigscan))
		{
			Msg("Sigscan too long!\n");
			return NULL;
		}
	}

	unsigned int i;
	while (pBasePtr < pEndPtr)
	{
		for (i=0; i < scan_length; i++)
		{
			if (sigscan_wildcard[i] != true && sigscan[i] != pBasePtr[i])
				break;
		}
		//iff i reached the end, we know we have a match!
		if (i == scan_length)
			return (void *)pBasePtr;
		pBasePtr += sizeof(unsigned char);  //search memory in an aligned manner
	}

	return NULL;
}
#endif

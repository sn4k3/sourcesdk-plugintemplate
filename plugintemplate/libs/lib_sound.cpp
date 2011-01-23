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
#include "lib_player.h"
#include "lib_download.h"
#include "lib_sound.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_SOUND_CLASS::LIB_SOUND_CLASS(){}
LIB_SOUND_CLASS::~LIB_SOUND_CLASS(){}

//=================================================================================
// Load sounds from config
//=================================================================================
bool LIB_SOUND_CLASS::Load(KeyValues *kvSound)
{
	if(!kvSound) return false;
	if(kvSound->IsEmpty())
	{
		return true;
	}
	KeyValues *kvLoop;
	for(kvLoop = kvSound->GetFirstValue(); kvLoop; kvLoop = kvLoop->GetNextValue())
	{
		const char *name = kvLoop->GetName();
		if(!name) continue;
		const char *file = kvLoop->GetString();
		if(LIB_STRING_CLASS::StrIsNULL(file)) continue;
		bool download = false;
		unsigned int len = sizeof(file);
		if(file[0] == '#')
		{
			if(len < 2) continue;
			download = true;
			file = LIB_STRING_CLASS::SubStr(file, 1, len);
		}
		DevMsg("Sound: %s added to list, with %s\n", name, file);
		AddOrReplace(name, file, download);
	}
	return true;
}

//=================================================================================
// List Functions
//=================================================================================
// Add a sound to list, but never write to file
bool LIB_SOUND_CLASS::Add(const char *name, const char *file, bool addToDownloads /*= true*/)
{
	if(GetIndex(name) != -1) return false;
	char exists_string[512];
	snprintf(exists_string, sizeof(exists_string), "sound/%s", file);
	if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string))
		return false;
	SoundFile_t soundfile;
	soundfile.Name = name;
	soundfile.File = file;
	soundfile.AddToDownloads = addToDownloads;
	vec_soundfiles.AddToTail(soundfile);

#ifdef USE_LIB_DOWNLOAD
	if(addToDownloads)
		VAR_LIB_DOWNLOAD->Add(exists_string, false);
#endif
	return true;
}

// Add or Replace a sound to list, but never write to file
bool LIB_SOUND_CLASS::AddOrReplace(const char *name, const char *file, bool addToDownloads /*= true*/)
{
	if(!Add(name, file, addToDownloads))
		return Replace(name, file, addToDownloads);
	return true;
}

// Replace a sound from list, but never write to file
bool LIB_SOUND_CLASS::Replace(const char *name, const char *file, bool addToDownloads /*= true*/)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
	char exists_string[512];
	snprintf(exists_string, sizeof(exists_string), "sound/%s", file);
	if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string))
		return false;
	vec_soundfiles[index].File = file;
	vec_soundfiles[index].AddToDownloads = addToDownloads;
#ifdef USE_LIB_DOWNLOAD
	if(addToDownloads)
		VAR_LIB_DOWNLOAD->Add(exists_string, false);
#endif
	return true;
}

bool LIB_SOUND_CLASS::Remove(const char *name)
{
	int index = GetIndex(name);
	if(index == -1) return false;
#ifdef USE_LIB_DOWNLOAD
	if(vec_soundfiles[index].AddToDownloads)
	{
		char exists_string[512];
		snprintf(exists_string, sizeof(exists_string), "sound/%s", vec_soundfiles[index].File);
		VAR_LIB_DOWNLOAD->Remove(exists_string);
	}
#endif
	vec_soundfiles.Remove(index);
	return true;
}

int LIB_SOUND_CLASS::GetIndex(const char *name)
{
	if(!name) return -1;
	FOR_EACH_VEC(vec_soundfiles, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_soundfiles[i].Name, name))
			return i;
	}
	return -1;
}

// Get sound file from the list giving a name
const char *LIB_SOUND_CLASS::GetSound(const char *name, const char *default_value /*= NULL*/)
{
	int index = GetIndex(name);
	if(index == -1) return default_value;
	return vec_soundfiles[index].File;
}

//=================================================================================
// Play Sound Functions STATIC
//=================================================================================

// Emit a sound to player.
// Filters allowed
bool LIB_SOUND_CLASS::EmitSound(const char *players, edict_t *pEntity, const char *file, float vol /*= VOL_NORM*/, float attenuation /*= ATTN_NORM*/, SoundFlags_t flags /*= SND_NOFLAGS*/, Vector *vecAbsOrigin /*= NULL*/, Vector *pDirection /*= NULL*/, CUtlVector< Vector >* pUtlVecOrigins /*= NULL*/, bool bUpdatePositions /*= true*/, float soundtime /*= 0.0f*/, int speakerentity /*= -1*/)
{
#ifndef VAR_IFACE_SOUNDS
	DevMsg("[WARNING] IEngineSound interface is disabled!\n");
	return false;
#else
	if(!VAR_IFACE_SOUNDS) return false;
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	char exists_string[512];
	snprintf(exists_string, sizeof(exists_string), "sound/%s", file);
	if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string))
		return false;

	if(!vecAbsOrigin || vecAbsOrigin->IsZero())
	{
		IPlayerInfo *playerinfo = LIB_PLAYER_CLASS::IsPlayer(pEntity);
		if(playerinfo)
			vecAbsOrigin = new Vector(playerinfo->GetAbsOrigin());
	}
	VAR_IFACE_SOUNDS->PrecacheSound(file, true);

	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	VAR_IFACE_SOUNDS->EmitSound((IRecipientFilter&)mrf, IndexOfEdict(pEntity), CHAN_AUTO, file, vol, attenuation, flags, PITCH_NORM, vecAbsOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity);
	return true;
#endif
}

// Play a sound file to player.
// No emit
// Filters allowed
bool LIB_SOUND_CLASS::Play(const char *players, const char *file, bool checkExits /*= false*/)
{
	if(checkExits)
	{
		char exists_string[512];
		// Check file exists on server
		snprintf(exists_string, sizeof(exists_string), "sound/%s", file);
		if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string)) 
			return false;
	}
	return LIB_PLAYER_CLASS::Cexec(players, "play %s", file);
}

// Play a sound file to player.
// No emit
bool LIB_SOUND_CLASS::Play(edict_t *pEntity, const char *file, bool checkExits /*= false*/)
{
	if(checkExits)
	{
		char exists_string[512];
		// Check file exists on server
		snprintf(exists_string, sizeof(exists_string), "sound/%s", file);
		if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string)) 
			return false;
	}
	return LIB_PLAYER_CLASS::Cexec(pEntity, "play %s", file);
}

LIB_SOUND_CLASS *VAR_LIB_SOUND = NULL;
#ifndef LIB_SOUND_H
#define LIB_SOUND_H
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
#define LIB_SOUND_VERSION "1.0"
#define LIB_SOUND_CLASS CSoundLib

//=================================================================================
// Class
//=================================================================================
class LIB_SOUND_CLASS
{
public:
	struct SoundFile_t
	{
		const char *Name;
		const char *File;
		bool		AddToDownloads;
	};

	LIB_SOUND_CLASS();
	~LIB_SOUND_CLASS();

	// Load sounds from config
	bool Load(KeyValues *kvSound);

	// Add a sound to list, but never write to file
	bool Add(const char *name, const char *file, bool addToDownloads = true);

	// Add or Replace a sound to list, but never write to file
	bool AddOrReplace(const char *name, const char *file, bool addToDownloads = true);

	// Replace a sound from list, but never write to file
	bool Replace(const char *name, const char *file, bool addToDownloads = true);
	
	// Remove a sound from list, but never write to file
	bool Remove(const char *name);


	int GetIndex(const char *name);

	// Get sound file from the list giving a name
	const char *GetSound(const char *name, const char *default_value = NULL);

	// Emit a sound to player.
	// Filters allowed
	static bool EmitSound(const char *players, edict_t *pEntity, const char *file, float vol = VOL_NORM, float attenuation = ATTN_NORM, SoundFlags_t flags = SND_NOFLAGS, Vector *vecAbsOrigin = NULL, Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1);
	
	// Play a sound file to player.
	// No emit
	// Filters allowed
	static bool Play(const char *players, const char *file, bool checkExits = false);

	// Play a sound file to player.
	// No emit
	static bool Play(edict_t *pEntity, const char *file, bool checkExits = false);

	// Sound files list
	// Use to loop only
	CUtlVector<SoundFile_t> vec_soundfiles;
};

//=================================================================================
// Extern global variable
//=================================================================================
extern LIB_SOUND_CLASS *VAR_LIB_SOUND;

#endif
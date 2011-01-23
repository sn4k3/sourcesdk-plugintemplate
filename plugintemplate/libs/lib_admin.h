#ifndef LIB_ADMIN_H
#define LIB_ADMIN_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_ADMIN_VERSION "1.0"
#define LIB_ADMIN_CLASS CAdminLib

class LIB_ADMIN_CLASS
{
public:
	// Admin group data
	struct AdminGroup {
		const char *Name;
		CUtlVector<const char *> vec_flags;
	};

	// Immunity group data
	struct ImmunityGroup {
		const char *Name;
		CUtlVector<const char *> vec_flags;
	};

	// Admin data
	class Admin {
	public:
		// Check if that 'Client' have any Admin Flags By SteamID OR UniqueName.
		bool HaveAdminFlag(const char *flags, bool searchOnGroups = true);
		bool HaveImmunityFlag(const char *flags, bool searchOnGroups = true);

		bool UpdateClient(const char *newSteamId = NULL, const char *name = NULL, const char *contact = NULL, const char *aflags = NULL, const char *iflags = NULL);

		BasicStr szClientName;
		BasicStr szName;
		BasicStr szSteamID;
		BasicStr szContact;
		CUtlVector<const char *>* vec_adminflags;
		CUtlVector<const char *>* vec_immunityflags;
		CUtlVector<AdminGroup>* vec_admingroups;
		CUtlVector<ImmunityGroup>* vec_immunitygroups;
		/*
		char szAFlags[MAX_STR_LEN];
		char szIFlags[MAX_STR_LEN];
		char szRealAFlags[MAX_STR_LEN];
		char szRealIFlags[MAX_STR_LEN];
		char szContact[MAX_STR_LEN];
		char szAGroup[MAX_STR_LEN];
		char szIGroup[MAX_STR_LEN];*/
	};


	LIB_ADMIN_CLASS();
	~LIB_ADMIN_CLASS();

	// Load admins from a created file. (Require a valid format).
	bool Load(const char *file);

	// Clean all data.
	void Reset();

	// Allow use admins without load from file (good for do simple admins like only steamid and without save).
	// NOTE: 'fileToSaveAdmins' is require but only save admins for file if you want!
	bool New(const char *fileToSaveAdmins, const char *fileKeyName = NULL);

	// Save current data to the default file
	void Save();

	// Save current data for a file.
	void Save(const char *saveToFile, const char *keyvalueName = NULL);

	// Get current file version
	// Usefull when Adminlib is updated to fix or update cliets (Based on 'SPT_ADMINLIB_VERSION').
	// NOTE: On save for file will set the newest version.
	int GetFileVersion();

	// Check if that 'Client' is an admin (SteamID OR UniqueName).
	bool IsAdmin(const char *idOrName);

	// Check if that 'Client' is an admin By SteamID.
	bool IsAdminBySteamID(const char *steamid);

	// Check if that 'Client' is an admin by SteamID.
	bool IsAdminByUniqueName(const char *UniqueName);

	// Check if that 'Name' is an Admin Group.
	bool IsAGroup(const char *name);

	// Check if that 'Name' is an Immunity Group.
	bool IsIGroup(const char *name);

	// Check if that 'Client' have any Admin Flags By SteamID OR UniqueName.
	bool HaveAdminFlag(const char *string, const char *flags);

	// Check if that 'Client' have any Admin Flags by SteamID.
	bool HaveAdminFlagBySteamID(const char *steamid, const char *flags);

	// Check if that 'Client' have any Admin Flags By UniqueName.
	bool HaveAdminFlagByUniqueName(const char *UniqueName, const char *flags);

	// Check if that 'Client' have any Immunity Flags By SteamID OR UniqueName.
	bool HaveImmunityFlag(const char *idOrName, const char *flags);

	// Check if that 'Client' have any Immunity Flags By SteamID.
	bool HaveImmunityFlagBySteamID(const char *steamid, const char *flags);

	// Check if that 'Client' have any Immunity Flags By UniqueName.
	bool HaveImmunityFlagByUniqueName(const char *UniqueName, const char *flags);

	// Add a new Client
	// NOTE: Will return new Client name if not NULL
	const char *AddClient(const char *steamid, const char *UniqueName = NULL, const char *name = NULL, const char *contact = NULL, const char *aflags = NULL, const char *iflags = NULL, const char *agroup = NULL, const char *igroup = NULL, bool saveToFile = false);

	// Remove that 'Client' By SteamID OR UniqueName.
	bool RemoveClient(const char *string, bool saveToFile = false);

	// Remove that 'Client' By SteamID.
	bool RemoveClientBySteamID(const char *steamid, bool saveToFile = false);

	// Remove that 'Client' By UniqueName.
	bool RemoveClientByUniqueName(const char *UniqueName, bool saveToFile = false);

	// Update an client By SteamID.
	// Use 'NULL' in 2 > params to advoid update that.
	bool UpdateClientBySteamID(const char *steamid, const char *UniqueName = NULL, const char *newSteamId = NULL, const char *name = NULL, const char *contact = NULL, const char *aflags = NULL, const char *iflags = NULL, const char *agroup = NULL, const char *igroup = NULL, bool saveToFile = false);

	// Update an client By UniqueName.
	// Use 'NULL' in 2 > params to advoid update that.
	bool UpdateClientByUniqueName(const char *UniqueName, const char *NewUniqueName = NULL, const char *steamid = NULL, const char *name = NULL, const char *contact = NULL, const char *aflags = NULL, const char *iflags = NULL, const char *agroup = NULL, const char *igroup = NULL, bool saveToFile = false);

	// Make an sample admin file.
	// This create an admin file sample good for see the KeyValues Format.
	// NOTE: For Flags or Groups will SET the new value not Add !
	void MakeEmptyAdminFile(const char *saveToFile, const char *KeyName = NULL, bool makePlayers = true, bool makePlayersName = true, bool makePlayersSteamID = true, bool makePlayersContact = true, bool makePlayersAFlags = true, bool makePlayersIFlags = true, bool makePlayersAGroup = true, bool makePlayersIGroup = true, bool makeGroups = true, bool makeAGroups = true, bool makeIGroups = true);

	// Assert KeyValues Names.
	const char *AssertValue(const char *value);

	// Convert 'CUtlVector' data to an KeyValue.
	KeyValues *CUtlToKv(const char *keyvalueName = NULL);

	// Print all clients.
	void DebugClients();

	// Print all groups.
	void DebugGroups();

private:
	// 'Admins' data.
	CUtlVector<Admin> vec_admins;

	// 'Admin Groups' data.
	CUtlVector<AdminGroup> vec_admingroups;

	// 'Immunity Groups' data.
	CUtlVector<ImmunityGroup> vec_immunitygroups;

	// Set an client value into 'CUtlVector'.
	void SetClientValue(const char *type, const char *value, int i);

	// Clean client double flags and update real flags with groups
	void ParseClient(int x);

	// Current file where data will be saved
	const char *file;

	// Current Admin File Version (Based on 'LIB_ADMIN_VERSION')
	const char *fileVersion;

	// Current KeyName for your file
	// eg.
	// "admins" // KeyName
	// {
	//		"players"
	//		{
	//		}
	// }
	const char *fileKeyname;
};

#define LIB_EASYADMIN_VERSION "1.0"
#define LIB_EASYADMIN_CLASS CEasyAdminLib

class LIB_EASYADMIN_CLASS
{
public:
	enum LoadType
	{
		TextFile = 0,
		Keyvalues,
		IniFile
	};

	// Constructor
	LIB_EASYADMIN_CLASS(const char *adminFile = NULL);

	// Destructor
	~LIB_EASYADMIN_CLASS();

	// Clean up all admins
	void Reset();

	// Add an admin
	bool Add(const char *steamid);

	// Add an lan players as admin
	// STEAM_ID_LAN
	void AddLan();

	// Add admins, from server players
	// Filters allowed
	// Return how many players got added
	int AddFromServer(const char *players);

	// Remove an admin
	bool Remove(const char *steamid);

	// Check if a player is admin
	bool IsAdmin(const char *steamid);

	// Get steamid index on the list
	int GetIndex(const char *steamid);

	// Load admins from a text file
	// One Steamid per line
	bool LoadFromFile(const char *path);

	// Load admins from a keyvalue file
	// One Steamid per line
	bool LoadFromKeyvalue(const char *path);

	// Load admins from a ini file
	// One Steamid per line
	bool LoadFromIni(const char *path);

	// Save admins to a text file
	// When path is NULL, path from last load or save will be used
	bool SaveToFile(const char *path = NULL);

	// Save admins to a keyvalue file
	// When path is NULL, path from last load or save will be used
	bool SaveToKeyvalue(const char *path = NULL, const char *kvNamespace = "Admins");

	// Save admins to a ini file
	// When path is NULL, path from last load or save will be used
	bool SaveToIni(const char *path = NULL);

	// Last path where file got saved or loaded
	const char *GetFile();

	// Print all admins steamids to console
	void PrintAdmins();

	// Store all admins steam ids
	// Use only to loop admins
	CUtlVector<const char *> Admins;
private:
	// Last path where file got saved or loaded
	char *adminFile;
};

extern LIB_ADMIN_CLASS *VAR_LIB_ADMIN;
extern LIB_EASYADMIN_CLASS *VAR_LIB_EASYADMIN;

#endif
#ifndef LIB_DOWNLOAD_H
#define LIB_DOWNLOAD_H
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
#define LIB_DOWNLOAD_VERSION "1.0"
#define LIB_DOWNLOAD_CLASS CDownloadLib

//=================================================================================
// Class
//=================================================================================
class LIB_DOWNLOAD_CLASS
{
public:
	enum DownloadType { DOWNLOAD_FILE, DOWNLOAD_FROMFILE, DOWNLOAD_FOLDER };

public:
	// Constructor
	LIB_DOWNLOAD_CLASS();

	// Destructor
	~LIB_DOWNLOAD_CLASS();

	// Add a file to downloads list
	// This files got registed as download to clients when 'DispatchDownloads' was called.
	bool Add(const char *file, bool checkExist = true);

	// Add a file to downloads list
	// This files got registed as download to clients when 'DispatchDownloads' was called.
	bool Add(const char *path, DownloadType type, char *filesFilter /*= "*.*"*/, bool subFolders /*= false*/);

	// Remove a file to downloads list
	bool Remove(const char *file);

	// Clear downloads list
	void Clear();

	// Add a file to be downloaded
	static bool AddDownload(const char *file);

	// Add a file to be downloaded
	static bool AddDownload(const char *path, DownloadType type, char *filesFilter = "*.*", bool subFolders = false);

	// Find and Assign downloadables table, without this client download is not possible
	// Call once (Automatic).
	static bool RegisterDownloadables();

	// Register all files from list as client download.
	// Call once (Automatic).
	int DispatchDownloads() const;

	// Gets if download engine is ready to use
	static bool CanDownload();

	// Prints all strings on downloadables table
	static void PrintDownloadablesTable(); 

	// Store all files to be downloaded
	// Use to loop only
	CUtlVector<const char *> files;

public:
	// All downloads got Dispatch at Level Init
	// If true and if your plugin loads in a middle of a map all downloads in list will be Dispatch and avalible to download for new clients.
	bool DispatchDownloadsOnLoad;
	
};

//=================================================================================
// Extern global variable
//=================================================================================
extern LIB_DOWNLOAD_CLASS *VAR_LIB_DOWNLOAD;


#endif
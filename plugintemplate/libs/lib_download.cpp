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
#include "lib_download.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_DOWNLOAD_CLASS::LIB_DOWNLOAD_CLASS()
{
	DispatchDownloadsOnLoad = true;
}
LIB_DOWNLOAD_CLASS::~LIB_DOWNLOAD_CLASS()
{
	files.RemoveAll();
	files.~CUtlVector();
}

//=================================================================================
// List Functions
//=================================================================================

// Add a file to downloads list
// This files got registed as download to clients when 'DispatchDownloads' was called.
bool LIB_DOWNLOAD_CLASS::Add(const char *file, bool checkExist /* = true */)
{
	if(checkExist)
	{
		if(!VAR_IFACE_FILESYSTEM->FileExists(file))
			return false;
	}
	files.AddToTail(file);
	return true;
}

// Add a file to downloads list
// This files got registed as download to clients when 'DispatchDownloads' was called.
bool LIB_DOWNLOAD_CLASS::Add(const char *path, DownloadType type, char *filesFilter /*= "*.*"*/, bool subFolders /*= false*/)
{
	if(!path) return false;
	if(type == DOWNLOAD_FILE)
	{
		if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;
		files.AddToTail(path);
		return true;
	}
	if(type == DOWNLOAD_FROMFILE)
	{
		if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;

		FileHandle_t pfile = VAR_IFACE_FILESYSTEM->Open(path, "r");
		if(!pfile) return false;

		char line[MAX_STR_LENGTH];
		while (!VAR_IFACE_FILESYSTEM->EndOfFile(pfile))
		{
			if(!VAR_IFACE_FILESYSTEM->ReadLine(line, sizeof(line), pfile))
				continue;

			LIB_STRING_CLASS::GetParsedLine(line);
			const char *newline = LIB_STRING_CLASS::StrTrim(line);
			if(newline)
				files.AddToTail(newline);
		}
		VAR_IFACE_FILESYSTEM->Close(pfile);
		return true;
	}
	if(type == DOWNLOAD_FOLDER)
	{
		if(!VAR_IFACE_FILESYSTEM->IsDirectory(path)) return false;
		if(!filesFilter) filesFilter = "*.*";
		else if(LIB_STRING_CLASS::FStrEq(filesFilter, "*")) filesFilter = "*.*";
		FileFindHandle_t pfile;
		const char *fileName;
		unsigned int len = strlen(path)-1;
		if (!(path[len] == '\\' || path[len] == '/'))
		{
			path = LIB_STRING_CLASS::StrFormat("%s/", path);
		}
		
		char *correctPath = LIB_STRING_CLASS::StrNew(path);
		strcat(correctPath, filesFilter);
				
		fileName = VAR_IFACE_FILESYSTEM->FindFirstEx(correctPath, "MOD", &pfile);
		while(fileName)
		{
			if(LIB_STRING_CLASS::FStrEq(fileName, ".") || LIB_STRING_CLASS::FStrEq(fileName, ".."))
			{
				fileName = VAR_IFACE_FILESYSTEM->FindNext(pfile);
				continue;
			}
			char joinfile[MAX_STR_LEN];
			LIB_STRING_CLASS::UTIL_Format(joinfile, MAX_STR_LEN, "%s%s", path, fileName);
			files.AddToTail(joinfile);
			fileName = VAR_IFACE_FILESYSTEM->FindNext(pfile);
		}
		return true;
	}
	return false;
}

// Remove a file to downloads list
bool LIB_DOWNLOAD_CLASS::Remove(const char *file)
{
	FOR_EACH_VEC(files, i)
	{
		if(LIB_STRING_CLASS::FStrEq(files[i], file))
		{
			files.Remove(i);
			return true;
		}
	}
	return false;
}

// Remove all downloads from list
void LIB_DOWNLOAD_CLASS::Clear()
{
	files.RemoveAll();
}

//=================================================================================
// Downloads Functions
//=================================================================================

// Add a file to be downloaded
bool LIB_DOWNLOAD_CLASS::AddDownload(const char *file)
{
	if(!LIB_DOWNLOAD_CLASS::RegisterDownloadables())
		return false;
	bool save = VAR_IFACE_ENGINE->LockNetworkStringTables(false);
	downloadablestable->DOWNLOADABLES_ADDSTRING(file, strlen(file)+1);
	VAR_IFACE_ENGINE->LockNetworkStringTables(save);
	return true;
}

// Add a file to be downloaded
bool LIB_DOWNLOAD_CLASS::AddDownload(const char *path, DownloadType type, char *filesFilter /*= "*.*"*/, bool subFolders /*= false*/)
{
	if(!path) return false;
	if(!LIB_DOWNLOAD_CLASS::RegisterDownloadables())
		return false;
	if(type == DOWNLOAD_FILE)
	{
		if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;
		return AddDownload(path);
	}
	if(type == DOWNLOAD_FROMFILE)
	{
		if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;

		FileHandle_t pfile = VAR_IFACE_FILESYSTEM->Open(path, "r");
		if(!pfile) return false;

		char line[MAX_STR_LENGTH];
		bool save = VAR_IFACE_ENGINE->LockNetworkStringTables(false);
		while (!VAR_IFACE_FILESYSTEM->EndOfFile(pfile))
		{
			if(!VAR_IFACE_FILESYSTEM->ReadLine(line, sizeof(line), pfile))
				continue;

			LIB_STRING_CLASS::GetParsedLine(line);
			const char *newline = LIB_STRING_CLASS::StrTrim(line);
			if(newline)
				downloadablestable->DOWNLOADABLES_ADDSTRING(newline, strlen(newline)+1);
		}
		VAR_IFACE_ENGINE->LockNetworkStringTables(save);
		VAR_IFACE_FILESYSTEM->Close(pfile);
		return true;
	}
	if(type == DOWNLOAD_FOLDER)
	{
		if(!VAR_IFACE_FILESYSTEM->IsDirectory(path)) return false;
		if(!filesFilter) filesFilter = "*.*";
		else if(LIB_STRING_CLASS::FStrEq(filesFilter, "*")) filesFilter = "*.*";
		FileFindHandle_t pfile;
		const char *fileName;
		unsigned int len = strlen(path)-1;
		if (!(path[len] == '\\' || path[len] == '/'))
		{
			path = LIB_STRING_CLASS::StrFormat("%s/", path);
		}
		
		char *correctPath = LIB_STRING_CLASS::StrNew(path);
		strcat(correctPath, filesFilter);
				
		fileName = VAR_IFACE_FILESYSTEM->FindFirstEx(correctPath, "MOD", &pfile);
		while(fileName)
		{
			if(LIB_STRING_CLASS::FStrEq(fileName, ".") || LIB_STRING_CLASS::FStrEq(fileName, ".."))
			{
				fileName = VAR_IFACE_FILESYSTEM->FindNext(pfile);
				continue;
			}
			char joinfile[MAX_STR_LEN];
			LIB_STRING_CLASS::UTIL_Format(joinfile, MAX_STR_LEN, "%s%s", path, fileName);
			AddDownload(joinfile);
			fileName = VAR_IFACE_FILESYSTEM->FindNext(pfile);
		}
		return true;
	}
	return false;
}

// Find and Assign downloadables table, without this client download is not possible
// Call once (Automatic).
bool LIB_DOWNLOAD_CLASS::RegisterDownloadables()
{
#ifndef USE_IFACE_NETWORKSTRINGTABLE
	Msg("[WARNING] NetworkStringTableContainer interface is disabled!\n");
	return false;
#else
	if(!VAR_IFACE_NETWORKSTRINGTABLE)
		return false;
	if(!downloadablestable)
	{
		downloadablestable = VAR_IFACE_NETWORKSTRINGTABLE->FindTable("downloadables");
		if(!downloadablestable)
			return false;
	}
	return true;
#endif
}

// Register all files from list as client download.
// Call once (Automatic).
int LIB_DOWNLOAD_CLASS::DispatchDownloads() const
{
	if(!RegisterDownloadables())
		return -1;
	bool save = VAR_IFACE_ENGINE->LockNetworkStringTables(false);
	FOR_EACH_VEC(files, i)
		downloadablestable->DOWNLOADABLES_ADDSTRING(files[i], strlen(files[i])+1);
	VAR_IFACE_ENGINE->LockNetworkStringTables(save);
	return files.Count();
}

// Gets if download engine is ready to use
bool LIB_DOWNLOAD_CLASS::CanDownload()
{
	return downloadablestable != NULL;
}

//=================================================================================
// Print
//=================================================================================

// Prints all strings on downloadables table
void LIB_DOWNLOAD_CLASS::PrintDownloadablesTable()
{
	if(!RegisterDownloadables())
		return;
	int numStrings = downloadablestable->GetNumStrings();
	Msg("Downloadablestable Table:\nStrings: %i\n------------------------------\n", numStrings);
	for(int i = 0; i < numStrings; i++)
	{
		Msg("%i: %s\n", (i+1), downloadablestable->GetString(i));
	}
	Msg("------------------------------\n");
}

LIB_DOWNLOAD_CLASS *VAR_LIB_DOWNLOAD = NULL;
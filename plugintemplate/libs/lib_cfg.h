#ifndef LIB_CONFIG_H
#define LIB_CONFIG_H
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
#define LIB_CFG_VERSION "1.0"
#define LIB_CFG_CLASS CCfgLib

//=================================================================================
// Class
//=================================================================================
class LIB_CFG_CLASS
{
public:
	// Line type
	enum LINE_TYPE
	{
		TEXT = 0,
		CVAR,
		COMMAND
	};
	// Config file struct
	struct struct_file
	{
		LINE_TYPE type;
		int index;
	};
	// CVar and Command struct
	struct struct_cvar
	{
		BasicStr name;
		BasicStr value;
		BasicStr description;
	};


	// Constructor
	LIB_CFG_CLASS(const char *cfg);
	// Deconstructor
	~LIB_CFG_CLASS();

	// Make file empty
	void Empty();

	// Loads a config from file
	// If file is NULL, string passed on constructor will be used
	// Return true on success, otherwise false (file is null or invalid)
	bool Load(const char *file = NULL);

	// Append text to file
	// Return text line index
	int Text(const char *text);

	// Append an cvar to the file, if already exists new values will be used
	// Return false if cvar exists and got updated, otherwise cvar is new entry
	bool CVar(const char *name, const char *value, const char *description = NULL);

	// Append an cvar to the file, if already exists new values will be used
	// CVar name, defaultvalue and helptext will be used to populate the line
	// If overwritevalue is NULL defaultvalue from cvar will be used
	// Return false if cvar exists and got updated, otherwise cvar is new entry
	bool CVar(ConVar *cvar, const char *overwritevalue);

	// Append an cvar to the file, if already exists new values will be used
	// CVar name, defaultvalue and helptext will be used to populate the line
	// Return false if cvar exists and got updated, otherwise cvar is new entry
	bool CVar(ConVar *cvar);

	// Append an command 
	// Set replacevalues to true, if you want to update/replace values on commands
	// Return false if command exists and got updated, otherwise command is new entry
	bool Command(const char *name, const char *arguments = NULL, const char *description = NULL, bool replacevalues = false);

	// Append an command 
	// ConCommand name and helptext will be used to populate the line
	// Set replacevalues to true, if you want to update/replace values on commands
	// Return false if command exists and got updated, otherwise command is new entry
	bool Command(ConCommand *command, const char *arguments = NULL, bool replacevalues = false);

	// Remove a line from config
	// Returns true if something got removed
	bool Remove(LINE_TYPE type, const char *name);

	// Execute all cvars and commands
	// If byorder is true, execute cvars and commands by creation order, otherwise execute all cvars first and after the commands
	// Return the amount of exucuted commands
	int Execute(bool executecvars = true, bool executecommands = true, bool byorder = true);

	// Write to file
	// If file is NULL, string passed on constructor will be used
	// If overwrite is true, overwrite any file with the current lines
	// If writeempty is true, create a empty config file when there aren't lines to write
	bool Write(const char *file = NULL, bool writetext = true, bool writecvars = true, bool writecommands = true, bool overwrite = false, bool writeempty = false);

	// Print file structure to console
	void Print(bool printtext = true, bool printcvars = true, bool printcommands = true);

//=================================================================================
// Static Methods
//=================================================================================

	// Call exec server command
	// From dir: cfg/
	// Return false if file doesn't exists
	static bool Exec(const char *file, ...);

	// exec a .cfg file from any game path
	// Require full path
	// Return false if file doesn't exists
	static bool ExecEx(const char *file, ...);

	// exec a .cfg file from any game path
	// Require full path
	// Return a LIB_CFG_CLASS object with file contents, if fail returns NULL
	// NOTE: Free object when you no longer use it
	static LIB_CFG_CLASS *ExecEx2(const char *file, ...);

//=================================================================================
// Properties
//=================================================================================

	// File lines
	// Cache
	CUtlVector<struct_file> vec_file;

	// Text lines
	CUtlVector<BasicStr> vec_text;

	// Cvar lines
	CUtlVector<struct_cvar> vec_cvar;

	// Command lines
	CUtlVector<struct_cvar> vec_command;

	// Config files extension
	inline static const char *Extension() { return ".cfg"; }

private:
	// Path from file got loaded or saved
	const char *cfgFile;
};

#endif
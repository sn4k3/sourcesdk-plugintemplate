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
#include "lib_cfg.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_CFG_CLASS::LIB_CFG_CLASS(const char *cfg)
{
	cfgFile = cfg;
}
LIB_CFG_CLASS::~LIB_CFG_CLASS()
{
	cfgFile = NULL;
	vec_file.RemoveAll();
	vec_file.~CUtlVector();
	vec_text.RemoveAll();
	vec_text.~CUtlVector();
	vec_cvar.RemoveAll();
	vec_cvar.~CUtlVector();
	vec_command.RemoveAll();
	vec_command.~CUtlVector();
}

// Make file empty
void LIB_CFG_CLASS::Empty()
{
	vec_text.RemoveAll();
	vec_file.RemoveAll();
	vec_cvar.RemoveAll();
	vec_command.RemoveAll();
}

// Loads a config from file
// If file is NULL, string passed on constructor will be used
// Return true on success, otherwise false (file is null or invalid)
bool LIB_CFG_CLASS::Load(const char *file /*= NULL*/)
{
	if(!file)
		file = cfgFile;
	if(!file)
		return false; // No file to save
	if(!VAR_IFACE_FILESYSTEM->FileExists(file, "MOD"))
		return false;
	FileHandle_t pfile = VAR_IFACE_FILESYSTEM->Open(file, "r", "MOD");
	if(!pfile) return false;

	std::pair<unsigned int, const char *> lastcomment = std::make_pair<unsigned int, const char *>(0,NULL);
	unsigned int linecount = 0;
	int lastcommentindex = 0;
	int commentindex = -1;

	char line[MAX_STR_LENGTH];
	while (!VAR_IFACE_FILESYSTEM->EndOfFile(pfile))
	{
		if(!VAR_IFACE_FILESYSTEM->ReadLine(line, sizeof(line), pfile))
			continue;

		linecount++;


		if(!LIB_STRING_CLASS::GetParsedLine(line, false)) continue;
		if(LIB_STRING_CLASS::IsComment(line) >= 0)
		{
			lastcommentindex = Text(line);
			lastcomment.second = LIB_STRING_CLASS::StripCommentSymbols(LIB_STRING_CLASS::StrNew(line));
			continue; // Keep last comment, maybe is a cvar or command description, add latter
		}
		const char *newline = LIB_STRING_CLASS::StrTrim(line);
		if(!newline)
			continue;
		CUtlVector<const char *> *vec_line = LIB_STRING_CLASS::StrSplit(newline, ' ', 1);
		int i = vec_line->Count();
		if(!i)
			continue;
		const char *name = vec_line->Element(0);
		const char *value = i == 2 ? vec_line->Element(1) : NULL;
		const char *description = lastcomment.first == linecount-1 ? lastcomment.second : NULL;
		if(VAR_IFACE_ICVAR->FindVar(name)) // Is CVAR?
		{
			if(description) // Last comment belongs to cvar
				vec_file.Remove(lastcommentindex);
			CVar(name, value, description);
			vec_line->RemoveAll();
			vec_line->~CUtlVector();
			continue;
		}
		if(VAR_IFACE_ICVAR->FindCommand(name)) // Is COMMAND?
		{
			if(description) // Last comment belongs to command
				vec_file.Remove(lastcommentindex);
			Command(name, value, description);
			vec_line->RemoveAll();
			vec_line->~CUtlVector();
			continue;
		}
		Text(newline);
	}
	VAR_IFACE_FILESYSTEM->Close(pfile);
	return true;
}

// Append text to file
int LIB_CFG_CLASS::Text(const char *text)
{
	struct_file fLine;
	fLine.type = TEXT;
	fLine.index = vec_text.AddToTail(text);
	return vec_file.AddToTail(fLine);
}

// Append an cvar to the file, if already exists new values will be used
// Return false if cvar exists and got updated, otherwise cvar is new entry
bool LIB_CFG_CLASS::CVar(const char *name, const char *value, const char *description /*= NULL*/)
{
	FOR_EACH_VEC(vec_cvar, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_cvar[i].name.str, name))
		{
			vec_cvar[i].value = BasicStr(value);
			vec_cvar[i].description = BasicStr(description);
			return false;
		}
	}
	struct_cvar cvar;
	cvar.name = BasicStr(name);
	cvar.value = BasicStr(value);
	cvar.description = BasicStr(description);
	struct_file fLine;
	fLine.type = CVAR;
	fLine.index = vec_cvar.AddToTail(cvar);
	vec_file.AddToTail(fLine);
	return true;
}

// Append an cvar to the file, if already exists new values will be used
// CVar name, defaultvalue and helptext will be used to populate the line
// If overwritevalue is NULL defaultvalue from cvar will be used
// Return false if cvar exists and got updated, otherwise cvar is new entry
bool LIB_CFG_CLASS::CVar(ConVar *cvar, const char *overwritevalue = NULL)
{
	if(!cvar)
		return false;
	return CVar(cvar->GetName(), (overwritevalue ? overwritevalue : cvar->GetDefault()), cvar->GetHelpText());
}

// Append an cvar to the file, if already exists new values will be used
// CVar name, defaultvalue and helptext will be used to populate the line
// Return false if cvar exists and got updated, otherwise cvar is new entry
bool LIB_CFG_CLASS::CVar(ConVar *cvar)
{
	if(!cvar)
		return false;
	return CVar(cvar->GetName(), cvar->GetDefault(), cvar->GetHelpText());
}

// Append an command 
// Set replacevalues to true, if you want to update/replace values on commands
// Return false if command exists and got updated, otherwise command is new entry
bool LIB_CFG_CLASS::Command(const char *name, const char *arguments /*= NULL*/, const char *description /*= NULL*/, bool replacevalues /*= false*/)
{
	if(replacevalues)
	{
		FOR_EACH_VEC(vec_command, i)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_command[i].name.str, name))
			{
				vec_command[i].value = BasicStr(arguments);
				vec_command[i].description = BasicStr(description);
				return false;
			}
		}
	}
	struct_cvar command;
	command.name = BasicStr(name);
	command.value = BasicStr(arguments);
	command.description = BasicStr(description);
	struct_file fLine;
	fLine.type = COMMAND;
	fLine.index = vec_command.AddToTail(command);
	vec_file.AddToTail(fLine);
	return true;
}

// Append an command 
// ConCommand name and helptext will be used to populate the line
// Set replacevalues to true, if you want to update/replace values on commands
// Return false if command exists and got updated, otherwise command is new entry
bool LIB_CFG_CLASS::Command(ConCommand *command, const char *arguments /*= NULL*/, bool replacevalues /*= false*/)
{
	if(!command)
		return false;
	return Command(command->GetName(), arguments, command->GetHelpText(), replacevalues);
}

// Execute all cvars and commands
// If byorder is true, execute cvars and commands by creation order, otherwise execute all cvars first and after the commands
// Return the amount of exucuted commands
int LIB_CFG_CLASS::Execute(bool executecvars /*= true*/, bool executecommands /*= true*/, bool byorder /*= true*/)
{
	if(!vec_file.Count()) 
		return 0; // Nothing to execute
	int count = 0;
	char line_string[1024];
	if(executecvars && executecommands && byorder)
	{
		FOR_EACH_VEC(vec_file, i)
		{
			switch(vec_file[i].type)
			{
			case TEXT:
				break;
			case CVAR:
				count++;
				snprintf(line_string, sizeof(line_string), "%s %s\n", vec_cvar[vec_file[i].index].name.str, vec_cvar[vec_file[i].index].value.str);
				VAR_IFACE_ENGINE->ServerCommand(line_string);
				break;
			case COMMAND:
				count++;
				if(vec_command[vec_file[i].index].value.IsNULL())
					snprintf(line_string, sizeof(line_string), "%s\n", vec_command[vec_file[i].index].name.str);
				else
					snprintf(line_string, sizeof(line_string), "%s %s\n", vec_command[vec_file[i].index].name.str, vec_command[vec_file[i].index].value.str);
				VAR_IFACE_ENGINE->ServerCommand(line_string);
			}
		}
	}
	else
	{
		if(executecvars)
		{
			FOR_EACH_VEC(vec_cvar, i)
			{
				count++;
				snprintf(line_string, sizeof(line_string), "%s %s\n", vec_cvar[i].name.str, vec_cvar[i].value.str);
				VAR_IFACE_ENGINE->ServerCommand(line_string);
			}
		}
		if(executecommands)
		{
			FOR_EACH_VEC(vec_command, i)
			{
				count++;
				if(vec_command[i].value.IsNULL())
					snprintf(line_string, sizeof(line_string), "%s\n", vec_command[i].name.str);
				else
					snprintf(line_string, sizeof(line_string), "%s %s\n", vec_command[i].name.str, vec_command[i].value.str);
				VAR_IFACE_ENGINE->ServerCommand(line_string);
			}
		}
	}
	if(count)
		VAR_IFACE_ENGINE->ServerExecute();
	return count;
}

// Remove a line from config
// Returns true if something got removed
bool LIB_CFG_CLASS::Remove(LIB_CFG_CLASS::LINE_TYPE type, const char *name)
{
	int index = -1;
	switch(type)
	{
	case TEXT:
		FOR_EACH_VEC(vec_text, i)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_text[i].str, name))
			{
				index = i;
				vec_text.Remove(i);
				break;
			}
		}
		break;
	case CVAR:
		FOR_EACH_VEC(vec_cvar, i)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_cvar[i].name.str, name))
			{
				index = i;
				vec_cvar.Remove(i);
				break;
			}
		}
		break;
	case COMMAND:
		FOR_EACH_VEC(vec_command, i)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_command[i].name.str, name))
			{
				index = i;
				vec_command.Remove(i);
				break;
			}
		}
		break;
	}
	if(index == -1)
		return false;
	FOR_EACH_VEC(vec_file, i)
	{
		if(vec_file[i].type == type && vec_file[i].index == index)
		{
			vec_file.Remove(i);
			break;
		}
	}
	return true;
}

// Write to file
// If file is NULL, string passed on constructor will be used
// If overwrite is true, overwrite any file with the current lines
// If writeempty is true, create a empty config file when there aren't lines to write
bool LIB_CFG_CLASS::Write(const char *file /*= NULL*/, bool writetext /*= true*/, bool writecvars /*= true*/, bool writecommands /*= true*/, bool overwrite /*= false*/, bool writeempty /*= false*/)
{
	if(!vec_file.Count() && !writeempty) 
		return false; // Nothing to save
	if(!file)
		file = cfgFile;
	if(!file)
		return false; // No file to save
	if(!overwrite)
		if(VAR_IFACE_FILESYSTEM->FileExists(file))
			return false;
	FileHandle_t fp = VAR_IFACE_FILESYSTEM->Open(file, "w", "MOD");
	if(!fp)
		return false; // Cant write, file doesn't exists?
	FOR_EACH_VEC(vec_file, i)
	{
		switch(vec_file[i].type)
		{
		case TEXT:
			if(!writetext)
				break;
			VAR_IFACE_FILESYSTEM->FPrintf(fp, "%s\n", vec_text[vec_file[i].index].str);
			break;
		case CVAR:
			if(!writecvars)
				break;
			if(vec_cvar[vec_file[i].index].description.IsNULL())
				VAR_IFACE_FILESYSTEM->FPrintf(fp, "%s %s\n\n", vec_cvar[vec_file[i].index].name.str, vec_cvar[vec_file[i].index].value.str);
			else
				VAR_IFACE_FILESYSTEM->FPrintf(fp, "// %s\n%s %s\n\n", vec_cvar[vec_file[i].index].description.str, vec_cvar[vec_file[i].index].name.str, vec_cvar[vec_file[i].index].value.str);
			break;
		case COMMAND:
			if(!writecommands)
				break;
			if(!vec_command[vec_file[i].index].description.IsNULL())
				VAR_IFACE_FILESYSTEM->FPrintf(fp, "// %s\n", vec_command[vec_file[i].index].description.str);
			if(!vec_command[vec_file[i].index].value.IsNULL())
				VAR_IFACE_FILESYSTEM->FPrintf(fp, "%s %s\n\n", vec_command[vec_file[i].index].name.str, vec_command[vec_file[i].index].value.str);
			else
				VAR_IFACE_FILESYSTEM->FPrintf(fp, "%s\n\n", vec_command[vec_file[i].index].name.str);
			break;
		}
	}
	VAR_IFACE_FILESYSTEM->Close(fp);
	return true;
}

// Print file structure to console
void LIB_CFG_CLASS::Print(bool printtext /*= true*/, bool printcvars /*= true*/, bool printcommands /*= true*/)
{
	FOR_EACH_VEC(vec_file, i)
	{
		switch(vec_file[i].type)
		{
		case TEXT:
			if(!printtext)
				break;
			Msg("%s\n", vec_text[vec_file[i].index].str);
			break;
		case CVAR:
			if(!printcvars)
				break;
			if(vec_cvar[vec_file[i].index].description.IsNULL())
				Msg("%s %s\n\n", vec_cvar[vec_file[i].index].name.str, vec_cvar[vec_file[i].index].value.str);
			else
				Msg("// %s\n%s %s\n\n", vec_cvar[vec_file[i].index].description.str, vec_cvar[vec_file[i].index].name.str, vec_cvar[vec_file[i].index].value.str);
			break;
		case COMMAND:
			if(!printcommands)
				break;
			if(!vec_command[vec_file[i].index].description.IsNULL())
				Msg("// %s\n", vec_command[vec_file[i].index].description.str);
			if(!vec_command[vec_file[i].index].value.IsNULL())
				Msg("%s %s\n\n", vec_command[vec_file[i].index].name.str, vec_command[vec_file[i].index].value.str);
			else
				Msg("%s\n\n", vec_command[vec_file[i].index].name.str);
			break;
		}
	}
}

//=================================================================================
// Static Methods
//=================================================================================

// Call exec server command
// From dir: cfg/
// Return false if file doesn't exists
bool LIB_CFG_CLASS::Exec(const char *file, ...)
{
	MULTIARGS(file);
	char exists_string[512];
	snprintf(exists_string, sizeof(exists_string), "cfg/%s", string);
	if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string, "MOD"))
	{
		strcat(exists_string, ".cfg");
		//snprintf(exists_string, sizeof(exists_string), "cfg/%s.cfg", string);
		if(!VAR_IFACE_FILESYSTEM->FileExists(exists_string, "MOD"))
			return false;
	}
	char buffer[1024];
	LIB_STRING_CLASS::UTIL_Format(buffer, sizeof(buffer), "exec %s\n", string);
	VAR_IFACE_ENGINE->ServerCommand(buffer);
	VAR_IFACE_ENGINE->ServerExecute();
	return true;
}

// exec a .cfg file from any game path
// Require full path
// Return false if file doesn't exists
bool LIB_CFG_CLASS::ExecEx(const char *file, ...)
{
	MULTIARGS(file);
	if(LIB_STRING_CLASS::StrLeftEq(string, "cfg/"))
		return Exec(string);
	if(!VAR_IFACE_FILESYSTEM->FileExists(string, "MOD"))
		return false;
	LIB_CFG_CLASS *config = new LIB_CFG_CLASS(string);
	if(config->Load(string))
		config->Execute();
	config->~LIB_CFG_CLASS();
	return true;
}

// exec a .cfg file from any game path
// Require full path
// Return a LIB_CFG_CLASS object with file contents, if fail returns NULL
// NOTE: Free object when you no longer use it
LIB_CFG_CLASS *LIB_CFG_CLASS::ExecEx2(const char *file, ...)
{
	MULTIARGS(file);
	if(!VAR_IFACE_FILESYSTEM->FileExists(string, "MOD"))
		return NULL;
	LIB_CFG_CLASS *config = new LIB_CFG_CLASS(string);
	if(config->Load(string))
		config->Execute();
	return config;
}
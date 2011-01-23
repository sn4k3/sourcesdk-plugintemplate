//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_ini.h"
#include "tier0/memdbgon.h"


LIB_INI_CLASS::LIB_INI_CLASS()
{
	Reset();
}

LIB_INI_CLASS::LIB_INI_CLASS(const char *file, bool autoload /*= false*/)
{
	Reset();
	pathFile = file;
	if(autoload)
		Load();
}

LIB_INI_CLASS::~LIB_INI_CLASS()
{
	Reset();
	fileHearder.~BasicStr();
}

void LIB_INI_CLASS::Reset(bool unsetFile /*= true*/)
{
	if(unsetFile) pathFile = NULL;
	fileHearder.Clean();
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
		map_itn->second->RemoveAll();
	map_file.clear();
}

bool LIB_INI_CLASS::Load()
{
	return Load(pathFile);
}

bool LIB_INI_CLASS::Load(const char *file)
{
	if(!file) return false;
	if(!VAR_IFACE_FILESYSTEM->FileExists(file)) return false;

	FileHandle_t pFile = VAR_IFACE_FILESYSTEM->Open(file, "rb");
	if(!pFile) return false;

	Reset();
	pathFile = LIB_STRING_CLASS::StrNew(file);

	char line[MAX_STR_LENGTH], section[MAX_STR_LENGTH], entry[MAX_STR_LENGTH], value[MAX_STR_LENGTH];
	char *lastsection = NULL, *szComment = NULL;
	//IniKeyValue iniKeyValue_temp;
	//IniKey iniKey_temp;
	unsigned int i = 0; /*loc = 0, loc2 = 0, loc3 = 0,*/ 
	int comment = 0, includeOther = 0;

	while (!VAR_IFACE_FILESYSTEM->EndOfFile(pFile))
	{
		if(!VAR_IFACE_FILESYSTEM->ReadLine(line, sizeof(line), pFile))
			continue;

		if (!line || line[0] == '\n' || line[0] == '\r' || (lastsection && (line[0] == '#' || line[0] == ';' || (line[0] == '/' && line[0+1] == '/'))))
			continue;

		comment = -1;
		includeOther = -1;
		for(i = 0; i < strlen(line); i++)
		{
			if(line[i] == '\r' || line[i] == '\n')
				line[i] = '\0';
			/*else if(line[i] == '[')
				loc = i+1;
			else if(line[i] == ']')
				loc2 = i-1;
			else if(line[i] == '=')
				loc3 = i;*/
			else if(line[i] == ';' || line[i] == '#' || (line[i] == '/' && line[i-1] == '/'))
				comment = i+1;
			else if(line[i] == '>' && line[i-1] == '-')
				includeOther = i+1;
		}

		if(includeOther != -1)
		{
			char *fileToinclude = LIB_STRING_CLASS::SubStr(line, includeOther, strlen(line));
			fileToinclude = LIB_STRING_CLASS::StrTrim(fileToinclude);
			Join(fileToinclude);
		}

		szComment = NULL;
		if(comment != -1)
		{
			szComment = LIB_STRING_CLASS::SubStr(line, comment, strlen(line));
			szComment = LIB_STRING_CLASS::StrTrim(szComment);
			if(!lastsection && szComment)
			{
				if(fileHearder.IsNULL()) fileHearder = BasicStr("// ");
				else fileHearder.Cat("// ");
				fileHearder.Cat(szComment);
				fileHearder.Cat("\n");
			}
		}
		if (sscanf(line, "[%[^]]", section) == 1)
		{
			//IniKey iniKey_temp;
			//iniKey_temp.szKey = LIB_STRING_CLASS::StrNew(section);
			//iniKey_temp.szComment = szComment ? LIB_STRING_CLASS::StrNew(szComment) : NULL;
			
			lastsection = section;
			if(!Exists(section))
				map_file[BasicStr(section)] = new CUtlVector<IniKeyValue>();
			continue;
		}
		// else
		if ((sscanf (line, "%[^=] = \"%[^\"]\"", entry, value) == 2)
			|| (sscanf (line, "%[^=] = '%[^\']'", entry, value) == 2)
			|| (sscanf (line, "%[^=] = %[^;#]", entry, value) == 2)
			|| (sscanf (line, "%[^=]=\"%[^\"]\"", entry, value) == 2)
			|| (sscanf (line, "%[^=]='%[^\']'", entry, value) == 2)
			|| (sscanf (line, "%[^=]=%[^;#]", entry, value) == 2))
		{
			if(!lastsection) continue;
			if ((strcmp (value, "\"\"") == 0) || (strcmp (value, "''") == 0)) continue;


			const char *newentry = LIB_STRING_CLASS::StrTrim(entry, true, true);

			IniKeyValue iniKeyValue_temp;
			iniKeyValue_temp.szKeyName = BasicStr(newentry);
			iniKeyValue_temp.szKeyValue = BasicStr(value);
			iniKeyValue_temp.szComment = BasicStr(szComment);
			map_file[lastsection]->AddToTail(iniKeyValue_temp);
			continue;
		}
	}

	VAR_IFACE_FILESYSTEM->Close(pFile);

	return true;
}

CUtlVector<const char *>* LIB_INI_CLASS::GetSections()
{
	CUtlVector<const char *>* vec = new CUtlVector<const char *>();
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
		vec->AddToTail(map_itn->first.ToString());
	return vec;
}

CUtlVector<LIB_INI_CLASS::IniKeyValue>* LIB_INI_CLASS::GetSectionKeyValues(const char *section)
{
	CUtlVector<IniKeyValue>* vec = new CUtlVector<IniKeyValue>();
	map_itn = map_file.find(section);
	if(map_itn == map_file.end())
		return vec;
	for(int i = 0; map_itn->second->Count(); i++)
		vec->AddToTail(map_itn->second->Element(i));
	return vec;
}

bool LIB_INI_CLASS::Exists(const char *Key)
{
	return map_file.find(Key) != map_file.end();
}

bool LIB_INI_CLASS::Exists(const char *Key, const char *KeyName)
{
	return GetIndex(Key, KeyName) != -1;
}

bool LIB_INI_CLASS::Remove(const char *Key, bool movedata /*= false*/, const char *forKey /*= NULL*/, bool createIt /*= true*/)
{
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return false;

	if(forKey) // Try to move data
	{
		if(LIB_STRING_CLASS::FStrEq(Key, forKey))
			return false;
		if(!createIt && !Exists(forKey))
		{
			return false;
		}
		for(int i = 0; i < map_itn->second->Count(); i++) // Copy data for the new key
		{
			IniKeyValue keyvalue = map_itn->second->Element(i);
			New(forKey, keyvalue.szKeyName.str, keyvalue.szKeyValue.str, keyvalue.szComment.str, true);
		}
	}
	// Remove data
	map_itn->second->RemoveAll();
	map_file.erase(map_itn);

	return true;
}

unsigned int LIB_INI_CLASS::Remove(const char *Key, const char *KeyName, bool isPartial /*= false*/)
{
	unsigned int Rcount = 0;
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return Rcount;
	for(int i = 0; i < map_itn->second->Count(); i++)
	{
		IniKeyValue keyvalue = map_itn->second->Element(i);
		if(isPartial)
		{
			if(!strstr(keyvalue.szKeyName.str, KeyName))
			{
				Rcount++;
				map_itn->second->Remove(i);
			}
		}
		else
		{
			if(LIB_STRING_CLASS::FStrEq(keyvalue.szKeyName.str, KeyName))
			{
				Rcount++;
				map_itn->second->Remove(i);
			}
		}
	}

	return Rcount;
}

unsigned int LIB_INI_CLASS::RemoveAllComments(bool fromKeys, bool fromKeynames)
{
	unsigned int rcount = 0;
	/*for(int i = 0; i < vec_keys.Count(); i++)
	{
		if(vec_keys[i].szComment)
		{
			rcount++;
			vec_keys[i].szComment = NULL;
		}
	}*/
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
	{
		for(int i = 0; i < map_itn->second->Count(); i++)
		{
			map_itn->second->Element(i).szComment.Clean();
			rcount++;
		}
	}
	return rcount;
}

unsigned int LIB_INI_CLASS::RemoveComment(const char *Key, bool isPartial /*= false*/)
{
	unsigned int Rcount = 0;
	/*for(int i = 0; i < vec_keys.Count(); i++)
	{
		if(isPartial)
		{
			if(!strstr(vec_keys[i].szKey, Key))
			{
				Rcount++;
				vec_keys[i].szComment = NULL;
			}
		}
		else
		{
			if(LIB_STRING_CLASS::FStrEq(vec_keys[i].szKey, Key))
			{
				Rcount++;
				vec_keys[i].szComment = NULL;
			}
		}
	}*/
	return Rcount;
}

unsigned int LIB_INI_CLASS::RemoveComment(const char *Key, const char *KeyName, bool isPartial /*= false*/)
{
	int Rcount = 0;
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return Rcount;
	for(int i = 0; i < map_itn->second->Count(); i++)
	{
		if(isPartial)
		{
			if(!strstr(map_itn->second->Element(i).szKeyName.str, KeyName))
			{
				Rcount++;
				map_itn->second->Element(i).szComment.Clean();
			}
		}
		else
		{
			if(LIB_STRING_CLASS::FStrEq(map_itn->second->Element(i).szKeyName.str, KeyName))
			{
				Rcount++;
				map_itn->second->Element(i).szComment.Clean();
			}
		}
	}
	return Rcount;
}

bool LIB_INI_CLASS::New(const char *Key, const char *comment /*= NULL*/)
{
	if(!Key) return false;
	if(Exists(Key)) return false;
	map_file[Key] = new CUtlVector<IniKeyValue>();
	return true;
}

bool LIB_INI_CLASS::New(const char *Key, const char *keyName, const char *KeyValue, const char *comment /*= NULL*/, bool createIt /*= true*/)
{
	if(!Key) return false;
	if(!keyName) return false;
	if(createIt)
		New(Key);
	else if(!Exists(Key)) return false;

	IniKeyValue inikeyvalue;

	inikeyvalue.szKeyName = BasicStr(keyName);
	inikeyvalue.szKeyValue = BasicStr(KeyValue);
	inikeyvalue.szComment = BasicStr(comment);

	map_file[Key]->AddToTail(inikeyvalue);

	return true;
}

unsigned int LIB_INI_CLASS::GetCount() const
{
	return map_file.size();
}

unsigned int LIB_INI_CLASS::GetCount(const char *Key)
{
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return 0;
	return map_itn->second->Count();
}

int LIB_INI_CLASS::GetLine(const char *Key)
{
	int Lcount = -1;
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return Lcount;
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
	{
		Lcount++;
		if(LIB_STRING_CLASS::FStrEq(map_itn->first.str, Key)) break;
	}
	return Lcount;
}

int LIB_INI_CLASS::GetLine(const char *Key, const char *KeyName)
{
	int Lcount = -1;
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return Lcount;
	for(int i = 0; i < map_itn->second->Count(); i++)
	{
		Lcount++;
		if(LIB_STRING_CLASS::FStrEq(map_itn->second->Element(i).szKeyName.str, KeyName)) break;
	}
	return Lcount;
}

int LIB_INI_CLASS::GetIndex(const char *Key, const char *KeyName)
{
	map_itn = map_file.find(Key);
	if(map_itn == map_file.end())
		return -1;
	for(int i = 0; i < map_itn->second->Count(); i++)
		if(LIB_STRING_CLASS::FStrEq(map_itn->second->Element(i).szKeyName.str, KeyName))
			return i;
	return -1;
}

/*spt_inikeys_struct SIniLib::GetElement(int keyIndex)
{
	spt_inikeys_struct tempStruct;
	tempStruct.szKey = NULL;
	tempStruct.szComment = NULL;
	if(keyIndex > SPT_Ini_Data.Count()-1) return tempStruct;
	return SPT_IniKeys_Data[keyIndex];
}

spt_ini_struct SIniLib::GetElement(int keyIndex, int keyNameLine)
{
	spt_ini_struct tempStruct;
	tempStruct.szKey = NULL;
	tempStruct.szKeyName = NULL;
	tempStruct.szKeyValue = NULL;
	tempStruct.szComment = NULL;
	if(keyIndex > SPT_Ini_Data.Count()-1) return tempStruct;
	int count = -1;
	for(int i = 0; i < SPT_Ini_Data.Count(); i++)
	{
		if(FStrEq(SPT_Ini_Data[i].szKey, SPT_IniKeys_Data[keyIndex].szKey))
		{
			count++;
			if(count == keyNameLine)
				return SPT_Ini_Data[i];
		}
	}
	return tempStruct;
}


SIniLib *SIniLib::GetFirst()
{
	if(SPT_Ini_Data.Count() == 0 || SPT_IniKeys_Data.Count() == 0) return NULL;
	SIniLib *newIni = new SIniLib(this);
	return newIni;
}

SIniLib *SIniLib::GetNextKey()
{
	if(iGetNextKey == 0) 
	{
		iGetNextKey++;
		return new SIniLib(this);
	}
	iGetNextKey++;
	iGetNextValue = 0;
	SIniLib* newIni = new SIniLib(this);
	newIni->Delete(0);
	if(newIni->SPT_IniKeys_Data.Count() == 0) return NULL;
	return newIni;
}

SIniLib *SIniLib::GetNextKeyName()
{
	if(SPT_Ini_Data.Count() == 0 || SPT_IniKeys_Data.Count() == 0) return NULL;
	if(GetCount(SPT_IniKeys_Data[0].szKey) <= 1) return NULL;
	if(iGetNextValue == 0)
	{
		iGetNextValue++;
		return new SIniLib(this);
	}
	iGetNextValue++;
	SIniLib* newIni = new SIniLib(this);
	for(int i = 0; i < newIni->SPT_Ini_Data.Count(); i++)
	{
		if(FStrEq(newIni->SPT_Ini_Data[i].szKey, newIni->SPT_IniKeys_Data[0].szKey))
		{
			if(newIni->SPT_Ini_Data.Count()-1 == 0) return NULL;
			newIni->SPT_Ini_Data.Remove(i);
			return newIni;
		}
	}
	return NULL;
}
*/

const char *LIB_INI_CLASS::GetValueStr(const char *Key, const char *KeyName)
{
	int index = GetIndex(Key, KeyName);
	if(index == -1) return NULL;
	return map_file[Key]->Element(index).szKeyValue.ToString();
}

int LIB_INI_CLASS::GetValueInt(const char *Key, const char *KeyName)
{
	const char *value = GetValueStr(Key, KeyName);
	if(value == NULL) return -1;
	return atoi(value);
}

float LIB_INI_CLASS::GetValueFloat(const char *Key, const char *KeyName)
{
	const char *value = GetValueStr(Key, KeyName);
	if(value == NULL) return -1;
	return atof(value);
}

const char *LIB_INI_CLASS::GetComment(const char *Key, const char *KeyName)
{
	int index = GetIndex(Key, KeyName);
	if(index == -1) return NULL;
	return map_file[Key]->Element(index).szComment.ToString();
}

bool LIB_INI_CLASS::SetValue(const char *Key, const char *KeyName, const char *KeyValue, const char *comment /*= NULL*/, bool createIt /*= true*/)
{
	if(!Key) return false;
	if(!KeyName) return false;
	int index = GetIndex(Key, KeyName);
	if(index == -1)
	{
		return createIt ? New(Key, KeyName, KeyValue, comment, true) : false;
	}
	map_file[Key]->Element(index).szKeyValue = BasicStr(KeyValue);
	map_file[Key]->Element(index).szComment = BasicStr(comment);
	return true;
}

bool LIB_INI_CLASS::SetComment(const char *Key, const char *KeyName, const char *comment)
{
	int index = GetIndex(Key, KeyName);
	if(index == -1) return false;
	map_file[Key]->Element(index).szComment = BasicStr(comment);
	return true;
}

void LIB_INI_CLASS::SetHearder(const char *text, bool appendLine /*= true*/)
{
	if(!text) return;
	if(!appendLine)
	{
		fileHearder = BasicStr(text);
	}
	else
	{
		if(fileHearder.IsNULL())
			fileHearder = BasicStr(text);
		else
			fileHearder.Cat(text);
	}
	fileHearder.Cat("\n");
}

bool LIB_INI_CLASS::Rename(const char *Key, const char *NewKey)
{
	return Remove(Key, true, NewKey, true);
}

bool LIB_INI_CLASS::Rename(const char *Key, const char *KeyName, const char *NewKeyName)
{
	int index = GetIndex(Key, KeyName);
	if(index == -1) return false;
	map_file[Key]->Element(index).szKeyName = BasicStr(NewKeyName);
	return true;
}

/*bool LIB_INI_CLASS::Move(const char *Key, const char matchOperator, int lines)
{
	int index = GetIndex(Key);
	if(index == -1) return false;

	int moveTo = index;
	IniKey inikey = vec_keys[index];
	switch(matchOperator)
	{
	case '<':
		vec_keys.Remove(index);
		vec_keys.AddToHead(inikey);
		return true;
	case '>':
		vec_keys.Remove(index);
		vec_keys.AddToTail(inikey);
		return true;
	case '-':
		if(lines <= 0) return false;
		moveTo -= lines;
		break;
	case '+':
		if(lines <= 0) return false;
		moveTo += lines;
		break;
	default:
		return false;
	}

	if(moveTo < 0)
		moveTo = 0;
	else if(moveTo >= vec_keys.Count())
		moveTo = vec_keys.Count()-1;

	if(moveTo == index) return true;
	int elmC = 0;
	if(matchOperator == '-')
		elmC = vec_keys.InsertBefore(moveTo, inikey);
	else
		elmC = vec_keys.InsertAfter(moveTo, inikey);

	if(elmC < index) index++;
	//else if (elmC > index) index--;
	
	vec_keys.Remove(index);
	return true;
}*/

bool LIB_INI_CLASS::Move(const char *Key, const char *KeyName, const char matchOperator, int lines)
{
	int index = GetIndex(Key, KeyName);
	if(index == -1) return false;

	int moveTo = index;
	IniKeyValue tempme = map_file[Key]->Element(index);
	if(matchOperator == '<')
	{
		map_file[Key]->Remove(index);
		map_file[Key]->AddToHead(tempme);
		return true;
	}
	if(matchOperator == '>')
	{
		map_file[Key]->Remove(index);
		map_file[Key]->AddToTail(tempme);
		return true;
	}
	if(lines <= 0) return false;
	if(matchOperator == '-')
	{	moveTo -= lines;}
	else if(matchOperator == '+')
	{	moveTo += lines;}
	else
		return false;

	int count = map_file[Key]->Count();
	if(moveTo < 0)
		moveTo = 0;
	else if(moveTo > count-1)
		moveTo = count-1;

	if(moveTo == index) return true;
	int elmC = 0;
	if(matchOperator == '-')
		elmC = map_file[Key]->InsertBefore(moveTo, tempme);
	else
		elmC = map_file[Key]->InsertAfter(moveTo, tempme);

	if(elmC < index) index++;
	//else if (elmC > index) index--;
	
	map_file[Key]->Remove(index/*-1*/);
	return true;
}

void LIB_INI_CLASS::Join(LIB_INI_CLASS *toJoin, bool replaceValues /*= false*/)
{
	if(!toJoin) return;
	
	for(map_itn = map_file.begin(); map_itn!=toJoin->map_file.end(); ++map_itn)
	{
		if(!Exists(map_itn->first.str))
			New(map_itn->first.str);

		for(int i = 0; i < map_itn->second->Count(); i++)
		{
			IniKeyValue keyvalue = map_itn->second->Element(i);
			int index = GetIndex(map_itn->first.str, keyvalue.szKeyName.str);
			if(index == -1)
			{
				New(map_itn->first.str, keyvalue.szKeyName.str, keyvalue.szKeyValue.str, keyvalue.szComment.str);
				continue;
			}
			if(replaceValues)
			{
				map_itn->second->Element(i).szKeyValue = BasicStr(keyvalue.szKeyValue.str);
				map_itn->second->Element(i).szComment = BasicStr(keyvalue.szComment.str);
				continue;
			}
		}
	}
}

bool LIB_INI_CLASS::Join(const char *file, bool replaceValues /*= false*/)
{
	LIB_INI_CLASS *ini = new LIB_INI_CLASS(file);
	if(!ini->Load()) return false;
	Join(ini, replaceValues);
	ini->~LIB_INI_CLASS();
	return true;
}

bool LIB_INI_CLASS::Write(const char *file /*= NULL*/, const char *extraText /*= NULL*/, bool forceCreate /*= true*/)
{
	if(!file)
		file = pathFile;
	if(!file) return false;

	if(!forceCreate)
		if(!VAR_IFACE_FILESYSTEM->FileExists(file)) return false;

	FileHandle_t pFile = VAR_IFACE_FILESYSTEM->Open(file, "w");
	if(!fileHearder.IsNULL()) VAR_IFACE_FILESYSTEM->FPrintf(pFile, "%s\n",fileHearder);
	if(extraText) VAR_IFACE_FILESYSTEM->FPrintf(pFile, "%s\n",extraText);


	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
	{
		VAR_IFACE_FILESYSTEM->FPrintf(pFile, "\n[%s]\n",map_itn->first.str);
		//if(vec_keys[i].szComment)
		//	VAR_IFACE_FILESYSTEM->FPrintf(pFile, "\t#%s",vec_keys[i].szComment);
			//VAR_IFACE_FILESYSTEM->FPrintf(pFile, "\n");
		for(int i = 0; i < map_itn->second->Count(); i++)
		{
			IniKeyValue keyvalue = map_itn->second->Element(i);
			VAR_IFACE_FILESYSTEM->FPrintf(pFile, "%s=%s",keyvalue.szKeyName.str, keyvalue.szKeyValue.str);
			if(!keyvalue.szComment.IsNULL())
				VAR_IFACE_FILESYSTEM->FPrintf(pFile, "\t#%s", keyvalue.szComment.str);
			VAR_IFACE_FILESYSTEM->FPrintf(pFile, "\n");
		}
	}
	VAR_IFACE_FILESYSTEM->Close(pFile);
	return true;
}

bool LIB_INI_CLASS::Save(const char *file /*= NULL*/, const char *extraText /*= NULL*/, bool forceCreate /*= true*/)
{
	return Write(file, extraText, forceCreate);
}

KeyValues *LIB_INI_CLASS::Convert(const char *nameSpace /*= "Ini2KV"*/)
{
	KeyValues *iniToKv = new KeyValues(nameSpace);
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
	{
		KeyValues *tempKv = new KeyValues(map_itn->first.str);
		for(int i = 0; i < map_itn->second->Count(); i++)
		{
			IniKeyValue keyvalue = map_itn->second->Element(i);
			tempKv->SetString(keyvalue.szKeyName.str, keyvalue.szKeyValue.str);
		}
		iniToKv->AddSubKey(tempKv);
	}
	return iniToKv;
}

void LIB_INI_CLASS::Convert(KeyValues *kv)
{
	if(!kv) return;
	Reset();
	KeyValues *tempForeachKv, *tempValueForeachKv;
	for(tempForeachKv = kv->GetFirstSubKey(); tempForeachKv; tempForeachKv = tempForeachKv->GetNextKey())
	{
		const char *Key = tempForeachKv->GetName();
		if(!Key) continue;
		New(Key);
		for(tempValueForeachKv = tempForeachKv->GetFirstValue(); tempValueForeachKv; tempValueForeachKv = tempValueForeachKv->GetNextValue())
		{
			New(Key, tempValueForeachKv->GetName(), tempValueForeachKv->GetString(), NULL, false);
		}
	}
}

void LIB_INI_CLASS::SetFilePath(const char *newFile)
{
	LIB_STRING_CLASS::StrNew(newFile);
}

void LIB_INI_CLASS::PrintHearder()
{
	Msg("\n--------------------------------------\nFile: %s\n\n%s\n",pathFile, fileHearder.str);
	Msg("\n--------------------------------------\n\n");

}

void LIB_INI_CLASS::Print(const char *Key /*= NULL*/)
{
	Msg("\n--------------------------------------\nFile: %s\n\n",pathFile);
	if(Key)
	{
		map_itn = map_file.find(Key);
		if(map_itn == map_file.end())
		{
			Msg("The section [%s] doesn't exists!\n", Key);
		}
		else
		{
			Msg("[%s]\n", Key);
			for(int i = 0; i < map_itn->second->Count(); i++)
			{
				IniKeyValue keyvalue = map_itn->second->Element(i);
				Msg("%s=%s", keyvalue.szKeyName.str, keyvalue.szKeyValue.str);
				if(!keyvalue.szComment.IsNULL())
					Msg("\t#%s", keyvalue.szComment.str);
				Msg("\n");
			}
		}
	}
	else
	{
		for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
		{
			Msg("[%s]\n", map_itn->first.str);
			for(int i = 0; i < map_itn->second->Count(); i++)
			{
				IniKeyValue keyvalue = map_itn->second->Element(i);
				Msg("%s=%s", keyvalue.szKeyName.str, keyvalue.szKeyValue.str);
				if(!keyvalue.szComment.IsNULL())
					Msg("\t#%s", keyvalue.szComment.str);
				Msg("\n");
			}
			Msg("\n");
		}
	}
	Msg("--------------------------------------\n\n");
}

void LIB_INI_CLASS::PrintKeys()
{
	Msg("\n--------------------------------------\nFile: %s\n\n",pathFile);
	for(map_itn = map_file.begin(); map_itn!=map_file.end(); ++map_itn)
	{
		Msg("[%s]\n",map_itn->first.str);
	}
	Msg("\n--------------------------------------\n\n");
}
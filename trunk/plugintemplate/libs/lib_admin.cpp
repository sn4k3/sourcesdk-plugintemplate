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
#include "includes/default.h"

//=================================================================================
// LIB_ADMIN_CLASS::Admin Functions
//=================================================================================
bool LIB_ADMIN_CLASS::Admin::HaveAdminFlag(const char *flags, bool searchOnGroups /*= true*/)
{
	CUtlVector<const char *>* flags_split = LIB_STRING_CLASS::StrSplit(flags, ' ');
	bool found = false;
	for(int i = 0; i < flags_split->Count(); i++)
	{
		found = false;
		const char *flagCheck = flags_split->Element(i);
		for(int x = 0; x < vec_adminflags->Count(); x++)
		{
			found = LIB_STRING_CLASS::FStrEq(vec_adminflags->Element(x), flagCheck);
			if(found)
				break;
		}
		if(found) continue;
		if(!searchOnGroups) return false; // A flag missing, can't check on groups
		for(int y = 0; y < vec_admingroups->Count(); y++) // Not found, search on groups too
		{
			for(int z = 0; z < vec_admingroups->Element(y).vec_flags.Count(); z++)
			{
				found = LIB_STRING_CLASS::FStrEq(vec_admingroups->Element(y).vec_flags[z], flagCheck);
				if(found)
					break;
			}
			if(found)
				break;
		}
		if(!found) return false; // A flag missing, false
	}
	return true;
}

bool LIB_ADMIN_CLASS::Admin::HaveImmunityFlag(const char *flags, bool searchOnGroups /*= true*/)
{
	CUtlVector<const char *>* flags_split = LIB_STRING_CLASS::StrSplit(flags, ' ');
	bool found = false;
	for(int i = 0; i < flags_split->Count(); i++)
	{
		found = false;
		const char *flagCheck = flags_split->Element(i);
		for(int x = 0; x < vec_immunityflags->Count(); x++)
		{
			found = LIB_STRING_CLASS::FStrEq(vec_immunityflags->Element(x), flagCheck);
			if(found)
				break;
		}
		if(found) continue;
		if(!searchOnGroups) return false; // A flag missing, can't check on groups
		for(int y = 0; y < vec_immunitygroups->Count(); y) // Not found, search on groups too
		{
			for(int z = 0; z < vec_immunitygroups->Element(y).vec_flags.Count(); z)
			{
				found = LIB_STRING_CLASS::FStrEq(vec_immunitygroups->Element(y).vec_flags[z], flagCheck);
				if(found)
					break;
			}
			if(found)
				break;
		}
		if(!found) return false; // A flag missing, false
	}
	return true;
}

bool LIB_ADMIN_CLASS::Admin::UpdateClient(const char *newSteamId /*= NULL*/, const char *name /*= NULL*/, const char *contact /*= NULL*/, const char *aflags /*= NULL*/, const char *iflags /*= NULL*/)
{
	if(newSteamId)
		szSteamID = BasicStr(newSteamId);
	if(name)
		szName = BasicStr(name);
	if(contact)
		szContact = BasicStr(contact);
	#pragma message("FIX THIS")
	return true;
}

//=================================================================================
// LIB_ADMIN_CLASS Functions
//=================================================================================
// Constructor
LIB_ADMIN_CLASS::LIB_ADMIN_CLASS()
{
}
// Destructor
LIB_ADMIN_CLASS::~LIB_ADMIN_CLASS()
{
	Reset();
}

bool LIB_ADMIN_CLASS::Load(const char *file)
{
	KeyValues *kvOperation, *kvLoopKey, *kvLoopValue, *kvMain = new KeyValues("admins");
	if(!kvMain->LoadFromFile(VAR_IFACE_FILESYSTEM, file))
	{
		DevMsg("AdminLib: Can't load Admin file\n%s\n", file);
		return false;
	}
	Reset();
	this->file = file;
	fileKeyname = kvMain->GetName();
	int x = 0;
	const char *keyname;

	fileVersion = kvMain->GetString("version", "1.0");
	kvOperation = kvMain->FindKey("groups");

	if(kvOperation)
	{
		kvLoopKey = kvOperation->FindKey("Admin");
		if(kvLoopKey)
		{
			for(kvLoopValue = kvLoopKey->GetFirstValue(); kvLoopValue; kvLoopValue = kvLoopValue->GetNextValue())
			{
				if(IsAGroup(kvLoopValue->GetName()))
				{
					for(int i = 0; i < vec_admingroups.Count(); i++)
					{
						if (LIB_STRING_CLASS::FStrEq(vec_admingroups[i].Name, kvLoopValue->GetName()))
						{
							CUtlVector<const char *>* flag_split = LIB_STRING_CLASS::StrSplit(kvLoopValue->GetString(), ' ');
							for(int y = 0; y < flag_split->Count(); y++)
							{
								vec_admingroups[i].vec_flags.AddToTail(flag_split->Element(y));
							}
							break;
						}
					}
				}
				else
				{
					x = vec_admingroups.AddToTail();
					vec_admingroups[x].Name = kvLoopValue->GetName();
					CUtlVector<const char *>* flag_split = LIB_STRING_CLASS::StrSplit(kvLoopValue->GetString(), ' ');
					for(int y = 0; y < flag_split->Count(); y++)
					{
						vec_admingroups[x].vec_flags.AddToTail(flag_split->Element(y));
					}
				}
			}
		}
		kvLoopKey = kvOperation->FindKey("Immunity");
		if(kvLoopKey)
		{
			for(kvLoopValue = kvLoopKey->GetFirstValue(); kvLoopValue; kvLoopValue = kvLoopValue->GetNextValue())
			{
				if(IsIGroup(kvLoopValue->GetName()))
				{
					for(int i = 0; i < vec_immunitygroups.Count(); i++)
					{
						if (LIB_STRING_CLASS::FStrEq(vec_immunitygroups[i].Name, kvLoopValue->GetName()))
						{
							CUtlVector<const char *>* flag_split = LIB_STRING_CLASS::StrSplit(kvLoopValue->GetString(), ' ');
							for(int y = 0; y < flag_split->Count(); y++)
							{
								vec_immunitygroups[i].vec_flags.AddToTail(flag_split->Element(y));
							}
							break;
						}
					}
				}
				else
				{
					x = vec_immunitygroups.AddToTail();
					vec_immunitygroups[x].Name = kvLoopValue->GetName();
					CUtlVector<const char *>* flag_split = LIB_STRING_CLASS::StrSplit(kvLoopValue->GetString(), ' ');
					for(int y = 0; y < flag_split->Count(); y++)
					{
						vec_immunitygroups[x].vec_flags.AddToTail(flag_split->Element(y));
					}
				}
			}
		}
	}
	kvOperation = kvMain->FindKey("players");
	if(kvOperation)
	{
		for(kvLoopKey = kvOperation->GetFirstSubKey(); kvLoopKey; kvLoopKey = kvLoopKey->GetNextKey())
		{
			x = 0;
			keyname = kvLoopKey->GetName();
			while(IsAdminByUniqueName(keyname))
			{
				x++;
				keyname = LIB_STRING_CLASS::StrFormat("%s_%i",kvLoopKey->GetName(),x);
			}
			x = vec_admins.AddToTail();
			vec_admins[x].szClientName = keyname;

			for(kvLoopValue = kvLoopKey->GetFirstValue(); kvLoopValue; kvLoopValue = kvLoopValue->GetNextValue())
			{
				keyname = AssertValue(kvLoopValue->GetName());
				if(!keyname) continue;


				if (LIB_STRING_CLASS::FStrEq(keyname, "STEAMID"))
				{
					if(IsAdminBySteamID(kvLoopValue->GetString())) // Duplicated SteamID
					{
						vec_admins.Remove(x);
						break;
					}
				}
				SetClientValue(keyname, kvLoopValue->GetString(), x);
			}
			ParseClient(x);
		}
	}
	return true;
}

void LIB_ADMIN_CLASS::Reset()
{
	file = NULL;
	vec_admins.RemoveAll();
	vec_admingroups.RemoveAll();
	vec_immunitygroups.RemoveAll();
}

bool LIB_ADMIN_CLASS::New(const char *fileToSaveAdmins, const char *fileKeyName /*= NULL*/)
{
	Reset();
	if(strlen(fileToSaveAdmins) < 5) return false;
	file = LIB_STRING_CLASS::StrNew(fileToSaveAdmins);
	fileKeyname = LIB_STRING_CLASS::StrNew(fileKeyName);

	return true;
}

void LIB_ADMIN_CLASS::Save()
{
	if(!file) return ;
	KeyValues *kv = CUtlToKv(fileKeyname);
	kv->SaveToFile(VAR_IFACE_FILESYSTEM, file);
}

void LIB_ADMIN_CLASS::Save(const char *saveToFile, const char *keyvalueName /*= NULL*/)
{
	if(!saveToFile) return ;
	KeyValues *kv = CUtlToKv(keyvalueName);
	kv->SaveToFile(VAR_IFACE_FILESYSTEM, saveToFile, "MOD");
}

int LIB_ADMIN_CLASS::GetFileVersion()
{
	return atoi(fileVersion);
}

bool LIB_ADMIN_CLASS::IsAdmin(const char *idOrName)
{
	if(!idOrName) return false;
	const char *isSteam = LIB_STRING_CLASS::StrToUpper(idOrName);
	if(LIB_STRING_CLASS::StrLeftEq(isSteam, "STEAM_")) 
		return IsAdminBySteamID(isSteam);
	else
		return IsAdminByUniqueName(idOrName);
}

bool LIB_ADMIN_CLASS::IsAdminBySteamID(const char *steamid)
{
	if(!steamid) return false;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szSteamID.str, steamid))
			return true;
	}
	return false;
}

bool LIB_ADMIN_CLASS::IsAdminByUniqueName(const char *UniqueName)
{
	if(!UniqueName) return false;

	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szClientName.str, UniqueName))
			return true;
	}
	return false;
}

bool LIB_ADMIN_CLASS::IsAGroup(const char *name)
{
	FOR_EACH_VEC(vec_admingroups, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admingroups[i].Name, name))
			return true;
	}
	return false;
}

bool LIB_ADMIN_CLASS::IsIGroup(const char *name)
{
	FOR_EACH_VEC(vec_immunitygroups, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_immunitygroups[i].Name, name))
			return true;
	}
	return false;
}

bool LIB_ADMIN_CLASS::HaveAdminFlag(const char *string, const char *flags)
{
	if(!string) return false;
	char *isSteam = LIB_STRING_CLASS::StrToUpper(string);
	if(LIB_STRING_CLASS::StrLeftEq(isSteam, "STEAM_")) 
		return HaveAdminFlagBySteamID(isSteam, flags);
	else
		return HaveAdminFlagByUniqueName(string, flags);
}

bool LIB_ADMIN_CLASS::HaveAdminFlagBySteamID(const char *steamid, const char *flags)
{
	if(!steamid) return false;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szSteamID.str, steamid))
		{
			return vec_admins[i].HaveAdminFlag(flags);
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::HaveAdminFlagByUniqueName(const char *UniqueName, const char *flags)
{
	if(!UniqueName) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szClientName.str, UniqueName))
		{
			return vec_admins[i].HaveAdminFlag(flags);
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::HaveImmunityFlag(const char *idOrName, const char *flags)
{
	if(!idOrName) return false;
	char *isSteam = LIB_STRING_CLASS::StrToUpper(idOrName);
	if(LIB_STRING_CLASS::StrLeftEq(isSteam, "STEAM_")) 
		return HaveImmunityFlagBySteamID(isSteam, flags);
	else
		return HaveImmunityFlagByUniqueName(idOrName, flags);
}

bool LIB_ADMIN_CLASS::HaveImmunityFlagBySteamID(const char *steamid, const char *flags)
{
	if(!steamid) return false;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szSteamID.str, steamid))
		{
			return vec_admins[i].HaveImmunityFlag(flags);
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::HaveImmunityFlagByUniqueName(const char *UniqueName, const char *flags)
{
	if(!UniqueName) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szClientName.str, UniqueName))
		{
			return vec_admins[i].HaveImmunityFlag(flags);
		}
	}
	return false;
}

const char *LIB_ADMIN_CLASS::AddClient(const char *steamid, const char *UniqueName /*= NULL*/, const char *name /*= NULL*/, const char *contact /*= NULL*/, const char *aflags /*= NULL*/, const char *iflags /*= NULL*/, const char *agroup /*= NULL*/, const char *igroup /*= NULL*/, bool saveToFile /*= false*/)
{
	if(!steamid) return NULL;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_"))	return NULL;
	BasicStr uniqueName = BasicStr("Client");
	if(UniqueName) uniqueName = BasicStr(UniqueName);
	if(IsAdminBySteamID(steamid)) return NULL;
	int x = 0;
	char copyUniqueName[1024];
	snprintf(copyUniqueName, sizeof(copyUniqueName), "%s", uniqueName.str);
	while(IsAdminByUniqueName(copyUniqueName))
	{
		x++;
		snprintf(copyUniqueName, sizeof(copyUniqueName), "%s_%i", uniqueName.str,x);
	}
	Admin admin;
	admin.szClientName = BasicStr(copyUniqueName);
	admin.szSteamID = BasicStr(steamid);
	admin.szName = BasicStr(name);
	admin.szContact = BasicStr(contact);
	x = vec_admins.AddToTail(admin);
	Msg("Client: %s\n", admin.szClientName);
	#pragma message("FIX THIS")
	/*if(aflags)
		strncpy(vec_admins[x].szAFlags, aflags, 1024);
	if(iflags)
		strncpy(vec_admins[x].szIFlags, iflags, 1024);
	if(agroup)
		strncpy(vec_admins[x].szAGroup, agroup, 1024);
	if(igroup)
		strncpy(vec_admins[x].szIGroup, igroup, 1024);

	ParseClient(x);*/
	if(saveToFile)
		Save(file, fileKeyname);
	return admin.szClientName.ToString();
}

bool LIB_ADMIN_CLASS::RemoveClient(const char *idOrName, bool saveToFile /*= false*/)
{
	if(!idOrName) return false;
	char *isSteam = LIB_STRING_CLASS::StrToUpper(idOrName);
	if(LIB_STRING_CLASS::StrLeftEq(isSteam, "STEAM_")) 
		return RemoveClientBySteamID(isSteam, saveToFile);
	else
		return RemoveClientByUniqueName(idOrName, saveToFile);
}

bool LIB_ADMIN_CLASS::RemoveClientBySteamID(const char *steamid, bool saveToFile /*= false*/)
{
	if(!steamid) return false;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szSteamID.str, steamid))
		{
			vec_admins.Remove(i);
			if(saveToFile)
				Save(file, fileKeyname);
			return true;
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::RemoveClientByUniqueName(const char *UniqueName, bool saveToFile /*= false*/)
{
	if(!UniqueName) return false;
	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szClientName.str, UniqueName))
		{
			vec_admins.Remove(i);
			if(saveToFile)
				Save(file, fileKeyname);
			return true;
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::UpdateClientBySteamID(const char *steamid, const char *UniqueName /*= NULL*/, const char *newSteamId /*= NULL*/, const char *name /*= NULL*/, const char *contact /*= NULL*/, const char *aflags /*= NULL*/, const char *iflags /*= NULL*/, const char *agroup /*= NULL*/, const char *igroup /*= NULL*/, bool saveToFile /*= false*/)
{
	if(!steamid) return false;
	steamid = LIB_STRING_CLASS::StrToUpper(steamid);
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;

	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szSteamID.str, steamid))
		{
			if(UniqueName)
				if(IsAdminByUniqueName(UniqueName))
					return false;
			if(newSteamId)
				if(IsAdminBySteamID(newSteamId))
					return false;
			vec_admins[i].UpdateClient(newSteamId, name, contact, aflags, iflags);
			#pragma message("FIX THIS")

			if(saveToFile)
				Save(file, fileKeyname);			
			return true;
		}
	}
	return false;
}

bool LIB_ADMIN_CLASS::UpdateClientByUniqueName(const char *UniqueName, const char *NewUniqueName /*= NULL*/, const char *steamid /*= NULL*/, const char *name /*= NULL*/, const char *contact /*= NULL*/, const char *aflags /*= NULL*/, const char *iflags /*= NULL*/, const char *agroup /*= NULL*/, const char *igroup /*= NULL*/, bool saveToFile /*= false*/)
{
	if(!UniqueName) return false;

	FOR_EACH_VEC(vec_admins, i)
	{
		if (LIB_STRING_CLASS::FStrEq(vec_admins[i].szClientName.str, UniqueName))
		{
			if(NewUniqueName)
				if(IsAdminByUniqueName(NewUniqueName))
					return false;
			if(steamid)
				if(IsAdminBySteamID(steamid))
					return false;
			vec_admins[i].UpdateClient(steamid, name, contact, aflags, iflags);
			#pragma message("FIX THIS")

			if(saveToFile)
				Save(file, fileKeyname);			
			return true;
		}
	}
	return false;
}

void LIB_ADMIN_CLASS::MakeEmptyAdminFile(const char *saveToFile, const char *KeyName /*= NULL*/, bool makePlayers /*= true*/, bool makePlayersName /*= true*/, bool makePlayersSteamID /*= true*/, bool makePlayersContact /*= true*/, bool makePlayersAFlags /*= true*/, bool makePlayersIFlags /*= true*/, bool makePlayersAGroup /*= true*/, bool makePlayersIGroup /*= true*/, bool makeGroups /*= true*/, bool makeAGroups /*= true*/, bool makeIGroups /*= true*/)
{
	if(!saveToFile) return ;
	if(!KeyName) KeyName = "admins";

	KeyValues *sub_kv, *sub_kv2, *admin_file_kv = new KeyValues(KeyName);
	admin_file_kv->SetString("version", LIB_ADMIN_VERSION);
	if(makePlayers)
	{
		sub_kv = new KeyValues("players");
		sub_kv2 = new KeyValues("Client Sample");
		if(makePlayersName)
			sub_kv2->SetString("Name", "Client Name or Nick");
		if(makePlayersSteamID)
			sub_kv2->SetString("SteamID", "STEAM_x:x:00000000");
		if(makePlayersContact)
			sub_kv2->SetString("Contact", "mycontact@operator.com");
		if(makePlayersAFlags)
			sub_kv2->SetString("AFlags", "set admin flags here separated by spaces");
		if(makePlayersIFlags)
			sub_kv2->SetString("IFlags", "set immunity flags here separated by spaces");
		if(makePlayersAGroup)
			sub_kv2->SetString("AGroup", "myAgroup");
		if(makePlayersAGroup)
			sub_kv2->SetString("IGroup", "myIgroup");
		admin_file_kv->AddSubKey(sub_kv2);
	}

	if(makeGroups)
	{
		sub_kv = new KeyValues("groups");
		if(makeAGroups)
		{
			sub_kv2 = new KeyValues("myAgroup");
			sub_kv2->SetString("AFlags", "set group admin flags here separated by spaces");
			sub_kv->AddSubKey(sub_kv2);
		}
		if(makeIGroups)
		{
			sub_kv2 = new KeyValues("myIgroup");
			sub_kv2->SetString("IFlags", "set group immunity flags here separated by spaces");
			sub_kv->AddSubKey(sub_kv2);
		}
		admin_file_kv->AddSubKey(sub_kv);
	}
	admin_file_kv->SaveToFile(VAR_IFACE_FILESYSTEM, saveToFile);
}

const char *LIB_ADMIN_CLASS::AssertValue(const char *value)
{
	if(LIB_STRING_CLASS::FStrEq(value, "NAME") ||LIB_STRING_CLASS::FStrEq(value, "NICK"))
		return "NAME";
	if(LIB_STRING_CLASS::FStrEq(value, "STEAMID") ||LIB_STRING_CLASS::FStrEq(value, "STEAM"))
		return "STEAMID";
	if(LIB_STRING_CLASS::FStrEq(value, "CONTACT") ||LIB_STRING_CLASS::FStrEq(value, "MAIL") ||LIB_STRING_CLASS::FStrEq(value, "EMAIL") ||LIB_STRING_CLASS::FStrEq(value, "E-MAIL"))
		return "CONTACT";
	if(LIB_STRING_CLASS::FStrEq(value, "AFLAGS") ||LIB_STRING_CLASS::FStrEq(value, "ADMIN FLAGS") ||LIB_STRING_CLASS::FStrEq(value, "AF"))
		return "AFLAGS";
	if(LIB_STRING_CLASS::FStrEq(value, "IFLAGS") ||LIB_STRING_CLASS::FStrEq(value, "IMMUNITY FLAGS") ||LIB_STRING_CLASS::FStrEq(value, "IF"))
		return "IFLAGS";
	if(LIB_STRING_CLASS::FStrEq(value, "AGROUP") ||LIB_STRING_CLASS::FStrEq(value, "ADMIN GROUP") ||LIB_STRING_CLASS::FStrEq(value, "AG"))
		return "AGROUP";
	if(LIB_STRING_CLASS::FStrEq(value, "IGROUP") ||LIB_STRING_CLASS::FStrEq(value, "IMMUNITY GROUP") ||LIB_STRING_CLASS::FStrEq(value, "IG"))
		return "IGROUP";
	return NULL;
}

void LIB_ADMIN_CLASS::SetClientValue(const char *type, const char *value, int i)
{
	if(LIB_STRING_CLASS::FStrEq(type, "NAME"))
		vec_admins[i].szName = value;
	else if(LIB_STRING_CLASS::FStrEq(type, "STEAMID"))
	{
		value = LIB_STRING_CLASS::StrToUpper(value);
		if(!LIB_STRING_CLASS::StrLeftEq(value, "STEAM_")) return ;
		vec_admins[i].szSteamID = value;
	}
	else if(LIB_STRING_CLASS::FStrEq(type, "CONTACT"))
		vec_admins[i].szContact = value;
#pragma message("FIX THIS")
	/*else if(LIB_STRING_CLASS::FStrEq(type, "AFLAGS"))
		if(strlen(vec_admins[i].szAFlags) > 0)
		{
			vec_admins[i].szAFlags, MAX_STR_LEN, "%s %s", vec_admins[i].szAFlags, value);
		}
		else
			V_strncpy(vec_admins[i].szAFlags, value, MAX_STR_LEN);
	else if(LIB_STRING_CLASS::FStrEq(type, "IFLAGS"))
		if(strlen(vec_admins[i].szIFlags) > 0)
		{
			V_snprintf(vec_admins[i].szIFlags, MAX_STR_LEN, "%s %s", vec_admins[i].szIFlags, value);
		}
		else
			V_strncpy(vec_admins[i].szIFlags, value, MAX_STR_LEN);
	else if(LIB_STRING_CLASS::FStrEq(type, "AGROUP"))
		if(strlen(vec_admins[i].szAGroup) > 0)
		{
			V_snprintf(vec_admins[i].szAGroup, MAX_STR_LEN, "%s %s", vec_admins[i].szAGroup, value);
		}
		else
			V_strncpy(vec_admins[i].szAGroup, value, MAX_STR_LEN);
	else if(LIB_STRING_CLASS::FStrEq(type, "IGROUP"))
		if(strlen(vec_admins[i].szIGroup) > 0)
		{
			V_snprintf(vec_admins[i].szIGroup, MAX_STR_LEN, "%s %s", vec_admins[i].szIGroup, value);
		}
		else
			V_strncpy(vec_admins[i].szIGroup, value, MAX_STR_LEN);*/
}

void LIB_ADMIN_CLASS::ParseClient(int x)
{
/*	// Begin update AFlags
	char *realaflags = "0";
	if(strlen(vec_admins[x].szAFlags) > 0)
		realaflags = vec_admins[x].szAFlags;
	if(strlen(vec_admins[x].szAGroup) > 0)
	{
		for(int i = 0; i < vec_admingroups.Count(); i++)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_admingroups[i].szGroupName, vec_admins[x].szAGroup) && strlen(vec_admingroups[i].szAFlags) > 0)
			{
				if(strlen(realaflags))
					realaflags = LIB_STRING_CLASS::StrFormat("%s %s", realaflags, vec_admingroups[i].szAFlags);
				else
					realaflags = vec_admingroups[i].szAFlags;
			}
		}
	}
	if(!LIB_STRING_CLASS::FStrEq(realaflags,"0"))
		strncpy(vec_admins[x].szRealAFlags, realaflags, 1024);
	// End update AFlags

	// Begin update IFlags
	char *realiflags = "0";
	if(strlen(vec_admins[x].szAFlags) > 0)
		realiflags = vec_admins[x].szIFlags;
	if(strlen(vec_admins[x].szAGroup) > 0)
	{
		for(int i = 0; i < vec_immunitygroups.Count(); i++)
		{
			if(LIB_STRING_CLASS::FStrEq(vec_immunitygroups[i].szGroupName, vec_admins[x].szIGroup) && strlen(vec_immunitygroups[i].szIFlags) > 0)
			{
				if(!realiflags)
					realiflags = LIB_STRING_CLASS::StrFormat("%s %s", realiflags, vec_immunitygroups[i].szIFlags);
				else
					realiflags = vec_immunitygroups[i].szIFlags;
			}
		}
	}
	if(!LIB_STRING_CLASS::FStrEq(realiflags,"0"))
		strncpy(vec_admins[x].szRealIFlags, realiflags, 1024);
	// End update IFlags*/
}

KeyValues *LIB_ADMIN_CLASS::CUtlToKv(const char *keyvalueName /*= NULL*/)
{
	if(!keyvalueName) keyvalueName = LIB_STRING_CLASS::StrNew("admins");
	KeyValues *admin_file_kv = new KeyValues(keyvalueName);
	admin_file_kv->SetString("version", LIB_ADMIN_VERSION);
	KeyValues *sub_kv2, *sub_kv = new KeyValues("players");
	for(int i = 0; i < vec_admins.Count(); i++)
	{
		Msg("Key: %s\n", vec_admins[i].szClientName.str);
		sub_kv2 = new KeyValues(vec_admins[i].szClientName.str);
		if(vec_admins[i].szName.len > 0)
			sub_kv2->SetString("Name", vec_admins[i].szName.str);
		if(vec_admins[i].szSteamID.len > 0)
			sub_kv2->SetString("SteamID", vec_admins[i].szSteamID.str);
		if(vec_admins[i].szContact.len > 0)
			sub_kv2->SetString("Contact", vec_admins[i].szContact.str);
#pragma message("FIX THIS")
		/*if(strlen(vec_admins[i].szAFlags) > 0)
			sub_kv2->SetString("AFlags", vec_admins[i].szAFlags);
		if(strlen(vec_admins[i].szIFlags) > 0)
			sub_kv2->SetString("IFlags", vec_admins[i].szIFlags);
		if(strlen(vec_admins[i].szAGroup) > 0)
			sub_kv2->SetString("AGroup", vec_admins[i].szAGroup);
		if(strlen(vec_admins[i].szIGroup) > 0)
			sub_kv2->SetString("IGroup", vec_admins[i].szIGroup);*/

		sub_kv->AddSubKey(sub_kv2);
	}
	admin_file_kv->AddSubKey(sub_kv);
	sub_kv = new KeyValues("groups");
	sub_kv2 = new KeyValues("Admin");
	FOR_EACH_VEC(vec_admingroups, i)
	{
		char flags[MAX_STR_LEN] = "";
		FOR_EACH_VEC(vec_admingroups[i].vec_flags, x)
			V_snprintf(flags, MAX_STR_LEN, "%s %s", flags, vec_admingroups[i].vec_flags[x]);
		sub_kv2->SetString(vec_admingroups[i].Name, flags);
	}
	sub_kv->AddSubKey(sub_kv2);
	sub_kv2 = new KeyValues("Immunity");
	FOR_EACH_VEC(vec_immunitygroups, i)
	{
		char flags[MAX_STR_LEN];
		FOR_EACH_VEC(vec_immunitygroups[i].vec_flags, x)
			V_snprintf(flags, MAX_STR_LEN, "%s %s", flags, vec_immunitygroups[i].vec_flags[x]);
		sub_kv2->SetString(vec_immunitygroups[i].Name, flags);
	}
	sub_kv->AddSubKey(sub_kv2);
	admin_file_kv->AddSubKey(sub_kv);
	return admin_file_kv;
}

void LIB_ADMIN_CLASS::DebugClients()
{
	Msg("-----------------Clients----------------\n");
	for(int i = 0; i < vec_admins.Count(); i++)
	{
		Msg("Client Unique Name: %s\n", vec_admins[i].szClientName.str);
		if(vec_admins[i].szName.len > 1)
			Msg("Name: %s\n", vec_admins[i].szName.str);
		if(vec_admins[i].szSteamID.len > 5)
			Msg("SteamID: %s\n", vec_admins[i].szSteamID.str);
		if(vec_admins[i].szContact.len > 4)
			Msg("Contact: %s\n", vec_admins[i].szContact.str);
#pragma message("FIX THIS")
		/*if(strlen(vec_admins[i].szAFlags) > 0)
			Msg("AFlags: %s\n", vec_admins[i].szAFlags);
		if(strlen(vec_admins[i].szIFlags) > 0)
			Msg("IFlags: %s\n", vec_admins[i].szIFlags);
		if(strlen(vec_admins[i].szRealAFlags) > 0)
			Msg("RealAFlags: %s\n", vec_admins[i].szRealAFlags);
		if(strlen(vec_admins[i].szRealIFlags) > 0)
			Msg("RealIFlags: %s\n", vec_admins[i].szRealIFlags);
		if(strlen(vec_admins[i].szAGroup) > 0)
			Msg("AGroup: %s\n", vec_admins[i].szAGroup);
		if(strlen(vec_admins[i].szIGroup) > 0)
			Msg("IGroup: %s\n", vec_admins[i].szIGroup);*/
		Msg("---------------------------------------\n");
	}
}

void LIB_ADMIN_CLASS::DebugGroups()
{
	Msg("----------------ADMIN GROUPS-----------------\n");
	FOR_EACH_VEC(vec_admingroups, i)
	{
		Msg("Name: %s\n", vec_admingroups[i].Name);
		Msg("Admin Flags:");
		FOR_EACH_VEC(vec_admingroups[i].vec_flags, x)
			Msg(" %s", vec_admingroups[i].vec_flags[x]);
		Msg("\n----------------------------------------\n");
	}
	Msg("----------------IMMUNITY GROUPS-----------------\n");
	FOR_EACH_VEC(vec_immunitygroups, i)
	{
		Msg("Name: %s\n", vec_immunitygroups[i].Name);
		Msg("Immunity Flags:");
		FOR_EACH_VEC(vec_immunitygroups[i].vec_flags, x)
			Msg(" %s", vec_immunitygroups[i].vec_flags[x]);
		Msg("\n----------------------------------------\n");
	}
}

/*************************
*	  Easy Admin Class
*************************/

// Constructor
LIB_EASYADMIN_CLASS::LIB_EASYADMIN_CLASS(const char *adminFile /*= NULL*/)
{
	adminFile = NULL;
	if(adminFile)
		this->adminFile = LIB_STRING_CLASS::StrNew(adminFile);
}

// Destructor
LIB_EASYADMIN_CLASS::~LIB_EASYADMIN_CLASS()
{
	Reset();
	adminFile = NULL;
}

// Clean up all admins
void LIB_EASYADMIN_CLASS::Reset()
{
	Admins.RemoveAll();
}

// Add an admin
bool LIB_EASYADMIN_CLASS::Add(const char *steamid)
{
	if(!steamid) return false;
	if(!LIB_STRING_CLASS::StrLeftEq(steamid, "STEAM_")) return false;
	if(IsAdmin(steamid)) return false;
	Admins.AddToTail(LIB_STRING_CLASS::StrToUpper(steamid));
	return true;
}

// Add admins, from server players
// Filters allowed
// Return how many players got added
int LIB_EASYADMIN_CLASS::AddFromServer(const char *players)
{
	MRecipientFilter mrf;
	mrf.AddByFilter(players, false, false);
	int count = 0;
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));
		if(!player->IsValid()) continue;
		if(player->PlayerInfo()->IsFakeClient()) continue;
		if(Add(player->SteamID()))
			count++;
		player->~LIB_PLAYER_CLASS();
	}
	
	return count;
}

// Add an lan players as admin
// STEAM_ID_LAN
void LIB_EASYADMIN_CLASS::AddLan()
{
	Admins.AddToTail("STEAM_ID_LAN");
}

// Remove an admin
bool LIB_EASYADMIN_CLASS::Remove(const char *steamid)
{
	int index = GetIndex(steamid);
	if (index < 0) return false;
	Admins.Remove(index);
	return true;
}

// Check if a player is admin
bool LIB_EASYADMIN_CLASS::IsAdmin(const char *steamid)
{
	FOR_EACH_VEC(Admins, i)
		if(LIB_STRING_CLASS::FStrEq(steamid, Admins[i]))
			return true;
	return false;
	return GetIndex(steamid) != -1; // other way
}

// Get steamid index on the list
int LIB_EASYADMIN_CLASS::GetIndex(const char *steamid)
{
	FOR_EACH_VEC(Admins, i)
		if(LIB_STRING_CLASS::FStrEq(steamid, Admins[i]))
			return i;
	return -1;
}

// Load admins from a text file
// One Steamid per line
bool LIB_EASYADMIN_CLASS::LoadFromFile(const char *path)
{
	adminFile = LIB_STRING_CLASS::StrNew(path);
	if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;

	FileHandle_t pfile = VAR_IFACE_FILESYSTEM->Open(path, "r");
	if(!pfile) return false;

	char line[MAX_STR_LENGTH];
	while (!VAR_IFACE_FILESYSTEM->EndOfFile(pfile))
	{
		if(!VAR_IFACE_FILESYSTEM->ReadLine(line, sizeof(line), pfile))
			continue;

		if(!LIB_STRING_CLASS::GetParsedLine(line)) continue;
		Add(LIB_STRING_CLASS::StrTrim(line));
	}
	VAR_IFACE_FILESYSTEM->Close(pfile);
	return true;
}

bool LIB_EASYADMIN_CLASS::LoadFromKeyvalue(const char *path)
{
	adminFile = LIB_STRING_CLASS::StrNew(path);
	KeyValues *kvMain = new KeyValues("Admins"), *kvLoop;
	if(!kvMain->LoadFromFile(VAR_IFACE_FILESYSTEM, path, "MOD")) return false;
	for(kvLoop = kvMain->GetFirstValue(); kvLoop; kvLoop = kvLoop->GetNextValue())
	{
		Add(kvLoop->GetString());
	}
	kvMain->deleteThis();
	kvLoop->deleteThis();
	return true;
}

bool LIB_EASYADMIN_CLASS::LoadFromIni(const char *path)
{
	adminFile = LIB_STRING_CLASS::StrNew(path);
	if (!VAR_IFACE_FILESYSTEM->FileExists(path))
			return false;

	LIB_INI_CLASS *ini = new LIB_INI_CLASS(path, false);
	if(!ini->Load())
		return false;
	
	return true;
}

// Save admins to a text file
// When path is NULL, path from last load or save will be used
bool LIB_EASYADMIN_CLASS::SaveToFile(const char *path /*= NULL*/)
{
	if(!path && !adminFile)
		return false;
	if(!Admins.Count()) return true;
	if(path)
		adminFile = LIB_STRING_CLASS::StrNew(path);
	FileHandle_t pFile = VAR_IFACE_FILESYSTEM->Open(adminFile, "w", "MOD");
	if(!pFile) return false;
	FOR_EACH_VEC(Admins, i)
		VAR_IFACE_FILESYSTEM->FPrintf(pFile, "%s\n", Admins[i]);
	VAR_IFACE_FILESYSTEM->Close(pFile);
	return true;
}

// Save admins to a keyvalue file
// When path is NULL, path from last load or save will be used
bool LIB_EASYADMIN_CLASS::SaveToKeyvalue(const char *path /*= NULL*/, const char *kvNamespace /*= "Admins"*/)
{
	if((!path && !adminFile) || !kvNamespace)
		return false;
	if(!Admins.Count()) return true;
	if(path)
		adminFile =  LIB_STRING_CLASS::StrNew(path);
	KeyValues *kvMain = new KeyValues(kvNamespace);
	FOR_EACH_VEC(Admins, i)
	{
		kvMain->SetString(LIB_STRING_CLASS::StrFormat("Admin %i", (i+1)), Admins[i]);
	}
	kvMain->SaveToFile(VAR_IFACE_FILESYSTEM, adminFile, "MOD");
	kvMain->deleteThis();
	return true;
}

// Save admins to a ini file
// When path is NULL, path from last load or save will be used
bool LIB_EASYADMIN_CLASS::SaveToIni(const char *path /*= NULL*/)
{
	if(!path && !adminFile)
		return false;
	if(!Admins.Count()) return true;
	if(path)
		adminFile = LIB_STRING_CLASS::StrNew(path);
	LIB_INI_CLASS *ini = new LIB_INI_CLASS(adminFile, false);
	ini->New("admins");
	FOR_EACH_VEC(Admins, i)
		ini->New("admins", Admins[i], "Admin");
	ini->Save();
	ini->~LIB_INI_CLASS();
	return true;
}

// Last path where file got saved or loaded
const char *LIB_EASYADMIN_CLASS::GetFile()
{
	return adminFile;
}

// Print all admins steamids to console
void LIB_EASYADMIN_CLASS::PrintAdmins()
{
	Msg("Total Admins: %i\n", Admins.Count());
	FOR_EACH_VEC(Admins, i)
	{
		Msg("%s\n", Admins[i]);
	}
}

LIB_ADMIN_CLASS *VAR_LIB_ADMIN = NULL;
LIB_EASYADMIN_CLASS *VAR_LIB_EASYADMIN = NULL;
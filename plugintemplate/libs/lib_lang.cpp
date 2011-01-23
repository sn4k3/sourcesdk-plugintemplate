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
#include "libs/lib_lang.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
LIB_LANG_CLASS::LIB_LANG_CLASS(const char *wildCard /*= NULL*/)
{
	if(wildCard)
		filesWildCard = wildCard;
	else
		filesWildCard = "*.*";
}


LIB_LANG_CLASS::~LIB_LANG_CLASS()
{
	Reset();
}

//=================================================================================
// Functions
//=================================================================================
// Clean all translations
void LIB_LANG_CLASS::Reset()
{
	vec_translations.RemoveAll();
}

// Load multiple files, from a directory
// WilCard from constructor will be used
// If a file used instead a directory, that file will got loaded
bool LIB_LANG_CLASS::Load(const char *directory)
{
	if(!filesWildCard)
		filesWildCard = "*.*";
	if(VAR_IFACE_FILESYSTEM->FileExists(directory, "MOD"))
		return LoadSingleFile(directory);
	else if(!VAR_IFACE_FILESYSTEM->IsDirectory(directory, "MOD"))
		return false;
	FileFindHandle_t findfiles;
	unsigned int len = strlen(directory)-1;
	if (!(directory[len] == '\\' || directory[len] == '/'))
	{
		directory = LIB_STRING_CLASS::StrFormat("%s/", directory);
	}
	const char *filename = VAR_IFACE_FILESYSTEM->FindFirstEx(LIB_STRING_CLASS::StrFormat("%s%s", directory, filesWildCard), "MOD", &findfiles);
	while(filename)
	{
		if(VAR_IFACE_FILESYSTEM->IsDirectory(filename)) 
		{
			filename = VAR_IFACE_FILESYSTEM->FindNext(findfiles);
			continue;
		}
		if(LIB_STRING_CLASS::FStrEq(filename, ".") || LIB_STRING_CLASS::FStrEq(filename, ".."))
		{
			filename = VAR_IFACE_FILESYSTEM->FindNext(findfiles);
			continue;
		}
		LoadSingleFile(LIB_STRING_CLASS::StrFormat("%s%s", directory, filename));
		filename = VAR_IFACE_FILESYSTEM->FindNext(findfiles);
	}
	VAR_IFACE_FILESYSTEM->FindClose(findfiles);
	
	return true;
}

// Load a single translation file
bool LIB_LANG_CLASS::LoadSingleFile(const char *file)
{
	if(!VAR_IFACE_FILESYSTEM->FileExists(file, "MOD")) return false;
	KeyValues *kvMain = new KeyValues("languages");
	if(!kvMain->LoadFromFile(VAR_IFACE_FILESYSTEM, file))
	{
#ifdef DEBUG
		Msg("CLangLib: Can't load languages file\n%s\n", file);
#endif
		return false;
	}
	Reset();
	const char *nameSpace = kvMain->GetString("#namespace", "default");
	int index = GetIndexOrCreateLanguage(nameSpace, file);

	KeyValues *kvLoop, *kvValuesLoop;
	Languages newlang = INVALIDLANG;
	for(kvLoop = kvMain->GetFirstSubKey(); kvLoop; kvLoop = kvLoop->GetNextKey())
	{
		const char *phrase = kvLoop->GetName();
		int translationIndex = GetIndex(nameSpace, phrase);
		if(translationIndex == -1) 
		{
			LanguageDict langdict;
			langdict.szPhrase = kvLoop->GetName();
			langdict.szDA = NULL;
			langdict.szDE = NULL;
			langdict.szDEFAULT = NULL;
			langdict.szEN = NULL;
			langdict.szES = NULL;
			langdict.szFI = NULL;
			langdict.szFR = NULL;
			langdict.szIT = NULL;
			langdict.szJA = NULL;
			langdict.szKO = NULL;
			langdict.szNB = NULL;
			langdict.szNL = NULL;
			langdict.szPL = NULL;
			langdict.szPT = NULL;
			langdict.szRU = NULL;
			langdict.szSV = NULL;
			langdict.szTH = NULL;
			langdict.szZHCN = NULL;
			langdict.szZHTW = NULL;
			translationIndex = vec_translations[index].vec_phrases.AddToTail(langdict);
		}
		// Loop translated values
		for(kvValuesLoop = kvLoop->GetFirstValue(); kvValuesLoop; kvValuesLoop = kvValuesLoop->GetNextValue())
		{
			newlang = AssertLang(kvValuesLoop->GetName());
			if(newlang == INVALIDLANG) continue;
			else if(newlang == DEFAULT)
			{
				const char *defaultlang = kvValuesLoop->GetString();
				const char *newlangStr = AssertLangStr(defaultlang);
				if(!newlangStr) continue;
				SetTranslatedStr(DEFAULT, index, translationIndex, kvLoop->GetString(newlangStr, NULL));
				continue;
			}
			SetTranslatedStr(newlang, index, translationIndex, kvValuesLoop->GetString());
		}
	}
	return true;
}

// Get Index of a Translation or try to create
int LIB_LANG_CLASS::GetIndexOrCreateLanguage(const char *nameSpace, const char *fromFile /*= NULL*/)
{
	int index = GetIndex(nameSpace);
	if (index >= 0) return index;
	/*Translation translation;
	translation.szFile = fromFile;
	translation.szFrom = nameSpace;*/
	index = vec_translations.AddToTail();
	vec_translations[index].szFile = fromFile;
	vec_translations[index].szNamespace = nameSpace;
	return index;
}

// Get index of a Translation
int LIB_LANG_CLASS::GetIndex(const char *nameSpace)
{
	FOR_EACH_VEC(vec_translations, i)
		if(LIB_STRING_CLASS::FStrEq(vec_translations[i].szNamespace, nameSpace))
			return i;
	return -1;
}

// Get index of a LanguageDict
int LIB_LANG_CLASS::GetIndex(const char *nameSpace, const char *phrase)
{
	int iNameSpace = GetIndex(nameSpace);
	if(iNameSpace == -1) return -1;
	FOR_EACH_VEC(vec_translations[iNameSpace].vec_phrases, i)
		if(LIB_STRING_CLASS::FStrEq(vec_translations[iNameSpace].vec_phrases[i].szPhrase, phrase))
			return i;
	return -1;
}

// Get the default translation
const char *LIB_LANG_CLASS::GetLangStr(const char *nameSpace, const char *phrase)
{
	int iNameSpace = GetIndex(nameSpace);
	if(iNameSpace == -1) 
		return NULL;
	FOR_EACH_VEC(vec_translations[iNameSpace].vec_phrases, i)
		if(LIB_STRING_CLASS::FStrEq(vec_translations[iNameSpace].vec_phrases[i].szPhrase, phrase))
			return vec_translations[iNameSpace].vec_phrases[i].szDEFAULT;
	return NULL;
}
// Get a translation in a specific language
// If safe is true, returns the DEFAULT if the language was not translated
const char *LIB_LANG_CLASS::GetLangStr(const char *nameSpace, const char *phrase, const char *lang, bool safe /*= true*/)
{
	int iNameSpace = GetIndex(nameSpace);
	if(iNameSpace == -1) 
		return NULL;
	FOR_EACH_VEC(vec_translations[iNameSpace].vec_phrases, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_translations[iNameSpace].vec_phrases[i].szPhrase, phrase))
		{
			Languages newlang = AssertLang(lang);
			if(newlang == INVALIDLANG) return GetTranslatedStr(DEFAULT, iNameSpace, i);
			return GetTranslatedStr(newlang, iNameSpace, i, safe);
		}
	}
	return NULL;
}

// Get a translation based in the player game language
// If safe is true, returns the DEFAULT if the language was not translated
const char *LIB_LANG_CLASS::GetLangStr(edict_t *pEntity, const char *nameSpace, const char *phrase, bool safe /*= true*/)
{
	if(!pEntity || pEntity->IsFree()) return NULL;
	int index = IndexOfEdict(pEntity);
	if(!index) return NULL;

	int iNameSpace = GetIndex(nameSpace);
	if(iNameSpace == -1) 
		return NULL;
	FOR_EACH_VEC(vec_translations[iNameSpace].vec_phrases, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_translations[iNameSpace].vec_phrases[i].szPhrase, phrase))
		{
			Languages newlang = AssertLang(VAR_IFACE_ENGINE->GetClientConVarValue(index, "cl_language"));
			if(newlang == INVALIDLANG) return GetTranslatedStr(DEFAULT, iNameSpace, i);
			return GetTranslatedStr(newlang, iNameSpace, i, safe);
		}
	}
	return NULL;
}

// Assign translated phrase to the dictionary
const char *LIB_LANG_CLASS::GetTranslatedStr(Languages Lang, int iNameSpace, int iPhrase, bool safe /*= true*/)
{
	switch (Lang)
	{
	case EN:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szEN;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szEN ? vec_translations[iNameSpace].vec_phrases[iPhrase].szEN : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case ES:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szES;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szES ? vec_translations[iNameSpace].vec_phrases[iPhrase].szES : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case FR:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szFR;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szFR ? vec_translations[iNameSpace].vec_phrases[iPhrase].szFR : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case IT:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szIT;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szIT ? vec_translations[iNameSpace].vec_phrases[iPhrase].szIT : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case DE:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szDE;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szDE ? vec_translations[iNameSpace].vec_phrases[iPhrase].szDE : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case KO:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szKO;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szKO ? vec_translations[iNameSpace].vec_phrases[iPhrase].szKO : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case ZHCN:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szZHCN;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szZHCN ? vec_translations[iNameSpace].vec_phrases[iPhrase].szZHCN : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case ZHTW:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szZHTW;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szZHTW ? vec_translations[iNameSpace].vec_phrases[iPhrase].szZHTW : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case RU:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szRU;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szRU ? vec_translations[iNameSpace].vec_phrases[iPhrase].szRU : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case TH:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szTH;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szTH ? vec_translations[iNameSpace].vec_phrases[iPhrase].szTH : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case JA:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szJA;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szJA ? vec_translations[iNameSpace].vec_phrases[iPhrase].szJA : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case PT:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szPT;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szPT ? vec_translations[iNameSpace].vec_phrases[iPhrase].szPT : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case PL:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szPL;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szPL ? vec_translations[iNameSpace].vec_phrases[iPhrase].szPL : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case FI:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szFI;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szFI ? vec_translations[iNameSpace].vec_phrases[iPhrase].szFI : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case NB:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szNB;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szNB ? vec_translations[iNameSpace].vec_phrases[iPhrase].szNB : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case SV:
		if(!safe)
			return vec_translations[iNameSpace].vec_phrases[iPhrase].szSV;
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szSV ? vec_translations[iNameSpace].vec_phrases[iPhrase].szSV : vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	case DEFAULT:
		return vec_translations[iNameSpace].vec_phrases[iPhrase].szDEFAULT;
	}
	return NULL;
}

// Get a translation in a specific language
// Returns the DEFAULT if the language was not translated
const char *LIB_LANG_CLASS::GetTranslatedStr(const char *Lang, int iNameSpace, int iPhrase, bool safe /*= true*/)
{
	return GetTranslatedStr(AssertLang(Lang), iNameSpace, iPhrase, safe);
}

// Get a translation in a specific language
// Returns the DEFAULT if the language was not translated
void LIB_LANG_CLASS::SetTranslatedStr(Languages lang, int iNamespace, int iPhrase, const char *str)
{
	switch (lang)
	{
	case EN:
		vec_translations[iNamespace].vec_phrases[iPhrase].szEN = str;
		break;
	case ES:
		vec_translations[iNamespace].vec_phrases[iPhrase].szES = str;
		break;
	case FR:
		vec_translations[iNamespace].vec_phrases[iPhrase].szFR = str;
		break;
	case IT:
		vec_translations[iNamespace].vec_phrases[iPhrase].szIT = str;
		break;
	case DE:
		vec_translations[iNamespace].vec_phrases[iPhrase].szDE = str;
		break;
	case KO:
		vec_translations[iNamespace].vec_phrases[iPhrase].szKO = str;
		break;
	case ZHCN:
		vec_translations[iNamespace].vec_phrases[iPhrase].szZHCN = str;
		break;
	case ZHTW:
		vec_translations[iNamespace].vec_phrases[iPhrase].szZHTW = str;
		break;
	case RU:
		vec_translations[iNamespace].vec_phrases[iPhrase].szRU = str;
		break;
	case TH:
		vec_translations[iNamespace].vec_phrases[iPhrase].szTH = str;
		break;
	case JA:
		vec_translations[iNamespace].vec_phrases[iPhrase].szJA = str;
		break;
	case PT:
		vec_translations[iNamespace].vec_phrases[iPhrase].szPT = str;
		break;
	case PL:
		vec_translations[iNamespace].vec_phrases[iPhrase].szPL = str;
		break;
	case FI:
		vec_translations[iNamespace].vec_phrases[iPhrase].szFI = str;
		break;
	case NB:
		vec_translations[iNamespace].vec_phrases[iPhrase].szNB = str;
		break;
	case SV:
		vec_translations[iNamespace].vec_phrases[iPhrase].szSV = str;
		break;
	case DEFAULT:
		vec_translations[iNamespace].vec_phrases[iPhrase].szDEFAULT = str;
		break;
	}
}

// Assert a language
LIB_LANG_CLASS::Languages LIB_LANG_CLASS::AssertLang(const char *Lang)
{
	if(stricmp(Lang, "EN") == 0 || stricmp(Lang, "ENGLISH") == 0)
		return EN;
	if(stricmp(Lang, "ES") == 0 || stricmp(Lang, "SPANISH") == 0)
		return ES;
	if(stricmp(Lang, "FR") == 0 || stricmp(Lang, "FRENCH") == 0)
		return FR;
	if(stricmp(Lang, "IT") == 0 || stricmp(Lang, "ITALIAN") == 0)
		return IT;
	if(stricmp(Lang, "DE") == 0 || stricmp(Lang, "GERMAN") == 0)
		return DE;
	if(stricmp(Lang, "KO") == 0 || stricmp(Lang, "KOREAN") == 0)
		return KO;
	if(stricmp(Lang, "ZHCN") == 0 || stricmp(Lang, "SCHINESE") == 0)
		return ZHCN;
	if(stricmp(Lang, "ZHTW") == 0 || stricmp(Lang, "TCHINESE") == 0)
		return ZHTW;
	if(stricmp(Lang, "RU") == 0 || stricmp(Lang, "RUSSIAN") == 0)
		return RU;
	if(stricmp(Lang, "TH") == 0 || stricmp(Lang, "THAI") == 0)
		return TH;
	if(stricmp(Lang, "JA") == 0 || stricmp(Lang, "JAPANESE") == 0)
		return JA;
	if(stricmp(Lang, "PT") == 0 || stricmp(Lang, "PORTUGUESE") == 0)
		return PT;
	if(stricmp(Lang, "PL") == 0 || stricmp(Lang, "POLISH") == 0)
		return PL;
	if(stricmp(Lang, "DA") == 0 || stricmp(Lang, "DANISH") == 0)
		return DA;
	if(stricmp(Lang, "NL") == 0 || stricmp(Lang, "DUTCH") == 0)
		return NL;
	if(stricmp(Lang, "FI") == 0 || stricmp(Lang, "FINNISH") == 0)
		return FI;
	if(stricmp(Lang, "NB") == 0 || stricmp(Lang, "NORWEGIAN") == 0)
		return NB;
	if(stricmp(Lang, "SV") == 0 || stricmp(Lang, "SWEDISH") == 0)
		return SV;
	if(stricmp(Lang, "DEFAULT") == 0 || stricmp(Lang, "DEF") == 0)
		return DEFAULT;
	return INVALIDLANG;
}

// Assert a language
const char *LIB_LANG_CLASS::AssertLangStr(const char *Lang)
{
	if(stricmp(Lang, "EN") == 0 || stricmp(Lang, "ENGLISH") == 0)
		return "EN";
	if(stricmp(Lang, "ES") == 0 || stricmp(Lang, "SPANISH") == 0)
		return "ES";
	if(stricmp(Lang, "FR") == 0 || stricmp(Lang, "FRENCH") == 0)
		return "FR";
	if(stricmp(Lang, "IT") == 0 || stricmp(Lang, "ITALIAN") == 0)
		return "IT";
	if(stricmp(Lang, "DE") == 0 || stricmp(Lang, "GERMAN") == 0)
		return "DE";
	if(stricmp(Lang, "KO") == 0 || stricmp(Lang, "KOREAN") == 0)
		return "KO";
	if(stricmp(Lang, "ZHCN") == 0 || stricmp(Lang, "SCHINESE") == 0)
		return "ZHCN";
	if(stricmp(Lang, "ZHTW") == 0 || stricmp(Lang, "TCHINESE") == 0)
		return "ZHTW";
	if(stricmp(Lang, "RU") == 0 || stricmp(Lang, "RUSSIAN") == 0)
		return "RU";
	if(stricmp(Lang, "TH") == 0 || stricmp(Lang, "THAI") == 0)
		return "TH";
	if(stricmp(Lang, "JA") == 0 || stricmp(Lang, "JAPANESE") == 0)
		return "JA";
	if(stricmp(Lang, "PT") == 0 || stricmp(Lang, "PORTUGUESE") == 0)
		return "PT";
	if(stricmp(Lang, "PL") == 0 || stricmp(Lang, "POLISH") == 0)
		return "PL";
	if(stricmp(Lang, "DA") == 0 || stricmp(Lang, "DANISH") == 0)
		return "DA";
	if(stricmp(Lang, "NL") == 0 || stricmp(Lang, "DUTCH") == 0)
		return "NL";
	if(stricmp(Lang, "FI") == 0 || stricmp(Lang, "FINNISH") == 0)
		return "FI";
	if(stricmp(Lang, "NB") == 0 || stricmp(Lang, "NORWEGIAN") == 0)
		return "NB";
	if(stricmp(Lang, "SV") == 0 || stricmp(Lang, "SWEDISH") == 0)
		return "SV";
	if(stricmp(Lang, "DEFAULT") == 0 || stricmp(Lang, "DEF") == 0)
		return "DEFAULT";
	return NULL;
}

// Returns true if input language is valid
// Functions try to Assert first
bool LIB_LANG_CLASS::IsValidLang(const char *lang)
{
	return (AssertLang(lang) != INVALIDLANG);
}

// Prints all avaliable languages to console, the ones that can be used
void LIB_LANG_CLASS::PrintLanguages()
{
Msg("\n--------------Languages Avaliable----------------\n\n\
		English [EN]\n\
		Spanish [ES]\n\
		French [FR]\n\
		Italian [IT]\n\
		German [DE]\n\
		Korean [KO]\n\
		SChinese [ZHCN]\n\
		TChinese [ZHTW]\n\
		Russian [RU]\n\
		Thai [TH]\n\
		Japanese [JA]\n\
		Portuguese [PT]\n\
		Polish [PL]\n\
		Danish [DA]\n\
		Dutch [NL]\n\
		Finnish [FI]\n\
		Norwegian [NB]\n\
		Swedish [SV]\n\
\n-------------------------------------------------\n\n");
}

// Prints all stored translations to console
void LIB_LANG_CLASS::PrintTranslations()
{
	FOR_EACH_VEC(vec_translations, i)
	{
		Msg("[%s]\n\n", vec_translations[i].szNamespace);
		FOR_EACH_VEC(vec_translations[i].vec_phrases, x)
		{
			Msg("    [%s]\n    DEFAULT = ", vec_translations[i].vec_phrases[x].szPhrase, vec_translations[i].vec_phrases[x].szDEFAULT);
			if(vec_translations[i].vec_phrases[x].szEN)
				Msg("    English = %s", vec_translations[i].vec_phrases[x].szEN);
			if(vec_translations[i].vec_phrases[x].szES)
				Msg("    Spanish = %s", vec_translations[i].vec_phrases[x].szES);
			if(vec_translations[i].vec_phrases[x].szFR)
				Msg("    French = %s", vec_translations[i].vec_phrases[x].szFR);
			if(vec_translations[i].vec_phrases[x].szIT)
				Msg("    Italian = %s", vec_translations[i].vec_phrases[x].szIT);
			if(vec_translations[i].vec_phrases[x].szDE)
				Msg("    German = %s", vec_translations[i].vec_phrases[x].szDE);
			if(vec_translations[i].vec_phrases[x].szKO)
				Msg("    Korean = %s", vec_translations[i].vec_phrases[x].szKO);
			if(vec_translations[i].vec_phrases[x].szZHCN)
				Msg("    SChinese = %s", vec_translations[i].vec_phrases[x].szZHCN);
			if(vec_translations[i].vec_phrases[x].szZHTW)
				Msg("    TChinese = %s", vec_translations[i].vec_phrases[x].szZHTW);
			if(vec_translations[i].vec_phrases[x].szRU)
				Msg("    Russian = %s", vec_translations[i].vec_phrases[x].szRU);
			if(vec_translations[i].vec_phrases[x].szTH)
				Msg("    Thai = %s", vec_translations[i].vec_phrases[x].szTH);
			if(vec_translations[i].vec_phrases[x].szJA)
				Msg("    Japanese = %s", vec_translations[i].vec_phrases[x].szJA);
			if(vec_translations[i].vec_phrases[x].szPT)
				Msg("    Portuguese = %s", vec_translations[i].vec_phrases[x].szPT);
			if(vec_translations[i].vec_phrases[x].szPL)
				Msg("    Polish = %s", vec_translations[i].vec_phrases[x].szPL);
			if(vec_translations[i].vec_phrases[x].szDA)
				Msg("    Danish = %s", vec_translations[i].vec_phrases[x].szDA);
			if(vec_translations[i].vec_phrases[x].szNL)
				Msg("    Dutch = %s", vec_translations[i].vec_phrases[x].szNL);
			if(vec_translations[i].vec_phrases[x].szFI)
				Msg("    Finnish = %s", vec_translations[i].vec_phrases[x].szFI);
			if(vec_translations[i].vec_phrases[x].szNB)
				Msg("    Norwegian = %s", vec_translations[i].vec_phrases[x].szNB);
			if(vec_translations[i].vec_phrases[x].szSV)
				Msg("    Swedish = %s", vec_translations[i].vec_phrases[x].szSV);
		}
	}
}

LIB_LANG_CLASS *VAR_LIB_LANG = NULL;
#ifndef LIB_LANG_H
#define LIB_LANG_H
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
#define LIB_LANG_VERSION "1.0"
#define LIB_LANG_CLASS CLangLib

//=================================================================================
// Class
//=================================================================================
class LIB_LANG_CLASS
{
public:
	// Avaliable Languages
	enum Languages
	{
		DEFAULT = 0,
		EN,
		ES,
		FR,
		IT,
		DE,
		KO,
		ZHCN,
		ZHTW,
		RU,
		TH,
		JA,
		PT,
		PL,
		DA,
		NL,
		FI,
		NB,
		SV,
		INVALIDLANG
	};

	// Languages Dictionary
	struct LanguageDict {
		const char *szPhrase;
		const char *szEN;
		const char *szES;
		const char *szFR;
		const char *szIT;
		const char *szDE;
		const char *szKO;
		const char *szZHCN;
		const char *szZHTW;
		const char *szRU;
		const char *szTH;
		const char *szJA;
		const char *szPT;
		const char *szPL;
		const char *szDA;
		const char *szNL;
		const char *szFI;
		const char *szNB;
		const char *szSV;
		const char *szDEFAULT;

	};

	// Hold translation for a given namespace
	struct Translation
	{
		const char *szFile;
		const char *szNamespace;
		CUtlVector<LanguageDict> vec_phrases; 
	};

	// Constructor
	LIB_LANG_CLASS(const char *wildCard = NULL);

	// Destructor
	~LIB_LANG_CLASS();

	// Clean all translations
	void Reset();

	// Load multiple files, from a directory
	// WilCard from constructor will be used
	// If a file used instead a directory, that file will got loaded
	bool Load(const char *directory);

	// Load a single translation file
	bool LoadSingleFile(const char *file);

	// Get index of a Translation
	int GetIndex(const char *nameSpace);

	// Get index of a LanguageDict
	int GetIndex(const char *nameSpace, const char *phrase);

	// Get the default translation
	const char *GetLangStr(const char *nameSpace, const char *phrase);

	// Get a translation in a specific language
	// If safe is true, returns the DEFAULT if the language was not translated
	const char *GetLangStr(const char *nameSpace, const char *phrase, const char *lang, bool safe = true);

	// Get a translation based in the player game language
	// If safe is true, returns the DEFAULT if the language was not translated
	const char *GetLangStr(edict_t *pEntity, const char *nameSpace, const char *phrase, bool safe = true);

	// Assert a language
	static Languages AssertLang(const char *Lang);

	// Assert a language
	static const char *AssertLangStr(const char *Lang);

	// Returns true if input language is valid
	// Functions try to Assert first
	static bool IsValidLang(const char *lang);

	// Prints all avaliable languages to console, the ones that can be used
	static void PrintLanguages();

	// Prints all stored translations to console
	void PrintTranslations();

	// Store all translations
	// Use only to loop
	CUtlVector<Translation> vec_translations;
private:
	// Get Index of a Translation or try to create
	int GetIndexOrCreateLanguage(const char *nameSpace, const char *fromFile = NULL);

	// Get a translation in a specific language
	// If safe is true, returns the DEFAULT if the language was not translated
	const char *GetTranslatedStr(Languages Lang, int iNameSpace, int iPhrase, bool safe = true);

	// Get a translation in a specific language
	// If safe is true, returns the DEFAULT if the language was not translated
	const char *GetTranslatedStr(const char *Lang, int iNameSpace, int iPhrase, bool safe = true);

	// Assign translated phrase to the dictionary
	void SetTranslatedStr(Languages Lang, int iNameSpace, int iPhrase, const char *str);

	// Translation files wildcard
	// ie. *.phrases.txt
	const char *filesWildCard;
};

//=================================================================================
// Extern global variable
//=================================================================================
extern LIB_LANG_CLASS *VAR_LIB_LANG;

#endif
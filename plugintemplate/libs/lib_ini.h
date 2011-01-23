#ifndef LIB_INI_H
#define LIB_INI_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_INI_VERSION "1.0"
#define LIB_INI_CLASS CIniLib

#define LIB_INIKEY_CLASS IniKey
#define LIB_INIKEYVALUE_CLASS IniKeyValue

class LIB_INI_CLASS
{
public:
	/*class LIB_INIKEYVALUE_CLASS
	{
	public:
		char *name;
		char *value;
		char *comment;
	private:
		char *key;
	};

	class LIB_INIKEY_CLASS
	{
	public:
		// The collection of keyvalues for this Key 
		CUtlVector<LIB_INIKEYVALUE_CLASS> vec_keyvalues;

		// The key comment
		char *comment;
	private:
		// The key name.
		char *name;
	};
*/


	struct IniKeyValue{
		BasicStr szKeyName;
		BasicStr szKeyValue;
		BasicStr szComment;
	};

	// Constructor
	LIB_INI_CLASS();

	// Constructor
	LIB_INI_CLASS(const char *file, bool autoload = false);

	// Constructor Load from a kv
	// NOTE: Kv must have same struct than a ini file, EX:
	//	"nameSpace"
	//	{
	//		"a group"
	//		{
	//			"key"	"my value"
	//			"otherkey"	"value_me"
	//		}
	//		"other group"
	//		{
	//			"singleKey" "SIniLib_Class"
	//		}
	//	}
	LIB_INI_CLASS(KeyValues *kv);

	// Destructor.
	~LIB_INI_CLASS();

	// Reset all data.
	void Reset(bool unsetFile = true);

	// Make a class copy.
	LIB_INI_CLASS *Copy();

	// Load data from file (require new SIniLib(file)).
	bool Load();

	// Load data from file.
	bool Load(const char *file);

	// Get all sections names.
	CUtlVector<const char *>* GetSections();

	// Get all IniKeyValues under a section name.
	CUtlVector<IniKeyValue>* GetSectionKeyValues(const char *section);

	// Check if exist a key.
	bool Exists(const char *Key);

	// Check if exist a keyName.
	bool Exists(const char *Key, const char *KeyName);

	// Check if KeyNames struct is valid.
	inline bool IsValid(IniKeyValue theStruct)
	{
		return theStruct.szKeyName.str != NULL;
	}


	// Delete a key (By Name).
	// 'forKey' is the new Key for data (Require: moveData = true).
	// 'createIt' allow create UnCreated keys.
	bool Remove(const char *Key, bool movedata = false, const char *forKey = NULL, bool createIt = true);

	// Delete a Keyname from a Key.
	// 'isPartial' Allow delete all keyNames by partial name (mathkey, mathkey2) can be both deleted with 'math' OR 'key' only. (Dangerous)
	// Will return remove count (0 = no removes)
	unsigned int Remove(const char *Key, const char *KeyName, bool isPartial = false);

	// Remove all comments from keys AND/OR keynames
	// Will return removed comments count.
	unsigned int RemoveAllComments(bool fromKeys, bool fromKeynames);

	// Remove comments from Keys.
	// 'isPartial' Allow delete all comments by partial name (mathkey, mathkey2) can be both deleted with 'math' OR 'key' only. (Dangerous)
	// Will return remove count (0 = no removes)
	unsigned int RemoveComment(const char *Key, bool isPartial = false);

	// Remove comments from Keynames.
	// 'isPartial' Allow delete all comments by partial name (mathkey, mathkey2) can be both deleted with 'math' OR 'key' only. (Dangerous)
	// Will return remove count (0 = no removes)
	unsigned int RemoveComment(const char *Key, const char *KeyName, bool isPartial = false);

	// Create a new key.
	bool New(const char *Key, const char *comment = NULL);

	// Create a new keyname with a value.
	// 'createIt' allow create 'Key' if not exists.
	bool New(const char *Key, const char *keyName, const char *KeyValue, const char *comment = NULL, bool createIt = true);

	// Get total saved Keys.
	unsigned int GetCount() const;

	// Get total saved KeyNames for a Key.
	unsigned int GetCount(const char *Key);

	// Get a Key line. (Not the line in true file, count begin from First Key).
	// Util for move DOWN or UP lines.
	// -1 = Invalid.
	int GetLine(const char *Key);

	// Get a KeyName line from Key. (Not the line in true file, count begin from Key).
	// Util for move down or up lines.
	// -1 = Invalid.
	int GetLine(const char *Key, const char *KeyName);

	// Get a keyName index.
	// -1 = Invalid.
	int GetIndex(const char *Key, const char *KeyName);

	/*// Get the data struct for Keys.
	// Foreach Util.
	spt_inikeys_struct GetElement(int keyIndex);

	// Get the data struct for KeyNames.
	// Foreach Util.
	spt_ini_struct GetElement(int keyIndex, int keyNameLine);

	// Get First Key.
	// If you want keep your ini data you msut call this.
	SIniLib *GetFirst(); 

	// Get Next Key.
	SIniLib *GetNextKey();

	// Get Next KeyName.
	SIniLib *GetNextKeyName();*/

	// Get a String value from Key and KeyName.
	const char *GetValueStr(const char *Key, const char *KeyName);

	// Get a Int value from Key and KeyName.
	int GetValueInt(const char *Key, const char *KeyName);

	// Get a Float value from  Key and KeyName.
	float GetValueFloat(const char *Key, const char *KeyName);

	// Get a comment from a KeyName
	const char *GetComment(const char *Key, const char *KeyName);

	// Set a Value from Key and KeyName.
	bool SetValue(const char *Key, const char *KeyName, const char *KeyValue, const char *comment = NULL, bool createIt = true);

	// Set a comment to a KeyName.
	bool SetComment(const char *Key, const char *KeyName, const char *comment);

	// Set file Hearder.
	// Require you set a comment char in every ENTER you make (\n)
	// comments: (//) (#) (;)
	void SetHearder(const char *text, bool appendLine = true);

	// Rename a Key.
	bool Rename(const char *Key, const char *NewKey);

	// Rename a KeyName.
	bool Rename(const char *Key, const char *KeyName, const char *NewKeyName);

	// Move Key UP or DOWN.
	// matchOperator '-' OR '+' OR '<' OR '>'
	// matchOperator '-' (Move to Up)
	// matchOperator '+' (Move to Down)
	// matchOperator '<' (Move to First)
	// matchOperator '>' (Move to End)
	// Line > 0 = Move.
	// If line no exists will move to LAST or to BEGIN.
	//bool Move(const char *Key, const char matchOperator, int lines);

	// Move KeyName UP or DOWN.
	// matchOperator '-' OR '+' OR '<' OR '>'
	// matchOperator '-' (Move to Up)
	// matchOperator '+' (Move to Down)
	// matchOperator '<' (Move to First)
	// matchOperator '>' (Move to End)
	// Line > 0 = Move.
	// If line no exists will move to LAST or to BEGIN.
	bool Move(const char *Key, const char *KeyName, const char matchOperator, int lines);

	// Join two ini files
	// replaceValues = allow replace keyname values (Only if found a duplicated KeyName!)
	void Join(LIB_INI_CLASS *toJoin, bool replaceValues = false);

	// Join two ini files
	// replaceValues = allow replace keyname values (Only if found a duplicated KeyName!)
	bool Join(const char *file, bool replaceValues = false);

	// Write current data for file.
	// If 'file' == NULL will use current 'pathFile' used in constructor.
	// 'extraText' Allow print custom text on file hearder.
	// 'forceCreate' will create the file if not exists.
	bool Write(const char *file = NULL, const char *extraText = NULL, bool forceCreate = true);

	// Save current data for file. (Write Alias)
	// If 'file' == NULL will use current 'pathFile' used in constructor.
	// 'extraText' Allow print custom text on file hearder.
	// 'forceCreate' will create the file if not exists.
	bool Save(const char *file = NULL, const char *extraText = NULL, bool forceCreate = true);

	// Convert current ini file to a keyValue.
	KeyValues *Convert(const char *nameSpace = "Ini2KV");

	// Convert a keyValue to INI.
	// Intire class will be changed! (Values, groups, file, hearder, ...)
	void Convert(KeyValues *kv);

	// Set File path to Load/Save.
	void SetFilePath(const char *newFile);

	// Get current file to Save/Load.
	inline const char *GetFilePath(){return pathFile;}

	// Print file Hearder.
	void PrintHearder();

	// Print all data to console.
	// 'Key' allow only print a key group.
	void Print(const char *Key = NULL);

	// Print all keys to console.
	void PrintKeys();
private:
	// File to Save/Load.
	const char *pathFile;

	// File hearder (comments?)
	BasicStr fileHearder;

	std::map<BasicStr, CUtlVector<IniKeyValue>*>::iterator map_itn;
	std::map<BasicStr, CUtlVector<IniKeyValue>*> map_file;
};


#endif
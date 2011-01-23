#ifndef LIB_STRING_H
#define LIB_STRING_H
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
#define LIB_STRING_VERSION "1.0"
#define LIB_STRING_CLASS CStringLib

//=================================================================================
// Class
//=================================================================================
class LIB_STRING_CLASS
{
public:
	// Convert Hex to Int.
	static int H2toInt(int hexdigit0, int hexdigit1);

	// Convert Hex to Int.
	static int Hex2Int(const char *hex);

	//***************************************************************************************

	// Check if text constains an string.
	static bool StrContains(const char *string, const char *tocheck);

	// Format text.
	// Allow use like: StrFormat("Time now is: %s", current_time);
	static const char *StrFormat( const char *format, ... );

	// Get game path
	static void UTIL_GetGamePath (char *path);

	// Format text
	static size_t UTIL_Format(char *buffer, size_t maxlength, const char *fmt, ...);

	// Format text
	static size_t UTIL_FormatArgs(char *buffer, size_t maxlength, const char *fmt, va_list ap);

	// String to Color.
	// ie. "red", "blue", "green", "violet"
	static Color StrToColor(const char *strColor, bool &bFound);

	// Replace text in an string.
	static unsigned  int StrReplace(char *str, const char *from, const char *to, int maxlen);

	// Replace text in an string.
	static unsigned int UTIL_ReplaceAll(char *subject, size_t maxlength, const char *search, const char *replace, bool caseSensitive);

	// Replace text in an string.
	static char *UTIL_ReplaceEx(char *subject, size_t maxLen, const char *search, size_t searchLen, const char *replace, size_t replaceLen, bool caseSensitive);

	//***************************************************************************************

	// Split a string
	static CUtlVector<const char*>* StrSplit(const char *str, const char *delims, int maxsplits = 0);

	// Split a string
	static CUtlVector<const char*>* StrSplit(const char *str, char delim, int maxsplits = 0);

	//***************************************************************************************

	// String comparsion is (string == string2?).
	static bool FStrEq(const char *sz1, const char *sz2);

	// String comparsion is (string == string2?).
	static bool StrEq(const char *str1, const char *str2);

	// Check if exist text at Left of an string.
	static bool StrLeftEq(const char *str1, const char *str2);

	// Append text to end of string.
	static char *StrAppend(char *str1, char *str2);

	//***************************************************************************************

	// Check if char in an space.
	static bool StrIsSpace(unsigned char b);

	// Check if that string is an integer (int).
	// Numeric only.
	static bool StrIsInt(const char *string);

	// Check if that string is NULL.
	static bool StrIsNULL(const char *str);

	//***************************************************************************************
	// Tokenize an string.
	static const char *StrNextToken(char *pToken, const char *pStr, char sep);

	// Escape '\n' '\r' '\t'.
	static char *StrEscape(char *str, unsigned int len);

	// Convert String to Signature.
	// Format: 105051B96CB24622895C2418E8B488F9FF8D4C241451538944
	static int Str2Sig(const char *pOld, unsigned char *pNew);

	//***************************************************************************************

	// Convert an String to Hex String.
	static unsigned char *StrToHexStr(const char *hex);

	//***************************************************************************************

	// Remove string quotes.
	// quotes = "
	static char *StrRemoveQuotes(char *text);

	//***************************************************************************************

	// Convert an string to Vector.
	static Vector StrToVec(const char *pStr);

	// Convert an string to QAngle.
	static QAngle StrToAngle(const char *pStr);

	// String to Color.
	// ie. "255 255 255 255"
	static color32 StrToColor32(const char *strColor);

	//***************************************************************************************

	// String substr Func
	// Allow select text begin in X pos and end in Y pos.
	static char *SubStr(const char* str, int start, int end = 0);

	// Eat Spaces at Begin AND/OR at End
	// stripQuotes Allow remove Fist and End quotes (" ') and stop removing spaces
	// stripQuotes (   " quotes test"  ) will return ( quotes test)
	static char *StrTrim(char *string, bool atBegin = true, bool atEnd = true, bool stripQuotes = true);

	// Tokenize an string.
	// NOTE: Use insted 'StrNextToken'
	static char *StrToken(char *text, int tokenchar, char *tokenseparator);

	// Get string next space count starting on a position.
	static int StrGetNextSpaceCount(char *Text,int CurIndex);

	// Append X Spaces in a string.
	// If string len = 0 will create only spaces on
	// If string have any text (len > 0) will append spaces at end of string.
	static void StrAppendSpaces(char *str, int numSpaces);

	// Find a letter on a string.
	// startPos = Start find after len X.
	static int StrFindChar(char c, const char* str, unsigned int startPos = 0);

	// Make a new string
	static char *StrNew(const char *string);

	// Copy a string.
	static inline char *StrCopy(const char *str)
	{
		char* newstr = new char[strlen(str)+1];
		strcpy(newstr, str);
		return newstr;
	}

	// Copy a string.
	static unsigned int StrCopy(char *dest, const char *src, size_t count);

	// Strip Aplha in string.
	static char *StrStripAlpha(const char *str);
	
	// Get last path in string.
	// NOTE: 'path/to/an/file.txt' Last path will be 'file.txt'.
	static const char *StrGetLastPath(char *path);

	// Get last path in string.
	static const char *StrGetLastPath(char *path, char sep);

	// Convert an string to Upper case.
	static char *StrToUpper(const char* oldstr);

	// Convert an string to Lower case.
	static char *StrToLower(const char* oldstr);

	// Strip comment symbols (//,#) from string
	// Return new string
	static const char *StripCommentSymbols(const char *str);

	// Check if string is a comment (//,#)
	// Return comment postion on string, otherwise returns -1 if the string isn't a comment 
	static int IsComment(const char *str);

	// Take a string, and remove the end of line characters
	static bool StripEOL(char *in);

	//***************************************************************************************

	// Parse a file line, removing Line Breaks (\n \r)
	// Return false if line is invalid " " or not line.
	// If ignorecomments is true and line is commented (// #) returns false
	static bool GetParsedLine(char *line, bool ignorecomments = true);

	//***************************************************************************************

};

//=================================================================================
// Class BasicStr (From MANI)
//=================================================================================
class BasicStr
{
public:
	BasicStr() {str = NULL;len = 0;};
	~BasicStr() {if (str) free (str);}
	BasicStr(const char *str_ptr)
	{
		if(str_ptr == NULL)
		{
			str = NULL;len = 0;
		}
		else
		{
			len = strlen(str_ptr);
			str = (char *) malloc(len + 1);
			strcpy(str, str_ptr);
		}
	}

	BasicStr(const BasicStr &src)
	{
		if(src.str == NULL)
		{
			str = NULL;len = 0;
		}
		else
		{
			len = strlen(src.str);
			str = (char *) malloc(len + 1);
			strcpy(str, src.str);
		}
	}

	BasicStr &operator=(const BasicStr &right)
	{
		if(right.str == NULL)
		{
			Clean();
			return *this;
		}
		if (this->str) free (this->str);
		len = strlen(right.str);
		this->str = (char *) malloc(len + 1);
		strcpy(this->str, right.str);
		return *this;
	}

	BasicStr &operator=(const char *str_ptr)
	{
		if(str_ptr == NULL)
		{
			Clean();
			return *this;
		}
		if (this->str) free (this->str);
		len = strlen(str_ptr);
		this->str = (char *) malloc(len + 1);
		strcpy(this->str, str_ptr);
		return *this;
	}


	bool operator==(const BasicStr &right) const 
	{
		if(this->str == NULL && right.str == NULL)
			return true;
		return LIB_STRING_CLASS::FStrEq(this->str, right.str);
	}

	bool operator<(const BasicStr &right) const 
	{
		return (strcmp(right.str, str) < 0);
	}

	// Free and set string to NULL
	void Clean()
	{
		if (str) free (str);
		str = NULL;len = 0;
	}

	// Set value
	void	Set(const char *str_ptr)
	{
		if (str != NULL) free(str);
		len = strlen(str_ptr);
		str = (char *) malloc(len + 1);
		strcpy(str, str_ptr);
	}

	// Convert string to upper case
	void	Upper() {if (str) for (int i = 0; str[i] != '\0'; i++) str[i] = toupper(str[i]);}
	// Convert string to lower case
	void	Lower()	{if (str) for (int i = 0; str[i] != '\0'; i++) str[i] = tolower(str[i]);}

	// Concrat string
	void	Cat(const char *str_ptr)
	{
		int old_len = len;
		int	str_len = strlen(str_ptr);
		len += str_len;
		str = (char *) realloc(str, len + 1);
		for (int i = 0; i <= str_len; i++)
		{
			str[i + old_len] =  str_ptr[i];
		}
	}

	// Concrat string
	void	Cat(const BasicStr &right)
	{
		int old_len = len;
		int	str_len = right.len;
		len += str_len;
		str = (char *) realloc(str, len + 1);
		for (int i = 0; i <= str_len; i++)
		{
			str[i + old_len] =  right.str[i];
		}
	}

	// Is string NULL?
	bool IsNULL()
	{
		if (len <= 0)
			return true;
		if(str == NULL)
			return true;
		return false;
	}

	// Convert to const char *
	inline const char *ToString() const
	{
		return str;
	}

	// Return string len (strlen)
	inline int Len() const
	{
		return len;
	}

	// The string itself
	char *str;
	// The string len
	int	 len;
};


#endif
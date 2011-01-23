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
#include "libs/lib_string.h"
#include "tier0/memdbgon.h"

// **********************************
// *           HEX Utils            *
// **********************************
// Convert Hex to Int.
int LIB_STRING_CLASS::H2toInt(int hexdigit0, int hexdigit1)
{
	
   if(hexdigit1 < 58)
   {
      hexdigit1 -= 48;
   }else{
      hexdigit1 = toupper(hexdigit1);
      hexdigit1 -= 55;
   }
   hexdigit1 *=1;
   if(hexdigit0 < 58)
   {
      hexdigit0 -= 48;
   }else{
      hexdigit0 = toupper(hexdigit0);
      hexdigit0 -= 55;
   }
   hexdigit0 *= 16;
   return (hexdigit1 + hexdigit0);
}

// Convert Hex to Int.
int LIB_STRING_CLASS::Hex2Int(const char *hex)
{
	int x = 0, y = 0, z = 0;
	int digit[5] = { 0 };
	int value = 0;

	while(x < 4)
	{
		if(hex[x] == '\0') break;
		if(hex[x] > 0x29 && hex[x] < 0x40)
			digit[x] = hex[x] & 0x0f;
		else if((hex[x] >= 'a' && hex[x] <= 'f') || (hex[x] >= 'A' && hex[x] <= 'F'))
			digit[x] = (hex[x] & 0x0f) + 9;
		else
			break;

		x++;
	}

	y = x - 1;

	while(z < x)
		value = value | (digit[z++] << (y-- << 2));

	return value;
}

// **********************************
// *          String Utils          *
// **********************************

// Check if text constains an string.
bool LIB_STRING_CLASS::StrContains(const char *string, const char *tocheck)
{
	if (strstr(string, tocheck)) return true; //string does contain tocheck and do something
	return false; //string doesnt contain tocheck and do something
}

// Format text.
// Allow use like: StrFormat("Time now is: %s", current_time);
const char *LIB_STRING_CLASS::StrFormat(const char *format, ... )
{
	MULTIARGS(format);
	return string;
}

// Get game path
void LIB_STRING_CLASS::UTIL_GetGamePath ( char *path )
{
	char gamedir[256];
	char *p_path = NULL;
	filesystem->RelativePathToFullPath ("gameinfo.txt", "GAME", gamedir, 256);
	if ( gamedir[0] != 0 ) {
		char *p_slash = strrchr (gamedir, PATH_SEP_CHAR);
		if ( p_slash )
			*p_slash = 0;

		p_path = strrchr(gamedir, PATH_SEP_CHAR);

		if (p_path)
			p_path ++;
	}
	Q_strncpy(path, p_path, 256);
}

// Format text
size_t LIB_STRING_CLASS::UTIL_Format(char *buffer, size_t maxlength, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	size_t len = vsnprintf(buffer, maxlength, fmt, ap);
	va_end(ap);

	if (len >= maxlength)
	{
		buffer[maxlength - 1] = '\0';
		return (maxlength - 1);
	}
	else
	{
		return len;
	}
}

// Format text
size_t LIB_STRING_CLASS::UTIL_FormatArgs(char *buffer, size_t maxlength, const char *fmt, va_list ap)
{
	size_t len = vsnprintf(buffer, maxlength, fmt, ap);

	if (len >= maxlength)
	{
		buffer[maxlength - 1] = '\0';
		return (maxlength - 1);
	}
	else
	{
		return len;
	}
}

// String to Color.
Color LIB_STRING_CLASS::StrToColor(const char *strColor, bool &bFound)
{
	bFound = true;
	if (!Q_stricmp(strColor, "red")) {
		return Color(255, 0, 0, 255);
	} else if (!Q_stricmp(strColor, "green")) {
		return Color(0, 255, 0, 255);
	} else if (!Q_stricmp(strColor, "blue")) {
		return Color(0, 0, 255, 255);
	} else if (!Q_stricmp(strColor, "orange")) {
		return Color(255, 130, 0, 255);
	} else if (!Q_stricmp(strColor, "purple") || !Q_stricmp(strColor, "violet")) {
		return Color(144, 0, 226, 255);
	} else if (!Q_stricmp(strColor, "pink")) {
		return Color(226, 0, 165, 255);
	} else if (!Q_stricmp(strColor, "cyan")) {
		return Color(0, 255, 255, 255);
	} else if (!Q_stricmp(strColor, "yellow")) {
		return Color(255, 255, 0, 255);
	} else if (!Q_stricmp(strColor, "blue")) {
		return Color(0, 0, 255, 255);
	} else if (!Q_stricmp(strColor, "white")) {
		return Color(255, 255, 255, 255);
	} else if (!Q_stricmp(strColor, "black")) {
		return Color(0, 0, 0, 255);
	} else if (!Q_stricmp(strColor, "darkgreen")) {
		return Color(0, 145, 0, 255);
	} else if (!Q_stricmp(strColor, "darkblue")) {
		return Color(0, 0, 145, 255);
	} else if (!Q_stricmp(strColor, "darkred")) {
		return Color(145, 0, 0, 255);
	} else if (!Q_stricmp(strColor, "gray") || !Q_stricmp(strColor, "grey")) {
		return Color(120, 120, 120, 255);
	}
	bFound = false;
	return Color(255, 255, 255, 255);
}

// Replace text in an string.
unsigned int LIB_STRING_CLASS::StrReplace(char *str, const char *from, const char *to, int maxlen) // Function from sslice
{
	char  *pstr   = str;
	int   fromlen = Q_strlen(from);
	int   tolen   = Q_strlen(to);
	unsigned int	  RC=0;		// Removed count

	while (*pstr != '\0' && pstr - str < maxlen) {
		if (Q_strncmp(pstr, from, fromlen) != 0) {
			*pstr++;
			continue;
		}
		Q_memmove(pstr + tolen, pstr + fromlen, maxlen - ((pstr + tolen) - str) - 1);
		Q_memcpy(pstr, to, tolen);
		pstr += tolen;
		RC++;
	}
	return RC;
}

// Replace text in an string.
unsigned int LIB_STRING_CLASS::UTIL_ReplaceAll(char *subject, size_t maxlength, const char *search, const char *replace, bool caseSensitive)
{
	size_t searchLen = strlen(search);
	size_t replaceLen = strlen(replace);

	char *ptr = subject;
	unsigned int total = 0;
	while ((ptr = UTIL_ReplaceEx(ptr, maxlength, search, searchLen, replace, replaceLen, caseSensitive)) != NULL)
	{
		total++;
		if (*ptr == '\0')
		{
			break;
		}
	}

	return total;
}

/**
 * NOTE: Do not edit this for the love of god unless you have 
 * read the test cases and understand the code behind each one.
 * While I don't guarantee there aren't mistakes, I do guarantee
 * that plugins will end up relying on tiny idiosyncrasies of this
 * function, just like they did with AMX Mod X.
 *
 * There are explicitly more cases than the AMX Mod X version because
 * we're not doing a blind copy.  Each case is specifically optimized
 * for what needs to be done.  Even better, we don't have to error on
 * bad buffer sizes.  Instead, this function will smartly cut off the 
 * string in a way that pushes old data out.
 */
char *LIB_STRING_CLASS::UTIL_ReplaceEx(char *subject, size_t maxLen, const char *search, size_t searchLen, const char *replace, size_t replaceLen, bool caseSensitive)
{
	char *ptr = subject;
	size_t browsed = 0;
	size_t textLen = strlen(subject);

	/* It's not possible to search or replace */
	if (searchLen > textLen)
	{
		return NULL;
	}

	/* Handle the case of one byte replacement.
	 * It's only valid in one case.
	 */
	if (maxLen == 1)
	{
		/* If the search matches and the replace length is 0, 
		 * we can just terminate the string and be done.
		 */
		if ((caseSensitive ? strcmp(subject, search) : strcasecmp(subject, search)) == 0 && replaceLen == 0)
		{
			*subject = '\0';
			return subject; 		}
		else
		{
			return NULL;
		}
	}

	/* Subtract one off the maxlength so we can include the null terminator */
	maxLen--;

	while (*ptr != '\0' && (browsed <= textLen - searchLen))
	{
		/* See if we get a comparison */
		if ((caseSensitive ? strncmp(ptr, search, searchLen) : strncasecmp(ptr, search, searchLen)) == 0)
		{
			if (replaceLen > searchLen)
			{
				/* First, see if we have enough space to do this operation */
				if (maxLen - textLen < replaceLen - searchLen)
				{
					/* First, see if the replacement length goes out of bounds. */
					if (browsed + replaceLen >= maxLen)
					{
						/* EXAMPLE CASE:
						 * Subject: AABBBCCC
						 * Buffer : 12 bytes
						 * Search : BBB
						 * Replace: DDDDDDDDDD
						 * OUTPUT : AADDDDDDDDD
						 * POSITION:           ^
						 */
						/* If it does, we'll just bound the length and do a strcpy. */
						replaceLen = maxLen - browsed;
						/* Note, we add one to the final result for the null terminator */
						StrCopy(ptr, replace, replaceLen+1);
					}
					else
					{
						/* EXAMPLE CASE:
						 * Subject: AABBBCCC
						 * Buffer : 12 bytes
						 * Search : BBB
						 * Replace: DDDDDDD
						 * OUTPUT : AADDDDDDDCC
						 * POSITION:         ^
						 */
						/* We're going to have some bytes left over... */
						size_t origBytesToCopy = (textLen - (browsed + searchLen)) + 1;
						size_t realBytesToCopy = (maxLen - (browsed + replaceLen)) + 1;
						char *moveFrom = ptr + searchLen + (origBytesToCopy - realBytesToCopy);
						char *moveTo = ptr + replaceLen;

						/* First, move our old data out of the way. */
						memmove(moveTo, moveFrom, realBytesToCopy);

						/* Now, do our replacement. */
						memcpy(ptr, replace, replaceLen);
					}
				}
				else
				{
					/* EXAMPLE CASE:
					 * Subject: AABBBCCC
					 * Buffer : 12 bytes
					 * Search : BBB
					 * Replace: DDDD
					 * OUTPUT : AADDDDCCC
					 * POSITION:      ^
					 */
					/* Yes, we have enough space.  Do a normal move operation. */
					char *moveFrom = ptr + searchLen;
					char *moveTo = ptr + replaceLen;

					/* First move our old data out of the way. */
					size_t bytesToCopy = (textLen - (browsed + searchLen)) + 1;
					memmove(moveTo, moveFrom, bytesToCopy);

					/* Now do our replacement. */
					memcpy(ptr, replace, replaceLen);
				}
			}
			else if (replaceLen < searchLen)
			{
				/* EXAMPLE CASE:
				 * Subject: AABBBCCC
				 * Buffer : 12 bytes
				 * Search : BBB
				 * Replace: D
				 * OUTPUT : AADCCC
				 * POSITION:   ^
				 */
				/* If the replacement does not grow the string length, we do not
				 * need to do any fancy checking at all.  Yay!
				 */
				char *moveFrom = ptr + searchLen;		/* Start after the search pointer */
				char *moveTo = ptr + replaceLen;		/* Copy to where the replacement ends */

				/* Copy our replacement in, if any */
				if (replaceLen)
				{
					memcpy(ptr, replace, replaceLen);
				}

				/* Figure out how many bytes to move down, including null terminator */
				size_t bytesToCopy = (textLen - (browsed + searchLen)) + 1;

				/* Move the rest of the string down */
				memmove(moveTo, moveFrom, bytesToCopy);
			}
			else
			{
				/* EXAMPLE CASE:
				 * Subject: AABBBCCC
				 * Buffer : 12 bytes
				 * Search : BBB
				 * Replace: DDD
				 * OUTPUT : AADDDCCC
				 * POSITION:     ^
				 */
				/* We don't have to move anything around, just do a straight copy */
				memcpy(ptr, replace, replaceLen);
			}

			return ptr + replaceLen;
		}
		ptr++;
		browsed++;
	}

	return NULL;
}


// Split a string
CUtlVector<const char*>* LIB_STRING_CLASS::StrSplit(const char *str, const char *delims, int maxsplits /*= 0*/)
{	
	char* tmp;
	CUtlVector<const char*>* ret = new CUtlVector<const char*>;
	unsigned int i = 0;
	int splits = 0;
	unsigned int len = strlen(str);
	while (i < len)
	{
		//ignore leading whitespace
		while (i < len && (StrFindChar(str[i], delims) != -1) || str[i] == '\r' || str[i] == '\n')
				++i;

		//find the end of the next word
		unsigned int j = i;
		while (j < len && (StrFindChar(str[j], delims) == -1) && str[j] != '\r' && str[j] != '\n')
				++j;

		if (i != j)
		{
			splits++;
			tmp = SubStr(str, i, j);
			ret->AddToTail(tmp);
			i = j;
			if(maxsplits > 0)
			{
				if(maxsplits == splits)
				{
					j++;
					if(j < len && str[j] != '\r' && str[j] != '\n')
					{
						tmp = SubStr(str, i+1, len);
						ret->AddToTail(tmp);
					}
					break;
				}
			}
		}
	}
	return ret;
}

// Split a string
CUtlVector<const char*>* LIB_STRING_CLASS::StrSplit(const char *str, char delim, int maxsplits /*= 0*/)
{
	char* tmp;
	CUtlVector<const char*>* ret = new CUtlVector<const char*>;
	unsigned int i = 0;
	int splits = 0;
	unsigned int len = strlen(str);
	while (i < len)
	{
		//ignore leading whitespace
		while (i < len && str[i] == delim || str[i] == '\r' || str[i] == '\n')
			++i;

		//find the end of the next word
		unsigned int j = i;
		while (j < len && str[j] != delim && str[j] != '\r' && str[j] != '\n')
			++j;

		if (i != j)
		{
			splits++;
			tmp = SubStr(str, i, j);
			ret->AddToTail(tmp);
			i = j;
			if(maxsplits > 0)
			{
				if(maxsplits == splits)
				{
					j++;
					if(j < len && str[j] != '\r' && str[j] != '\n')
					{
						tmp = SubStr(str, i+1, len);
						ret->AddToTail(tmp);
					}
					break;
				}
			}
		}
	}
	return ret;
}

// String comparsion is (string == string2?).
bool LIB_STRING_CLASS::FStrEq(const char *sz1, const char *sz2)
{
	return ( sz1 == sz2 || stricmp(sz1, sz2) == 0 );
}

// String comparsion is (string == string2?).
bool LIB_STRING_CLASS::StrEq(const char *str1, const char *str2)
{
	if(str1 && str2) return(Q_stricmp(str1, str2) == 0);
	return false;
}

// Check if exist text at Left of an string.
bool LIB_STRING_CLASS::StrLeftEq(const char *str1, const char *str2)
{
	if(str1 && str2)
		if(!strnicmp(str1, str2, strlen(str2)))
			return true;
	return false;
}

// Append text to end of string.
/*char *LIB_ENTITY_CLASS::StrAppend(char *str1, char c)
{    
     char * ret = (char*)malloc(sizeof(str1) + 1 + 1);
       strcpy(ret,str1);
         ret[strlen(ret)] = c;
         ret[sizeof(ret)] = '\0';
     return ret;     
}*/

// Append text to end of string.
char *LIB_STRING_CLASS::StrAppend(char *str1, char *str2)
{     
    strcpy(str1,str2);
	return str1;     
}

// Check if char in an space.
bool LIB_STRING_CLASS::StrIsSpace(unsigned char b)
{
	//return isspace(b);
	switch (b)
	{
	case ' ':
		return true;
	case '\n':
		return true;
	case '\r':
		return true;
	case '\0':
		return true;
	}
	return false;
}

// Check if that string is an integer (int).
// Numeric only.
bool LIB_STRING_CLASS::StrIsInt(const char *string)
{
	for(unsigned int i = 0; i < strlen(string); i++) {
		/*if (!(string[i] == '0' || string[i] == '1' || string[i] == '2' || string[i] == '3' || string[i] == '4' ||
			string[i] == '5' || string[i] == '6' || string[i] == '7' || string[i] == '8' || string[i] == '9'))
			return false;*/
		if(!isdigit(string[i])) return false;
	}
	return true;
}

// Check if that string is NULL.
bool LIB_STRING_CLASS::StrIsNULL(const char *str)
{
	if(!str) return true;
	unsigned int len = strlen(str);
	if(len <= 0)
		return true;
	if(str[0] == '0' || str[0] == '\0')
		return true;

	return false;
}

// Tokenize an string.
const char *LIB_STRING_CLASS::StrNextToken(char *pToken, const char *pStr, char sep)
{
	int i = 0;

	if(!pStr || *pStr == '\0')
	{
		*pToken = '\0';
		return pStr;
	}

	while(*pStr != sep && *pStr != '\0')
	{
		if(++i < 1024) *pToken++ = *pStr;
		*pStr++;
	}

	*pToken = '\0';

	return (*pStr == '\0') ? pStr : ++pStr;
}

// Escape '\n' '\r' '\t'.
char *LIB_STRING_CLASS::StrEscape(char *str, unsigned int len)
{
	if(!str) return NULL;
	/*for(int i = 0; i < strlen(str); i++)
	{
		if(str[i+1] == '\n')
			str[i] = '\n';
		else if(str[i+1] == '\t')
			str[i] = '\t';
		else if(str[i+1] == '\r')
			str[i] = '\r';
	}*/
	/*unsigned int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
		{
			switch (str[i + 1])
			{
			case 'n':
				{
					str[i] = NULL;
					break;
				}
			case 't':
				{
					str[i] = NULL;
					break;
				}
			case 'r':
				{
					str[i] = NULL;
					break;
				}
			}
		}
		i++;
	}
	return str;*/
	//if(StrContains(str, "\\n"))
		StrReplace(str, "\\n", "\n", len);
	//if(StrContains(str, "\\r"))
		StrReplace(str, "\\r", "\r", len);
	//if(StrContains(str, "\\t"))
		StrReplace(str, "\\t", "\t", len);
	return str;
}

// Convert String to Signature.
// Format: 105051B96CB24622895C2418E8B488F9FF8D4C241451538944
int LIB_STRING_CLASS::Str2Sig(const char *pOld, unsigned char *pNew)
{
	int iPos = 0, iLength = 0;
	char szToken[1024];

	while(pOld && *pOld != '\0' && iPos <= 1024)
	{
		pOld = StrNextToken(szToken, pOld, ' ');
		pNew[iPos++] = (unsigned char)strtol(szToken, NULL, 16);
		iLength++;
	}

	pNew[iPos] = '\0';

	return iLength;
}

// Convert an String to Hex String.
unsigned char *LIB_STRING_CLASS::StrToHexStr(const char *hex)
{
   unsigned char *str = new unsigned char[strlen(hex)/2+1];
   int decimal = 0;
   int writeto = 0;
   for(unsigned int i = 0;i<strlen(hex);i+=2)
   {
      decimal = H2toInt(hex[i], hex[i+1]);
      str[writeto] = (unsigned char)decimal;
      writeto++;
   }
   str[writeto] = '\0';
   return str;
}

// Remove string quotes.
// quotes = "
char *LIB_STRING_CLASS::StrRemoveQuotes(char *text)
{
	int len = strlen(text);

	for(int i=0;i<len;i++)
	{
		if(text[i] == '\"')
			text[i] = NULL;
	}
	return text;
}

// Convert an string to Vector.
Vector LIB_STRING_CLASS::StrToVec(const char *pStr)
{
	Vector vecPos;
	char szToken[MAX_STR_LENGTH];

	pStr = StrNextToken(szToken, pStr, ' ');
	vecPos.x = atof(szToken);

	pStr = StrNextToken(szToken, pStr, ' ');
	vecPos.y = atof(szToken);

	pStr = StrNextToken(szToken, pStr, ' ');
	vecPos.z = atof(szToken);

	return vecPos;
}

// Convert an string to QAngle.
QAngle LIB_STRING_CLASS::StrToAngle(const char *pStr)
{
	QAngle anglePos;
	char szToken[MAX_STR_LENGTH];

	pStr = StrNextToken(szToken, pStr, ' ');
	anglePos.x = atof(szToken);

	pStr = StrNextToken(szToken, pStr, ' ');
	anglePos.y = atof(szToken);

	pStr = StrNextToken(szToken, pStr, ' ');
	anglePos.z = atof(szToken);

	return anglePos;
}

// String to Color.
// ie. "255 255 255 255"
color32 LIB_STRING_CLASS::StrToColor32(const char *strColor)
{
	color32 color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	char szToken[MAX_STR_LENGTH];

	strColor = StrNextToken(szToken, strColor, ' ');
	color.r = atoi(szToken);

	strColor = StrNextToken(szToken, strColor, ' ');
	color.g = atoi(szToken);

	strColor = StrNextToken(szToken, strColor, ' ');
	color.b = atoi(szToken);

	strColor = StrNextToken(szToken, strColor, ' ');
	color.a = atoi(szToken);

	return color;
}

// String substr Func
// Allow select text begin in X pos and end in Y pos.
char *LIB_STRING_CLASS::SubStr(const char* str, int start, int end /*= 0*/)
{
	if(end <= 0)
		end = strlen(str);
	int len = (end - start);
	if (len < 0)
		len = 0;
	char* ret = new char[len+1];
	for (int i = start; i < end; ++i)
		ret[i-start] = str[i];
	ret[len] = '\0';
	return ret;	
}

// Eat Spaces at Begin AND/OR at End
// stripQuotes Allow remove Fist and End quotes (" ') and stop removing spaces
// stripQuotes (   " quotes test"  ) will return ( quotes test)
char *LIB_STRING_CLASS::StrTrim(char *string, bool atBegin /*= true*/, bool atEnd /*= true*/, bool stripQuotes /*= true*/)
{
	if((!atBegin && !atEnd) || !string) return string;
	int len = strlen(string);
	if(!len) return string;
	int y = 0, z = len-1;
	if(atBegin)
	{
		while(isspace(string[y]))
		{
			y++;
			if(stripQuotes)
			{
				if(string[y] == '\"' || string[y] == '\'')
				{
					y++;
					break;
				}
			}
		}
	}
	if(atEnd)
	{
		while(isspace(string[z]))
		{
			if(stripQuotes)
			{
				if(string[z] == '\"')
				{
					z--;
					string[z] = '\0';
					break;
				}
			}
			string[z] = '\0';
			z--;
		}
	}
	if(y == 0 && z == (len-1)) return string;
	return SubStr(string, y, strlen(string));
}

// Tokenize an string.
// NOTE: Use insted 'StrNextToken'
char *LIB_STRING_CLASS::StrToken(char *text, int tokenchar, char *tokenseparator)
{
	char *pch;
	pch = strtok(text,tokenseparator);
	for (int i = 0; i <= tokenchar; i++)
	{
		pch = strtok(NULL,tokenseparator);
	}
	return pch;
}

// Get string next space count starting on a position.
int LIB_STRING_CLASS::StrGetNextSpaceCount(char *Text,int CurIndex)
{
	int Count=0;
	int len = strlen(Text);
	for(int i=CurIndex;i<len;i++)
	{
		if(Text[i] == ' ')
			return Count;
		else
			Count++;
	}

	return Count;
}

// Append X Spaces in a string.
// If string len = 0 will create only spaces on
// If string have any text (len > 0) will append spaces at end of string.
void LIB_STRING_CLASS::StrAppendSpaces(char *str, int numSpaces)
{
	if (numSpaces < 1)
		return;

	char* spaces = new char[numSpaces+1];
	int i;
	for (i = 0; i < numSpaces; ++i)
		spaces[i] = ' ';
	spaces[i] = '\0';
	if (strlen(str))
		strcat(str, spaces);
	else
		strcpy(str, spaces);
	delete spaces;
}

// Find a letter on a string.
// startPos = Start find after len X.
int LIB_STRING_CLASS::StrFindChar(char c, const char* str, unsigned int startPos /*= 0*/)
{
	while (startPos < strlen(str) && str[startPos] != c)
		++startPos;
		
	if (startPos < strlen(str) && str[startPos] == c)
		return startPos;
	else
		return -1;
}

// Make a new string
char *LIB_STRING_CLASS::StrNew(const char *string)
{
	char *nstr = new char[(strlen(string) + 1)];
	if (nstr)
		strcpy(nstr, string);
	return nstr;
}

unsigned int LIB_STRING_CLASS::StrCopy(char *dest, const char *src, size_t count)
{
	if (!count)
	{
		return 0;
	}

	char *start = dest;
	while ((*src) && (--count))
	{
		*dest++ = *src++;
	}
	*dest = '\0';

	return (dest - start);
}


// Strip Aplha in string.
char *LIB_STRING_CLASS::StrStripAlpha(const char *str)
{
	char* newstr = new char[strlen(str)+1];
	strcpy(newstr, "");
	
	for (unsigned int i = 0; i < strlen(str); ++i)
	{
		if (!isalpha(str[i]))
			strcat(newstr, (const char*)str[i]);
	}
	return newstr;
}

// Get last path in string.
// NOTE: 'path/to/an/file.txt' Last path will be 'file.txt'.
const char *LIB_STRING_CLASS::StrGetLastPath(char *path)
{
	size_t length = strlen(path);
	for (size_t i = length - 1;
		 i >= 0 && i <= length - 1;
		 i--)
	{
		if (path[i] == '/'
#if defined WIN32
			|| path[i] == '\\'
#endif

			)
		{
			return &path[i+1];
		}
	}

	return path;
}

// Get last path in string.
const char *LIB_STRING_CLASS::StrGetLastPath(char *path, char sep)
{
	size_t length = strlen(path);
	for (size_t i = length - 1;
		 i >= 0 && i <= length - 1;
		 i--)
	{
		if (path[i] == sep)
			return &path[i+1];
	}

	return path;
}

//Convert string to upper case
char *LIB_STRING_CLASS::StrToUpper(const char* oldstr)
{
	char* newstr = new char[strlen(oldstr)+1];
	unsigned int i;
	for (i = 0; i < strlen(oldstr); ++i)
		newstr[i] = toupper(oldstr[i]);
	newstr[i] = '\0';
	return newstr;
}

// Convert string to lower case
char *LIB_STRING_CLASS::StrToLower(const char* oldstr)
{
	size_t len = strlen(oldstr);
	char *buffer = new char[len + 1];
	for (size_t i = 0; i < len; i++)
	{
		if (oldstr[i] >= 'A' && oldstr[i] <= 'Z')
			buffer[i] = tolower(oldstr[i]);
		else
			buffer[i] = oldstr[i];
	}
	buffer[len] = '\0';
	return buffer;
}

// Strip comment symbols (//,#) from string
// Return new string
const char *LIB_STRING_CLASS::StripCommentSymbols(const char *str)
{
	int index = IsComment(str);
	if(index == -1) 
		return str;
	if(str[index] == '/')
		index++;
	return SubStr(str, index, strlen(str));
}

// Check if string is a comment (//,#)
// Return comment postion on string, otherwise returns -1 if the string isn't a comment 
int LIB_STRING_CLASS::IsComment(const char *str)
{
	unsigned int len = strlen(str);
	if(len < 1)
		return -1;
	for(unsigned int i = 0; i < len; i++)
	{
		if(str[i] == ' ')
			continue;
		if(str[i] == '#')
			return i;
		if(i+1 == len)
			return -1;
		if(str[i] == '/' && str[i+1] == '/')
			return i;
		return -1;
	}
	return -1;
}

// Take a string, and remove the end of line characters
bool LIB_STRING_CLASS::StripEOL(char *in)
{
	int length;
	for ( length = strlen(in)-1; length >= 0; length-- ) {
		if (( in[length] == '\r' ) || ( in[length] == '\n' ) || ( in[length] == '\f' ) ||
			( in[length] == ' ' ) || ( in[length] == '\t') ) {
			in[length] = '\0';
		} else
			break;
	}
	length++;
	return ( length != 0 );
}

// Parse a file line, removing Line Breaks (\n \r) and comments (// #).
// Return NULL if line is invalid " " or not line.
bool LIB_STRING_CLASS::GetParsedLine(char *line, bool ignorecomments /*= true*/)
{
	if (!line || line[0] == '\n' || line[0] == '\r')
		return false;
	if(ignorecomments)
		if(IsComment(line) >= 0)
			return false;

	return StripEOL(line);
	/*for(unsigned int i = 0; i < strlen(line); i++)
	{
		if(line[i] == '\r' || line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
	}*/
	return true;
}
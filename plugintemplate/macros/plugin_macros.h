#ifndef PLUGIN_MACROS_H
#define PLUGIN_MACROS_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define PLUGINTEMPLATE_VERSION "1.0"

#define FOR_EACH_CHAR( str, iteratorName) \
	for(unsigned int iteratorName = 0; i < strlen(str); iteratorName++)

#define FOR_EACH_CHAR2( str, iteratorName) \
	for (unsigned int iteratorName = 0; str[i] != '\0'; iteratorName++)


#define WARN_IF(expression, code) \
	if(expression) { \
		Msg("Warning (%s:%d): \n" #expression, __FILE__, __LINE__); \
		code; \
	}

// Assign plugin interface
#define ASSIGN_INTERFACE(VAR, TYPE, FACTORY, NAME) \
	VAR = (TYPE)CPluginGlobals::InterfaceSearch(FACTORY, NAME); \
	if(VAR == NULL) \
		Warning("Unable to find an interface for "#VAR", ignoring\n");

// Assign plugin interface, die if fail to load an interface
#define ASSIGN_INTERFACE_OR_DIE(VAR, TYPE, FACTORY, NAME) \
	VAR = (TYPE)CPluginGlobals::InterfaceSearch(FACTORY, NAME); \
	if(VAR == NULL) { \
		Warning("Failed to load an interface for "#VAR"\n"); \
		return false; \
	}

#define MAX_STR_LEN 1024
#define MAX_STR_LENGTH MAX_STR_LEN
#define MAX_STRING_LEN MAX_STR_LEN
#define MAX_STRING_LENGTH MAX_STR_LEN
#define MAX_MENU_LEN 240
#define MULTIARGS(p) \
	va_list		argptr; \
	static char		string[MAX_STR_LENGTH]; \
	va_start (argptr, p); \
	Q_vsnprintf(string, sizeof(string), p,argptr); \
	va_end (argptr);

#define MULTIARGS2(p, s) \
	va_list		argptr; \
	static char		string[MAX_STR_LENGTH]; \
	va_start (argptr, s); \
	Q_vsnprintf(string, sizeof(string), p,argptr); \
	va_end (argptr);


#ifndef GetClassName
#define GetClassName GetClassNameA
#endif

class CPlugin_EmptyClass {}; // Just an empty class




#endif
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
#include "includes/precommun.h"
#include "serverplugin/serverplugin_enginepython.h"

SERVERPLUGIN_ENGINEPYTHON_CLASS::SERVERPLUGIN_ENGINEPYTHON_CLASS(){}
SERVERPLUGIN_ENGINEPYTHON_CLASS::~SERVERPLUGIN_ENGINEPYTHON_CLASS(){}

bool isPythonEnabled = false;

#ifdef PYTHON
//=================================================================================
// Global variables
//=================================================================================
extern char szGameDir[MAX_STR_LEN];
PyMethodDef VAR_PYTHON_METHODS[PYTHON_METHOD_TABLE_SIZE]; // Holds all of our python methods.

//=================================================================================
// Initializes python for us
//=================================================================================
bool EnablePython()
{
#ifdef _WIN32
	char szPythonDLL[MAX_STR_LEN];
	char szMSVCRTDLL[MAX_STR_LEN];

	// Path to python25.dll and msvcrt.dll
	V_snprintf(szMSVCRTDLL, MAX_STR_LEN, "%s\\addons\\eventscripts\\_engines\\python\\Lib\\plat-win\\msvcr71.dll", szGameDir);
	V_snprintf(szPythonDLL, MAX_STR_LEN, "%s\\addons\\eventscripts\\_engines\\python\\Lib\\plat-win\\python25.dll", szGameDir);

	// Load both modules.
	if(!LoadLibrary(szMSVCRTDLL) || !LoadLibrary(szPythonDLL))
	{
		Msg("[ERROR] Could not load one or more required dependencies to initialize python!\n");
		return false;
	}
#else
	if( !dlopen("libpython2.5.so.1.0", RTLD_NOW | RTLD_GLOBAL ) )
	{
		Error("[ERROR] Unable to open libpython2.5.so.1.0!\n");
		return false;
	}
#endif

	// Initialize python
	Py_Initialize();

	// Setup the module
	Py_InitModule(PYTHON_MODULE_NAME, VAR_PYTHON_METHODS);

	return true;
}

// Test
/*DECLARE_PYCMD(Msg, "Print text to console")
{
	char		*szText;

	if( !PyArg_ParseTuple(args, "s", &szText) )
	{
		Msg("Could not parse function arguments.\n");
		return Py_BuildValue("i", 0);
	}

	Msg(szText);

	return Py_BuildValue("i", 1);
}*/

#endif
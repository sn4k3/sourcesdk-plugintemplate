#ifndef PLUGIN_PYTHON_H
#define PLUGIN_PYTHON_H
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
#define PLUGIN_PYTHON_VERSION "1.0"
#define PLUGIN_PYTHON_CLASS CPluginPython

//=================================================================================
// Class
//=================================================================================
class PLUGIN_PYTHON_CLASS : public SERVERPLUGIN_ENGINEPYTHON_CLASS
{
public:
	PLUGIN_PYTHON_CLASS();
	~PLUGIN_PYTHON_CLASS();

	// Override
	// Called when python try to load
	// ok = true if all loads correctly, otherwise false
	void OnPythonLoad(bool ok);
};

//=================================================================================
// Extern global variable, never touch
//=================================================================================
extern PLUGIN_PYTHON_CLASS *VAR_PLUGIN_PYTHON;

#endif
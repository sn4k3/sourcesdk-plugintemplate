#ifndef PYTHON_CONFIG_H
#define PYTHON_CONFIG_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

/*
*	Windows only:
*	If you enable PYTHON, dont forget to link 'python25.lib'
*	Under Solution Explorer -> Link Libraries -> python25.lib 
*		-> Properties -> Configuration -> All Configurations -> Geral -> Exclude from build -> No -> OK
*/

//#define PYTHON									// Comment to disable python (Eventscripts required)
#define PYTHON_DIE_ON_FAIL			true		// Prevent plugin from load if python fails to load
#define PYTHON_MODULE_NAME			"pt_C"		// Define your python module name. ie. import pt_C
#define PYTHON_METHOD_TABLE_SIZE	100			// Methods struct array size
#define PYTHON_FUNCTION_PREFIX		pt_			// Prefix for every python function

#define VAR_PYTHON_METHODS g_PYMethods			// Methods struct variable

#define vpMethods VAR_PYTHON_METHODS


#endif
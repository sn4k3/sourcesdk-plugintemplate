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
//#include "includes/default.h"
#include "lib_globals.h"
#include "tier0/memdbgon.h"

LIB_GLOBALS_CLASS::LIB_GLOBALS_CLASS()
{
	Invalidate();
}

LIB_GLOBALS_CLASS::~LIB_GLOBALS_CLASS()
{
	Invalidate();
}

void LIB_GLOBALS_CLASS::Invalidate()
{
	szGameFolder	=	NULL; 
	szGameName		=	NULL;
	szCurrentMap	=	NULL;
	szOldMap		=	NULL;
	bPluginLoaded	=	false;
	iLevelChanges	=	0;
	iMaxclients		=	0;
}
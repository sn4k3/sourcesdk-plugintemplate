#ifndef INCLUDES_PRECOMMUN_H
#define INCLUDES_PRECOMMUN_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#ifdef WIN32
#pragma warning( disable : 4267 ) // warning C4267: 'argument' : conversion from 'size_t' to 'DWORD', possible loss of data
#endif

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <cstdio>
//#include <iostream>
#include <utility>
#include "time.h"

#include "includes/configs.h"
#include "plugin_macros.h"

#include "others/oslink.h"

#include "serverplugin/engine_wrappers.h"
#include "libs/lib_memory.h"

#ifndef PLUGIN_SOURCEMM
#ifdef PLUGIN_USE_SOURCEHOOK
#include <sourcehook/sourcehook_impl.h>
#include "sourcehook.h"
#endif
#endif

#include "serverplugin/serverplugin_enginepython.h"
#ifdef PYTHON
#include "Python.h"
#endif

#endif
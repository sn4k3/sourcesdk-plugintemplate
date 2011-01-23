#ifndef PLUGIN_HACK_H
#define PLUGIN_HACK_H
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
#define PLUGIN_PROP_VERSION "1.0"
#define PLUGIN_PROP_CLASS CPluginProp
#define PLUGIN_VFUNCS_VERSION "1.0"
#define PLUGIN_VFUNCS_CLASS CPluginVFuncs
#define PLUGIN_SIGSCAN_VERSION "1.0"
#define PLUGIN_SIGSCAN_CLASS CPluginSigScan

//=================================================================================
// Props Class
//=================================================================================
class PLUGIN_PROP_CLASS : public LIB_PROP_CLASS
{
public:
	PLUGIN_PROP_CLASS();
	~PLUGIN_PROP_CLASS();
};

//=================================================================================
// VFuncs Class
//=================================================================================
class PLUGIN_VFUNCS_CLASS : public LIB_VFUNCS_CLASS
{
public:
	PLUGIN_VFUNCS_CLASS();
	~PLUGIN_VFUNCS_CLASS();
};

//=================================================================================
// SigSacn Class
//=================================================================================
class PLUGIN_SIGSCAN_CLASS : public LIB_SIGSCAN_CLASS
{
public:
	PLUGIN_SIGSCAN_CLASS();
	~PLUGIN_SIGSCAN_CLASS();
};


#endif
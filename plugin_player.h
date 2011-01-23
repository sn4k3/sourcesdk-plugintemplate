#ifndef PLUGIN_PLAYER_H
#define PLUGIN_PLAYER_H
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
#define PLUGIN_PLAYER_VERSION "1.0"
#define PLUGIN_PLAYER_CLASS CPluginPlayer

//=================================================================================
// Class
//=================================================================================
class PLUGIN_PLAYER_CLASS : public LIB_PLAYER_CLASS
{
public:
	PLUGIN_PLAYER_CLASS();
	~PLUGIN_PLAYER_CLASS();
};

#endif
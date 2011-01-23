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
#include "includes/default.h"

//=================================================================================
// Assign Libraries
//=================================================================================
void LIB_LIBRARIES_CLASS::Assign()
{
	VAR_PLUGIN_GLOBALS = new PLUGIN_GLOBALS_CLASS();

#ifdef USE_LIB_DOWNLOAD
	VAR_LIB_DOWNLOAD = new LIB_DOWNLOAD_CLASS();
#endif
#ifdef USE_LIB_SOUND
	VAR_LIB_SOUND = new LIB_SOUND_CLASS();
#endif
#ifdef USE_LIB_PLAYERMNGR
	VAR_LIB_PLAYERMNGR = new LIB_PLAYERMNGR_CLASS();
#endif
#ifdef USE_LIB_TIMER
	VAR_LIB_TIMER = new LIB_TIMER_CLASS();
#endif
#ifdef USE_LIB_PROFILING
	VAR_LIB_PROFILING = new LIB_PROFILING_CLASS();
#endif
#ifdef USE_LIB_ADMIN
	VAR_LIB_ADMIN = new LIB_ADMIN_CLASS();
	#ifdef SETTING_LIB_ADMIN_CLIENTS_FILE
	if(SETTING_LIB_ADMIN_CLIENTS_FILE)
	{
		VAR_LIB_ADMIN->Load(SETTING_LIB_ADMIN_CLIENTS_FILE);
	}
	#endif
#endif
#ifdef USE_LIB_EASYADMIN
	VAR_LIB_EASYADMIN = new LIB_EASYADMIN_CLASS();
	#ifdef SETTING_LIB_EASYADMIN_FILE
	#ifdef SETTING_LIB_EASYADMIN_LOADFROM
	if(SETTING_LIB_EASYADMIN_FILE)
	{
		switch(SETTING_LIB_EASYADMIN_LOADFROM)
		{
		case LIB_EASYADMIN_CLASS::TextFile:
			VAR_LIB_EASYADMIN->LoadFromFile(SETTING_LIB_EASYADMIN_FILE);
			break;
		case LIB_EASYADMIN_CLASS::Keyvalues:
			VAR_LIB_EASYADMIN->LoadFromKeyvalue(SETTING_LIB_EASYADMIN_FILE);
			break;
		case LIB_EASYADMIN_CLASS::IniFile:
			VAR_LIB_EASYADMIN->LoadFromIni(SETTING_LIB_EASYADMIN_FILE);
			break;
		}
	}
	#endif
	#endif
#endif
#ifdef USE_LIB_LANG
	VAR_LIB_LANG = new LIB_LANG_CLASS(SETTING_LIB_LANG_WILDCARD);
	VAR_LIB_LANG->Load(SETTING_LIB_LANG_DIR);
#endif
#ifdef USE_LIB_MENU
	VAR_LIB_MENU = new LIB_MENU_CLASS();
#endif

	VAR_LIB_HACK = new LIB_HACK_CLASS(); // Must load

	VAR_PLUGIN_PYTHON = new PLUGIN_PYTHON_CLASS();
	VAR_PLUGIN_CONVARS = new PLUGIN_CONVARS_CLASS();
	VAR_PLUGIN_TIMERS = new PLUGIN_TIMERS_CLASS();
	PLUGIN_VAR = new PLUGIN_CLASS();
	VAR_PLUGIN_GAMEEVENTS = new PLUGIN_GAMEEVENTS_CLASS();

	if(!LIB_STRING_CLASS::StrIsNULL(VAR_IFACE_GLOBALVARS->mapname.ToCStr()))
	{
		VAR_PLUGIN_GLOBALS->szCurrentMap = VAR_IFACE_GLOBALVARS->mapname.ToCStr();
#ifdef USE_LIB_DOWNLOAD
		if(VAR_LIB_DOWNLOAD->DispatchDownloadsOnLoad)
			VAR_LIB_DOWNLOAD->DispatchDownloads();
#endif
#ifdef USE_LIB_PLAYERMNGR
		if(VAR_LIB_PLAYERMNGR)
		{
			LIB_MRECIPIENTFILTER_CLASS mfr;
			mfr.AddAllPlayers();
			for(int i = 0; i < mfr.GetRecipientCount(); i++)
			{
				VAR_LIB_PLAYERMNGR->AddClient(mfr.GetRecipientIndex(i));
			}
			mfr.~LIB_MRECIPIENTFILTER_CLASS();
		}
#endif
	}
}

//=================================================================================
// UnAssign libraries
//=================================================================================
void LIB_LIBRARIES_CLASS::UnAssign()
{
	if(PLUGIN_VAR)
		PLUGIN_VAR->~PLUGIN_CLASS();
	if(VAR_PLUGIN_PYTHON)
		VAR_PLUGIN_PYTHON->~PLUGIN_PYTHON_CLASS();
	if(VAR_PLUGIN_GAMEEVENTS)
		VAR_PLUGIN_GAMEEVENTS->~PLUGIN_GAMEEVENTS_CLASS();

	if(VAR_LIB_DOWNLOAD)
		VAR_LIB_DOWNLOAD->~LIB_DOWNLOAD_CLASS();
	if(VAR_LIB_SOUND)
		VAR_LIB_SOUND->~LIB_SOUND_CLASS();
	if(VAR_LIB_PLAYERMNGR)
		VAR_LIB_PLAYERMNGR->~LIB_PLAYERMNGR_CLASS();
	if(VAR_LIB_TIMER)
		VAR_LIB_TIMER->~LIB_TIMER_CLASS();
	if(VAR_LIB_PROFILING)
		VAR_LIB_PROFILING->~LIB_PROFILING_CLASS();
	if(VAR_LIB_ADMIN)
		VAR_LIB_ADMIN->~LIB_ADMIN_CLASS();
	if(VAR_LIB_EASYADMIN)
		VAR_LIB_EASYADMIN->~LIB_EASYADMIN_CLASS();
	if(VAR_LIB_LANG)
		VAR_LIB_LANG->~LIB_LANG_CLASS();

	if(VAR_PLUGIN_CONVARS)
		VAR_PLUGIN_CONVARS->~PLUGIN_CONVARS_CLASS();
	if(VAR_PLUGIN_TIMERS) 
		VAR_PLUGIN_TIMERS->~PLUGIN_TIMERS_CLASS();

	if(VAR_PLUGIN_GLOBALS)
		VAR_PLUGIN_GLOBALS->~PLUGIN_GLOBALS_CLASS();
	
}
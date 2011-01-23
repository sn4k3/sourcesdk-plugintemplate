//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#include "includes/default.h"
#include PLUGIN_MAIN_INCLUDE

//=================================================================================
// Constructor/Destructor
//=================================================================================
PLUGIN_CLASS::PLUGIN_CLASS()
{}

PLUGIN_CLASS::~PLUGIN_CLASS()
{}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//---------------------------------------------------------------------------------
bool PLUGIN_CLASS::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	Msg("Gamedir: %s\nGamefolder: %s\nGamename: %s\n", VAR_PLUGIN_GLOBALS->szGameDir, VAR_PLUGIN_GLOBALS->szGameFolder, VAR_PLUGIN_GLOBALS->szGameName);
	VAR_PLUGIN_CONVARS->Print();
	VAR_PLUGIN_CONVARS->AddOutsideConvar("sv_cheats"); // Keep sv_cheats in a list to fast access
	VAR_LIB_TIMER->Add("test", 10, 3, false, (void*)"Hi there from plugin");

	// test ini
	/*CIniLib *ini = new CIniLib("test.ini", false);
	ini->SetValue("Test key", "time", "22:11h", "Current time");
	ini->SetHearder("Hi there! im there to test ini lib\nThis is my head! :)");
	ini->Print();
	ini->New("SigSig", "renameme", "to be renamed");
	ini->Print();
	ini->Rename("SigSig", "renameme", "Hi there");
	ini->Print();
	ini->Remove("SigSig");
	ini->Print();
	ini->Rename("Test key", "Test");
	ini->Print();
	ini->Remove("Test", "time");
	ini->Print();
	ini->Write();
	ini->~CIniLib();*/

	// Initalize class
	LIB_CFG_CLASS *config = new LIB_CFG_CLASS("addons/plugintemplate/cfg/config.cfg");
	// We will create a config file, if don't exists one already
	if(!config->Load())
	{
		// Can't load, procede to creation
		config->Text("//***********************************//"); // Append a text line
		config->Text("//      PLUGIN TEMPLATE CONFIG       //"); 
		config->Text("//***********************************//");

		config->CVar("pt_rounds", "10", "Mod is only active in first 10 rounds"); // Append a cvar
		config->CVar("pt_enableclasses", "1", "Enable or not the plugin classes");
		config->CVar("pt_speed", "1", "Speed up gameplay up to defined value");

		config->Command("pt_addclass", "\"weapon_ak47, weapon_deagle\""); // Append an command
		config->Text("// Don't have mani? not a problem, command must exists to be written first");
		if(!config->Command(VAR_IFACE_ICVAR->FindCommand("mani_sethealth"), "#all 1000")) // Append an command giving and ConCommand*
			config->Text("// Yes i dont have mani-admin-plugin installed!");
		config->Text(" ");

		config->CVar(VAR_IFACE_ICVAR->FindVar("mp_restartgame"), "3"); // Append a cvar giving and ConVar*
		// Save to file
		config->Write();
	}
	// Change speed, we need more!
	config->CVar("pt_speed", "2", "Speed up gameplay up to defined value");
	// After load or create, execute cvars and commands
	config->Execute();
	// Save new configs
	config->Write(NULL, true, true, true, true/*We need to overwrite file*/, true);
	// If no longer needed, object should be free
	config->~LIB_CFG_CLASS();

	/*LIB_CFG_CLASS *config = new LIB_CFG_CLASS("testconfig.cfg");
	config->Text("// hi pll");
	config->Text("// hi pll");
	config->Text("// hi pll");
	config->CVar("motherfuckers", "lollolol");
	config->CVar("hoostname", "\"qwe2  asd\"", "server name");
	config->Command("mother", "lollossslol");
	config->Command("mother2");
	config->Command("mother", "no lol", "asdasd", true);
	config->CVar("hoostname", "me server", "server name 2");
	config->CVar(VAR_IFACE_ICVAR->FindVar("sv_cheats"));
	config->Write(NULL, true, true, true, true, true);*/
	LIB_CFG_CLASS::Exec("game11");
	LIB_CFG_CLASS::Exec("game.cfg");
	Msg("Die!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	LIB_CFG_CLASS *config2 = LIB_CFG_CLASS::ExecEx2("gadme.cfg");
	if(config2)
	{
		Msg("Config Lines: %i\n", config2->vec_file.Count());
		config2->~LIB_CFG_CLASS();
	}
	LIB_CFG_CLASS *serverconfig = new LIB_CFG_CLASS("cfg/server.cfg");
	serverconfig->Load();
	serverconfig->Print();
	serverconfig->Write("cfg/serverCOPY.cfg", true, true, true, true);
	serverconfig->~LIB_CFG_CLASS();
	return true;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::Unload(void)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is paused (i.e should stop running but isn't unloaded)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::Pause(void)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unpaused (i.e should start executing again)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::UnPause(void)
{

}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::LevelInit(char const *pMapName, const char *pOldMapName)
{
}

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{

}

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::GameFrame(bool simulating)
{

}

//---------------------------------------------------------------------------------
// Purpose: called on level end (as the server is shutting down or going to a new map)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::LevelShutdown(void)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::ClientActive(edict_t *pEntity)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::ClientDisconnect(edict_t *pEntity)
{

}

void PLUGIN_CLASS::ClientPutInServer(edict_t *pEntity, char const *playername)
{

}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::SetCommandClient(int index)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when the client change a setting (i.e name)
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::ClientSettingsChanged(edict_t *pEdict)
{

}

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
PLUGIN_RESULT PLUGIN_CLASS::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client types in a command (only a subset of commands however, not CON_COMMAND's)
//---------------------------------------------------------------------------------
CMD_PLUGIN_RESULT PLUGIN_CLASS::ENGINE_ClientCommand(pEntity)
{
	const char *pcmd = args.Arg(0);
	
	// TEST BLOCK
	// REMOVE TEST BLOCK
	if (LIB_STRING_CLASS::FStrEq(pcmd, "pt_translateme"))
	{
		if(!VAR_LIB_LANG) // Lang Lib was not initalized
			CMD_CONTINUE;
		// Show on player chat
		LIB_MESSAGE_CLASS::Say(pEntity, ""SAY_GREEN"Based on your game language:\n"SAY_DEFAULT"%s\n", VAR_LIB_LANG->GetLangStr(pEntity, "main", "translateme"));
		CMD_OVERRIDE;
	}
	if (LIB_STRING_CLASS::FStrEq(pcmd, "pt_radiusme"))
	{
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(pEntity);
		Msg("Are you within the radius?: %i\n", player->IsWithinRadius(LIB_STRING_CLASS::StrToVec(args.Arg(1)), atof(args.Arg(2))));
		CMD_OVERRIDE;
	}
	if (LIB_STRING_CLASS::FStrEq(pcmd, "menu"))
	{
		// Simple menu test
		if(VAR_LIB_MENU->Create("test", LIB_MENU_CLASS::SIMPLE, "Choose an option\n ", " \n0. Cancel"))
		{
			VAR_LIB_MENU->AddLine("test", "Hi there");
			VAR_LIB_MENU->AddLine("test", "You type 'menu' in console...");
			VAR_LIB_MENU->AddLine("test", "That menu was created using MenuLib");
			VAR_LIB_MENU->AddLine("test", "Explore all the functions.");
			VAR_LIB_MENU->AddLine("test", "->1. Click me!");
		}
		//VAR_LIB_MENU->DumpMenu("test"); / Test only
		VAR_LIB_MENU->Send(pEntity, "test");
		CMD_OVERRIDE;
	}
	if (LIB_STRING_CLASS::FStrEq(pcmd, "supermenu"))
	{
		// Create multi pagged menu, if not already
		if(VAR_LIB_MENU->Create("numbers", LIB_MENU_CLASS::PAGED, "Choose an option\n "))
		{
			// Some compability, see that cool feature
			if(VAR_LIB_SOUND)
				VAR_LIB_MENU->SetSounds(VAR_LIB_SOUND->GetSound("menu_select", "buttons/button14.wav"), VAR_LIB_SOUND->GetSound("menu_back", "buttons/button9.wav"), VAR_LIB_SOUND->GetSound("menu_next", "buttons/blip1.wav"), VAR_LIB_SOUND->GetSound("menu_exit", "buttons/combine_button7.wav"));
			else
				VAR_LIB_MENU->SetSounds("buttons/button14.wav", "buttons/button9.wav", "buttons/blip1.wav", "buttons/combine_button7.wav");
			// Add many as you want, they will got pagged
			VAR_LIB_MENU->AddLineEx("numbers", "One", NULL, false);
			VAR_LIB_MENU->AddLineEx("numbers", "Two", (void*)"Number 2", true);
			VAR_LIB_MENU->AddLineEx("numbers", "Three");
			VAR_LIB_MENU->AddLineEx("numbers", "Four");
			VAR_LIB_MENU->AddLineEx("numbers", "Five");
			VAR_LIB_MENU->AddLineEx("numbers", "Six");
			VAR_LIB_MENU->AddLineEx("numbers", "Seven", NULL, false);
			VAR_LIB_MENU->AddLineEx("numbers", "Eight");
			VAR_LIB_MENU->AddLineEx("numbers", "Nine");
			VAR_LIB_MENU->AddLineEx("numbers", "Ten");
			VAR_LIB_MENU->AddLineEx("numbers", "Eleven");
			VAR_LIB_MENU->AddLineEx("numbers", "Twelve");
			VAR_LIB_MENU->AddLineEx("numbers", "Thirthin");
			VAR_LIB_MENU->AddLineEx("numbers", "Fourthin");
			VAR_LIB_MENU->AddLineEx("numbers", "Fivethin", NULL, false);
			VAR_LIB_MENU->AddLineEx("numbers", "Sixthin");
			VAR_LIB_MENU->AddLineEx("numbers", "Seventhin");
			VAR_LIB_MENU->AddLineEx("numbers", "Ninethin");
			VAR_LIB_MENU->AddLineEx("numbers", "Tweenty");
		}
		//VAR_LIB_MENU->DumpMenu("numbers"); // Test only
		// Send menu to player
		VAR_LIB_MENU->Send(pEntity, "numbers");
		CMD_OVERRIDE;
	}
	if (LIB_STRING_CLASS::FStrEq(pcmd, "playermenu")) // I want to see a player list
	{
		if(!VAR_LIB_PLAYERMNGR) // We dont need this to make a player list, but its cool to use it
		{
			CMD_CONTINUE;
		}
		// Create multi pagged menu, if not already
		if(VAR_LIB_MENU->Create("players", LIB_MENU_CLASS::PAGED, "Choose a player\n "))
		{
			// Some compability, see that cool feature
			if(VAR_LIB_SOUND)
				VAR_LIB_MENU->SetSounds(VAR_LIB_SOUND->GetSound("menu_select", "buttons/button14.wav"), VAR_LIB_SOUND->GetSound("menu_back", "buttons/button9.wav"), VAR_LIB_SOUND->GetSound("menu_next", "buttons/blip1.wav"), VAR_LIB_SOUND->GetSound("menu_exit", "buttons/combine_button7.wav"));
			else
				VAR_LIB_MENU->SetSounds("buttons/button14.wav", "buttons/button9.wav", "buttons/blip1.wav", "buttons/combine_button7.wav");
			// foreach players inside PLAYERMNGR
			for(int i = 0; i < VAR_LIB_PLAYERMNGR->Count(); i++)
			{
				PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR->vec_players[i];
				// Add player to menu list, and give edict as argument
				VAR_LIB_MENU->AddLine("players", player->PlayerInfo()->GetName(), player->Edict());
			}
		}
		// Send menu to player
		VAR_LIB_MENU->Send(pEntity, "players");
		// After send we remove menu, to recreate a fresh with new players if avaliable when requested
		VAR_LIB_MENU->Remove("players"); 
		CMD_OVERRIDE;
	}
	// END TEST BLOCK

	CMD_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
CMD_PLUGIN_RESULT PLUGIN_CLASS::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	CMD_CONTINUE;
}

//---------------------------------------------------------------------------------
// Purpose: called when a cvar value query is finished
//---------------------------------------------------------------------------------
void PLUGIN_CLASS::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{

}

//=================================================================================
// Extern global variable, never touch
//=================================================================================
PLUGIN_CLASS *PLUGIN_VAR = NULL;

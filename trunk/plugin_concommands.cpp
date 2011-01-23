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

PLUGIN_CON_COMMAND(cvarlist, "Prints "PLUGIN_NAME" convars and concommands" )
{
	VAR_PLUGIN_CONVARS->Print();
}

PLUGIN_CON_COMMAND(convarlist, "Prints "PLUGIN_NAME" convars" )
{
	VAR_PLUGIN_CONVARS->Print(true, false);
}

PLUGIN_CON_COMMAND(cmdlist, "Prints "PLUGIN_NAME" concommands" )
{
	VAR_PLUGIN_CONVARS->Print(false, true);
}

PLUGIN_CON_COMMAND(csay, "Print text in screen center")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <text>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MESSAGE_CLASS::CenterSay(args.Arg(1), args.Arg(2));
}

PLUGIN_CON_COMMAND(cprint, "Print text in client console")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <text>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MESSAGE_CLASS::CPrint(args.Arg(1), args.Arg(2));
}

PLUGIN_CON_COMMAND(entry, "Print text in client console")
{
	if(args.ArgC() < 6)
	{
		Msg("Syntax: %s <players> <time> <title> <cmd> <msg>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MESSAGE_CLASS::Entry(args.Arg(1), atoi(args.Arg(2)), args.Arg(3), args.Arg(4), args.Arg(5));
}

PLUGIN_CON_COMMAND(fade, "Fade a player")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <delay> <time> [red] [green] [blue] [alpha]\n",args.Arg(0)); // Error Message
		return;
	}
	int red = args.ArgC() < 5 ? 255 : atoi(args.Arg(4));
	int green = args.ArgC() < 6 ? 255 : atoi(args.Arg(5));
	int blue = args.ArgC() < 7 ? 255 : atoi(args.Arg(6));
	int alpha = args.ArgC() < 8 ? 255 : atoi(args.Arg(7));
	LIB_MESSAGE_CLASS::Fade(args.Arg(1), FFADE_OUT | FFADE_STAYOUT, atof(args.Arg(2)), atof(args.Arg(3)), red, green, blue, alpha);
}

PLUGIN_CON_COMMAND(hint, "Send a hint to player")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <text>\n",args.Arg(0)); // Error Message
		return;
	}
	char text[MAX_STR_LEN];
	snprintf(text, MAX_STR_LEN, "%s", args.Arg(2));
	LIB_STRING_CLASS::StrEscape(text, MAX_STR_LEN);
	LIB_MESSAGE_CLASS::Hint(args.Arg(1), text);
}

PLUGIN_CON_COMMAND(menu, "Send a menu to player")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <text> <time> [options]\n",args.Arg(0)); // Error Message
		return;
	}
	int time = args.ArgC() < 4 ? 0 : atoi(args.Arg(3));
	const char *options = args.ArgC() < 5 ? "0123456789" : args.Arg(4);
	char text[MAX_STR_LEN];
	snprintf(text, MAX_STR_LEN, "%s", args.Arg(2));
	LIB_STRING_CLASS::StrEscape(text, MAX_STR_LEN);
	LIB_MESSAGE_CLASS::Menu(args.Arg(1), time, text, options);
}

PLUGIN_CON_COMMAND(redirect, "Redirect a player to other server")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <ip> [time]\n",args.Arg(0)); // Error Message
		return;
	}
	int time = atoi(args.Arg(3));
	LIB_MESSAGE_CLASS::Redirect(args.Arg(1), time, args.Arg(2));
}

PLUGIN_CON_COMMAND(richbox, "Sends a richbox to player")
{
	if(args.ArgC() < 5)
	{
		Msg("Syntax: %s <players> <time> <title> <text>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MESSAGE_CLASS::RichBox(args.Arg(1), atoi(args.Arg(2)), args.Arg(3), args.Arg(4));
}

PLUGIN_CON_COMMAND(say, "Print text in player chat")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <text>\n",args.Arg(0)); // Error Message
		return;
	}
	char text[MAX_STR_LEN];
	snprintf(text, MAX_STR_LEN, "%s", args.Arg(2));
	LIB_STRING_CLASS::StrEscape(text, MAX_STR_LEN);
	LIB_MESSAGE_CLASS::SayEscapeColors(text, MAX_STR_LEN);
	LIB_MESSAGE_CLASS::Say(args.Arg(1), text);
}

PLUGIN_CON_COMMAND(shake, "Shakes player screen")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <players> [time] [magnitude] [noise]\n",args.Arg(0)); // Error Message
		return;
	}
	float time = args.ArgC() < 3 ? 10 : atof(args.Arg(2));
	float magnitude = args.ArgC() < 4 ? 25 : atof(args.Arg(3));
	float noise = args.ArgC() < 5 ? 125 : atof(args.Arg(4));
	LIB_MESSAGE_CLASS::Shake(args.Arg(1), time, SHAKE_START, magnitude, noise);
}

PLUGIN_CON_COMMAND(tsay, "Show a top message to players")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <time> <text> [red] [green] [blue] [alpha]\n",args.Arg(0)); // Error Message
		return;
	}
	int red = args.ArgC() < 5 ? 255 : atoi(args.Arg(4));
	int green = args.ArgC() < 6 ? 255 : atoi(args.Arg(5));
	int blue = args.ArgC() < 7 ? 255 : atoi(args.Arg(6));
	int alpha = args.ArgC() < 8 ? 255 : atoi(args.Arg(7));
	LIB_MESSAGE_CLASS::Top(args.Arg(1), atoi(args.Arg(2)), args.Arg(3), red, green, blue, alpha);
}

PLUGIN_CON_COMMAND(vgui, "Show a vgui to players")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <title> <text> [type]\n",args.Arg(0)); // Error Message
		return;
	}
	int type = args.ArgC() < 5 ? 0 : atoi(args.Arg(4));
	LIB_MESSAGE_CLASS::VGUI(args.Arg(1), type, args.Arg(2), args.Arg(3));
}

PLUGIN_CON_COMMAND(randplayer, "Get a random player")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <players>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(LIB_ENTITY_CLASS::GetEntityOfRandPlayer(args.Arg(1)));
	if(!player->IsValid())
	{
		Msg("No player found\n");
		return;
	}

	Msg("Rand player: %s\n", player->PlayerInfo()->GetName());
}

PLUGIN_CON_COMMAND(playercount, "Count players")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <players>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	Msg("Founded: '%i' Players!\n", mrf.GetRecipientCount());
}

PLUGIN_CON_COMMAND(playerlist, "List players")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <players>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	Msg(""PLUGIN_HEADER"Player List\n_____________________________\nTotal Players: %i\n", mrf.GetRecipientCount());
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));
		Msg("Player '%s' [%s]:\nIndex = %i\nUserid: %i\n----------------------\n", 
			player->PlayerInfo()->GetName(), player->SteamID(), player->Index(), player->UserID());
	}
}

PLUGIN_CON_COMMAND(emitsound, "Emit a sound file to players")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <target> <file> [volume] [attenuation]\n",args.Arg(0)); // Error Message
		return;
	}
	float volume = args.ArgC() < 5 ? VOL_NORM : atof(args.Arg(4));
	float attenuation = args.ArgC() < 6 ? VOL_NORM : atof(args.Arg(5));
	LIB_SOUND_CLASS::EmitSound(args.Arg(1), LIB_ENTITY_CLASS::GetEntityOfRandPlayer((char*)args.Arg(2)), args.Arg(3), volume, attenuation);
}

PLUGIN_CON_COMMAND(play, "Play a sound file to players")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <file>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_SOUND_CLASS::Play(args.Arg(1), args.Arg(2));
}

PLUGIN_CON_COMMAND(countdown, "Show a count down in console")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <positive-number>\n",args.Arg(0)); // Error Message
		return;
	}
	int repeats = atoi(args.Arg(1));
	if(repeats < 1)
	{
		Msg("Syntax: %s <positive-number>\n",args.Arg(0)); // Error Message
		return;
	}
#ifndef USE_LIB_TIMER
	Msg("Timers are disabled, can't count down\n");
#else
	if(VAR_LIB_TIMER->Exists("countdown"))
	{
		Msg("Currently there are one count down, wait for his termination!\n");
	}
	else
		VAR_LIB_TIMER ->Add("countdown", 1, repeats, false, NULL, NULL, NULL, repeats);
#endif
}

PLUGIN_CON_COMMAND(formatbytes, "Format bytes to best file size")
{
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <positive-number>\n",args.Arg(0)); // Error Message
		return;
	}
	unsigned long bytes = atol(args.Arg(1));
	if(bytes < 1)
	{
		Msg("Syntax: %s <positive-number>\n",args.Arg(0)); // Error Message
		return;
	}
	Msg("%lu Byte(s) = %.2Lf %s\n", bytes, LIB_UNITCONVERTER_CLASS::FormatByteSize(bytes), LIB_UNITCONVERTER_CLASS::GetSizeNameFromBytes(bytes));
}

PLUGIN_CON_COMMAND(client, "Manage admins, groups and thier data")
{
	if(!VAR_LIB_ADMIN)
	{
		Msg("Admin features is disabled.");
		return;
	}
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <command> [arg1] [arg2]\
    Commands:\n",args.Arg(0)); // Error Message
		return;
	}
	const char *command = args.Arg(1);
	const char *arg1 = args.Arg(2);
	const char *arg2 = args.Arg(3);
	if(LIB_STRING_CLASS::FStrEq(command, "addclient"))
	{
		VAR_LIB_ADMIN->AddClient("STEAM_ID_LAN", arg1, arg1);
		VAR_LIB_ADMIN->Save("client_test.txt");
		return;
	}
	if(LIB_STRING_CLASS::FStrEq(command, "addagroup"))
	{
		//VAR_LIB_ADMIN->("STEAM_ID_LAN", arg1, arg1);
		return;
	}
	if(LIB_STRING_CLASS::FStrEq(command, "setnick"))
	{
		VAR_LIB_ADMIN->UpdateClientByUniqueName(arg1, arg2);
		VAR_LIB_ADMIN->Save();
		return;
	}
	if(LIB_STRING_CLASS::FStrEq(command, "print"))
	{
		VAR_LIB_ADMIN->DebugClients();
		return;
	}
}

PLUGIN_CON_COMMAND(makeadmin, "Add a steam id as admin")
{
	if(!VAR_LIB_EASYADMIN)
	{
		Msg("Easy Admin features are disabled.");
		return;
	}
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <steamid>\n",args.Arg(0)); // Error Message
		return;
	}
	VAR_LIB_EASYADMIN->Add(args.Arg(1));
}

PLUGIN_CON_COMMAND(isadmin, "Check if a steam id was an admin")
{
	if(!VAR_LIB_EASYADMIN)
	{
		Msg("Easy Admin features are disabled.");
		return;
	}
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <steamid>\n",args.Arg(0)); // Error Message
		return;
	}
	if(VAR_LIB_EASYADMIN->IsAdmin(args.Arg(1)))
		Msg("%s is an admim\n", args.Arg(1));
	else
		Msg("%s is not an admim\n", args.Arg(1));
}

PLUGIN_CON_COMMAND(printadmins, "Show all admins steamids")
{
	if(!VAR_LIB_EASYADMIN)
	{
		Msg("Easy Admin features are disabled.");
		return;
	}
	VAR_LIB_EASYADMIN->PrintAdmins();
}


PLUGIN_CON_COMMAND(dumpprops, "Dump props")
{
	if(args.ArgC() < 1)
	{
		Msg("Syntax: %s [classname]\n",args.Arg(0)); // Error Message
		return;
	}
	const char *classname = args.ArgC() < 2 ? NULL : args.Arg(1);
	LIB_PROP_CLASS::DumpProps(classname);
}

PLUGIN_CON_COMMAND(sethealth, "Set player health")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <amount>\n",args.Arg(0)); // Error Message
		return;
	}
	int amount = atoi(args.Arg(2));
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));
		if(!player->IsAlive())
		{
			Msg("ERROR: Dead player, can't set health to: %s\n", player->PlayerInfo()->GetName());
			player->~LIB_PLAYER_CLASS();
			continue;
		}
		VAR_LIB_PROP->Prop_SetInt(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), "CBasePlayer", "m_iHealth", amount);
		int health = VAR_LIB_PROP->Prop_GetInt(player->Edict(), "CBasePlayer", "m_iHealth");
		Msg("Player '%s', have now %i Health\n", player->PlayerInfo()->GetName(), health);
		player->~LIB_PLAYER_CLASS();
	}
}

PLUGIN_CON_COMMAND(health, "Math player health")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <amount> <operator>\n",args.Arg(0)); // Error Message
		return;
	}
	int amount = atoi(args.Arg(2));
	char coperator = *args.Arg(3);
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));
		if(!player->IsAlive())
		{
			Msg("ERROR: Dead player, can't set health to: %s\n", player->PlayerInfo()->GetName());
			player->~LIB_PLAYER_CLASS();
			continue;
		}
		int currenthealth = VAR_LIB_PROP->Prop_GetInt(player->Edict(), "CBasePlayer", "m_iHealth");
		switch(coperator)
		{
		case '+':
			amount += currenthealth;
			break;
		case '-':
			amount = currenthealth-amount;
			break;
		case '*':
			amount *= currenthealth;
			break;
		case '/':
			amount = currenthealth/amount;
			break;
		}
		if(amount < 0)
		{
			Msg("Can't set player '%s' Health, value is negative\n", player->PlayerInfo()->GetName());
			return;
		}
		VAR_LIB_PROP->Prop_SetInt(player->Edict(), "CBasePlayer", "m_iHealth", amount);
		Msg("Player '%s', have now %i Health\n", player->PlayerInfo()->GetName(), amount);
		player->~LIB_PLAYER_CLASS();
	}

}

PLUGIN_CON_COMMAND(setplayerprop, "Set player property")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <prop> <value>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		VAR_LIB_PROP->Prop_SetDynamic(mrf.GetRecipientEdict(i), args.Arg(2), NULL, args.Arg(3));
	}
}

PLUGIN_CON_COMMAND(setplayerdmap, "Set player datamap")
{
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <players> <datamap_name> <value>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		VAR_LIB_PROP->Map_SetDynamic(mrf.GetRecipientBaseEntity(i), args.Arg(2), args.Arg(3));
	}
}

PLUGIN_CON_COMMAND(getplayerprop, "Get player property")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <prop>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		Msg("Player %i: %s\n", mrf.GetRecipientIndex(i), VAR_LIB_PROP->Prop_GetDynamic(mrf.GetRecipientEdict(i), args.Arg(2), NULL));
	}
}

PLUGIN_CON_COMMAND(getplayerdmap, "Get player datamap")
{
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <datamap_name>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		Msg("Player %i: %s\n", mrf.GetRecipientIndex(i), VAR_LIB_PROP->Map_GetDynamic(mrf.GetRecipientBaseEntity(i), args.Arg(2)));
	}
}

PLUGIN_CON_COMMAND(dumptranslations, "Get one translated phrase")
{
	if(!VAR_LIB_LANG)
	{
		Msg("Language features are disabled.");
		return;
	}
	VAR_LIB_LANG->PrintTranslations();
}

PLUGIN_CON_COMMAND(gettranslation, "Get one translated phrase")
{
	if(!VAR_LIB_LANG)
	{
		Msg("Language features are disabled.");
		return;
	}
	if(args.ArgC() < 4)
	{
		Msg("Syntax: %s <namespace> <phrase> <language>\n",args.Arg(0)); // Error Message
		return;
	}
	VAR_LIB_LANG->LoadSingleFile("addons/plugintemplate/translations/main.phrases.txt");
	const char *language = args.Arg(3);
	const char *phrase = VAR_LIB_LANG->GetLangStr(args.Arg(1), args.Arg(2), language);
	Msg("[%s] %s\n", language, phrase);
}

PLUGIN_CON_COMMAND(teleport, "Teleport a player")
{
	if(!VAR_LIB_VFUNCS)
	{
		Msg("VFuncs features are disabled.");
		return;
	}
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <\"x y z Position\"> [\"x y z Velocity\"]\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	Vector vec = LIB_STRING_CLASS::StrToVec(args.Arg(2));
	Vector velocity = args.ArgC() < 4 ? NULL : LIB_STRING_CLASS::StrToVec(args.Arg(3));
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		VAR_LIB_VFUNCS->CBaseEntity_Teleport(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), &vec, NULL, &velocity, "CBaseEntity::Teleport");
	}
}

PLUGIN_CON_COMMAND(spawn, "Spanws a player")
{
	if(!VAR_LIB_SIGSCAN)
	{
		Msg("SigScan features are disabled.");
		return;
	}
	if(args.ArgC() < 2)
	{
		Msg("Syntax: %s <players> [force]\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	bool force = args.ArgC() >= 3;
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		edict_t *pEntity = PEntityOfEntIndex(mrf.GetRecipientIndex(i));
		if(!pEntity) continue;
		if (force)
		{
			VAR_LIB_SIGSCAN->CSSPlayer_RoundRespawn(pEntity, "CSSPlayer::RoundRespawn");
			continue;
		}
		if(!LIB_PLAYER_CLASS::IsAlive(pEntity))
		{
			VAR_LIB_SIGSCAN->CSSPlayer_RoundRespawn(pEntity, "CSSPlayer::RoundRespawn");
		}
	}
}

PLUGIN_CON_COMMAND(switchteam, "Switch a player fro other team")
{
	if(!VAR_LIB_SIGSCAN)
	{
		Msg("SigScan features are disabled.");
		return;
	}
	if(args.ArgC() < 3)
	{
		Msg("Syntax: %s <players> <team>\n",args.Arg(0)); // Error Message
		return;
	}
	LIB_MRECIPIENTFILTER_CLASS mrf;
	mrf.AddByFilter(args.Arg(1), false);
	int team = atoi(args.Arg(2));
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		VAR_LIB_SIGSCAN->CSSPlayer_SwitchTeam(mrf.GetRecipientEdict(i), team, "CSSPlayer::SwitchTeam");
	}
}

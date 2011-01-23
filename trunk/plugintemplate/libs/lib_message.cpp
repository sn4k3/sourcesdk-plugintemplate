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
#include "includes/default.h"
#include "libs/lib_message.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Static Methods
//=================================================================================
// Get Message Index
int LIB_MESSAGE_CLASS::GetMsgNum(const char *Msg)
{
#ifdef SOURCEMM
	return g_SMAPI->FindUserMessage(Msg);
#endif
	char TempMsgName[40];
	int dontdoit=0;
#ifdef SOURCEMM
	int MaxScan = g_SMAPI->GetUserMessageCount();
#else
	int MaxScan= 20;
	if(LIB_STRING_CLASS::StrLeftEq(VAR_IFACE_GAMESERVERDLL->GetGameDescription(),"Counter-Strike"))
		MaxScan = 25;
#endif
	for (int i=0;i<MaxScan;i++) 
	{
		VAR_IFACE_GAMESERVERDLL->GetUserMessageInfo(i,TempMsgName,39,dontdoit);
		if(strcmp(Msg,TempMsgName) == 0)
			return i;
	}
	return -1;
}

// Print text to client console.
// Filters allowed
bool LIB_MESSAGE_CLASS::CPrint(const char *players, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS(msg);

	for(int i = 0; i < mrf.GetRecipientCount(); i++)
	{
		CPrint(mrf.GetRecipientEdict(i), string);
	}
	mrf.~LIB_MRECIPIENTFILTER_CLASS();
	return true;
}

// Print text to client console.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::CPrint(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...)
{
	int count = mrf.GetRecipientCount();
	if(count == 0) return false;
	MULTIARGS(msg);
	for(int i = 0; i < count; i++)
	{
		CPrint(mrf.GetRecipientEdict(i), string);
	}
	return true;
}

// Print text to client console.
bool LIB_MESSAGE_CLASS::CPrint(edict_t *pEntity, const char *msg, ...)
{
	IPlayerInfo *playerinfo = LIB_ENTITY_CLASS::GetPlayerinfoFromEntity(pEntity);
	if(!playerinfo) return false;
	if(playerinfo->IsFakeClient()) return false; // Bot crash protection!
	MULTIARGS(msg);
	VAR_IFACE_ENGINE->ClientPrintf(pEntity, string);
	return true;
}

// Send a message and log.
void LIB_MESSAGE_CLASS::MsgALog(const char *msg, bool isWarning /*= false*/, ...)
{
	MULTIARGS(msg);
	VAR_IFACE_ENGINE->LogPrint(string);
	if(isWarning)
		Msg(string);
	else
		Warning(string);
}

// Shake player screen.
// Filters allowed
bool LIB_MESSAGE_CLASS::Shake(const char *players, float fTime /*= 10*/, int nType /*= SHAKE_START*/, float fMagnitude /*= 25*/, float fNoise /*= 150*/)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	bool result = Shake(mrf, fTime, nType, fMagnitude, fNoise);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Shake player screen.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Shake(LIB_MRECIPIENTFILTER_CLASS &mrf, float fTime /*= 10*/, int nType /*= SHAKE_START*/, float fMagnitude /*= 25*/, float fNoise /*= 150*/)
{
	if(!mrf.GetRecipientCount()) return false;
	int shakeIndex = GetMsgNum("Shake");
	if(shakeIndex == -1) return false;
	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, shakeIndex);
	if(!pWrite) return false;

    pWrite->WriteByte(nType); 		// shake command (SHAKE_START, STOP, FREQUENCY, AMPLITUDE)
    pWrite->WriteFloat(fMagnitude); // shake magnitude/amplitude
    pWrite->WriteFloat(fNoise); 	// shake noise frequency
    pWrite->WriteFloat(fTime);  	// shake lasts this long
	VAR_IFACE_ENGINE->MessageEnd();
	return true;
}

// Shake player screen.
bool LIB_MESSAGE_CLASS::Shake(edict_t *pEntity, float fTime /*= 10*/, int nType /*= SHAKE_START*/, float fMagnitude /*= 25*/, float fNoise /*= 150*/)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;

	bool result = Shake(mrf, fTime, nType, fMagnitude, fNoise);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Fade player screen.
// Filters allowed
bool LIB_MESSAGE_CLASS::Fade(const char *players, short nFlags /*= (FFADE_OUT | FFADE_STAYOUT)*/, float fFadeTime /*= 5*/, float fHoldTime /*= 30*/, int red /*= 0*/, int green /*= 0*/, int blue /*= 0*/, int alpha /*= 255*/)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	bool result = Fade(mrf, nFlags, fFadeTime, fHoldTime, red, green, blue, alpha);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Fade player screen.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Fade(LIB_MRECIPIENTFILTER_CLASS &mrf, short nFlags /*= (FFADE_OUT | FFADE_STAYOUT)*/, float fFadeTime /*= 5*/, float fHoldTime /*= 30*/, int red /*= 0*/, int green /*= 0*/, int blue /*= 0*/, int alpha /*= 255*/)
{
	if(!mrf.GetRecipientCount()) return false;
	int fadeIndex = GetMsgNum("Fade");
	if(fadeIndex == -1) return false;
	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, fadeIndex);
	if(!pWrite) return false;

	pWrite->WriteShort((short)(fFadeTime * 1000)); 	// fade out/in time
	pWrite->WriteShort((short)(fHoldTime * 1000));  // how long fade lasts
	pWrite->WriteShort(nFlags); 	// FFADE_IN - fade back in, FFADE_OUT - fade out to color, FFADE_PURGE - remove all fades, FFADE_STAYOUT - fade and stay, FFADE_MODULATE - blends colors?
	pWrite->WriteByte(red); 	// fade red
	pWrite->WriteByte(green); 	// fade green
	pWrite->WriteByte(blue); 	// fade blue
	pWrite->WriteByte(alpha); 	// fade alpha transparency
	VAR_IFACE_ENGINE->MessageEnd();

	return true;
}

// Fade player screen.
bool LIB_MESSAGE_CLASS::Fade(edict_t *pEntity, short nFlags /*= (FFADE_OUT | FFADE_STAYOUT)*/, float fFadeTime /*= 5*/, float fHoldTime /*= 30*/, int red /*= 0*/, int green /*= 0*/, int blue /*= 0*/, int alpha /*= 255*/)
{

	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;

	bool result = Fade(mrf, nFlags, fFadeTime, fHoldTime, red, green, blue, alpha);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Send text to player chat.
// Filters allowed
bool LIB_MESSAGE_CLASS::Say(const char *players, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS(msg);

	bool result = Say(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();
	
    return result;
}

// Send text to player chat.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Say(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...)
{
	if(!mrf.GetRecipientCount()) return false;
	int sayIndex = GetMsgNum("SayText");
	if(sayIndex == -1) return false;
	//remember to add \x01=yelow, \x03=lightgreen, \x04=green to msg
	MULTIARGS(msg);
	
    int len = strlen(string);
    if (len > 254)
	{
		char tmp[256];
		for (int i = 0; i < len; i += 254)
		{
			Q_strncpy(tmp, msg + i, 254);
			tmp[255] = 0;
			bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf,sayIndex);
			if(!pWrite) continue;
			pWrite->WriteByte(0);
			pWrite->WriteString(tmp);
			pWrite->WriteByte(0);
			VAR_IFACE_ENGINE->MessageEnd();
		}
		return true;
	}

	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf,sayIndex);
	if(!pWrite) return false;

	pWrite->WriteByte(0);
	pWrite->WriteString(string);
	pWrite->WriteByte(0);
	VAR_IFACE_ENGINE->MessageEnd();

	return true;
}

// Send text to player chat.
bool LIB_MESSAGE_CLASS::Say(edict_t *pEntity, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;
	MULTIARGS(msg);
	
    bool result = Say(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();
	
    return result;
}

void LIB_MESSAGE_CLASS::SayEscapeColors(char *str, unsigned int len)
{
	if(!str) return;
	LIB_STRING_CLASS::StrReplace(str, "\\x01", SAY_DEFAULT, len);
	LIB_STRING_CLASS::StrReplace(str, "\\x04", SAY_GREEN, len);
	LIB_STRING_CLASS::StrReplace(str, "\\x03", SAY_LIGHTGREEN, len);
	//LIB_STRING_CLASS::StrReplace(str, "\\x03", SAY_RED, len);
	//LIB_STRING_CLASS::StrReplace(str, "\\x03", SAY_BLUE, len);
	LIB_STRING_CLASS::StrReplace(str, "\\x05", SAY_OLIVE, len);
}

// Print text to player on center screen.
// Filters allowed
bool LIB_MESSAGE_CLASS::CenterSay(const char *players, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS(msg);

	bool result = CenterSay(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Print text to player on center screen.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::CenterSay(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...)
{
	if(!mrf.GetRecipientCount()) return false;
	int centerIndex = GetMsgNum("TextMsg");
	if(centerIndex == -1) return false;
	
	MULTIARGS(msg);

	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, centerIndex);
	if(!pWrite) return false;

	pWrite->WriteByte(HUD_PRINTCENTER);
	pWrite->WriteString(string);
	VAR_IFACE_ENGINE->MessageEnd();

	return true;
}

// Print text to player on center screen.
bool LIB_MESSAGE_CLASS::CenterSay(edict_t *pEntity, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;
	MULTIARGS(msg);

	bool result = CenterSay(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Print a hint to player.
// Filters allowed
bool LIB_MESSAGE_CLASS::Hint(const char *players, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	MULTIARGS(msg);

	bool result = Hint(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Print a hint to player.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Hint(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...)
{
	if(!mrf.GetRecipientCount()) return false;
	int hintIndex = GetMsgNum("HintText");
	if(hintIndex == -1) return false;

	MULTIARGS(msg);

	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, hintIndex);
	if(!pWrite) return false;
	//pWrite->WriteByte(-1);
	pWrite->WriteByte(1);
	pWrite->WriteString(string);
	VAR_IFACE_ENGINE->MessageEnd();

	return true;
}

// Print a hint to player.
bool LIB_MESSAGE_CLASS::Hint(edict_t *pEntity, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;
	
	MULTIARGS(msg);

	bool result = Hint(mrf, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Transform a numeric string into int keys to use with menus
// eg. "01239"
// 0 = 1 Key
// ...
// 8 = 9 Key
// 9 = 0 Key AKA Exit
// No digit character is ignored
int LIB_MESSAGE_CLASS::MenuOptionsFromString(const char *options /*= "0123456789"*/)
{
	int temp = 0, keys = 0;

	for (unsigned int i = 0; i < strlen(options); i++)
	{
		if(!isdigit(options[i])) continue;

		temp = options[i]-49;
		if(temp == -1)
			temp = 9;
		if(temp >= 0 && temp <= 9 && !(keys & (1 << temp)))
			keys |= 1 << temp;
	}
	return keys != 0 ? keys : (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)| (1<<8) | (1<<9);
}

// Shows a menu to player.
// Allow filters
bool LIB_MESSAGE_CLASS::Menu(const char *players, int time, const char *msg, const char *options /*= "0123456789"*/, ...)
{
	int menuIndex = GetMsgNum("ShowMenu");
	if(menuIndex == -1) return false;
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS2(msg, options);
	
	int keys = MenuOptionsFromString(options);

	char* page;
	bool bMoreToCome = true;
    int i = 0;
	unsigned int len = strlen(string);

	while (bMoreToCome)
	{
		if (len > MAX_MENU_LEN)
			page = LIB_STRING_CLASS::SubStr(string, i*MAX_MENU_LEN, (i+1)*MAX_MENU_LEN);
		else
		{
			bMoreToCome = false;
			page = LIB_STRING_CLASS::SubStr(string, i*MAX_MENU_LEN, strlen(string));
		}

		bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, menuIndex);
		if(!pWrite) return false;
		pWrite->WriteWord(keys); //Sets how many options the menu has
		pWrite->WriteChar(time); //Sets how long the menu stays open -1 for stay until option selected
		pWrite->WriteByte(bMoreToCome ? 0xFF : 0x00); //is there more data to come?
		pWrite->WriteString(page); //The text shown on the menu
		VAR_IFACE_ENGINE->MessageEnd();

		len -= strlen(page);
		delete [] page;
        ++i;
	}
	return true;
}

// Shows a menu to player.
bool LIB_MESSAGE_CLASS::Menu(edict_t *pEntity, int time, const char *msg, int keys /*= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)| (1<<8) | (1<<9)*/, ...)
{
	int menuIndex = GetMsgNum("ShowMenu");
	if(menuIndex == -1) return false;
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;
	MULTIARGS(msg);

	char* page;
	bool bMoreToCome = true;
    int i = 0;
	unsigned int len = strlen(string);

	while (bMoreToCome)
	{
		if (len > MAX_MENU_LEN)
			page = LIB_STRING_CLASS::SubStr(string, i*MAX_MENU_LEN, (i+1)*MAX_MENU_LEN);
		else
		{
			bMoreToCome = false;
			page = LIB_STRING_CLASS::SubStr(string, i*MAX_MENU_LEN, strlen(string));
		}

		bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, menuIndex);
		if(!pWrite) return false;
		pWrite->WriteWord(keys); //Sets how many options the menu has
		pWrite->WriteChar(time); //Sets how long the menu stays open -1 for stay until option selected
		pWrite->WriteByte(bMoreToCome ? 0xFF : 0x00); //is there more data to come?
		pWrite->WriteString(page); //The text shown on the menu
		VAR_IFACE_ENGINE->MessageEnd();

		len -= strlen(page);
		delete [] page;
        ++i;
	}
	return true;
}

// Shows a menu to player.
bool LIB_MESSAGE_CLASS::Menu(edict_t *pEntity, int time, const char *msg, const char *options /*= "0123456789"*/, ...)
{
	return Menu(pEntity, time, msg, MenuOptionsFromString(options));
}

// Print a top message to player.
// Filters allowed
bool LIB_MESSAGE_CLASS::Top(const char *players, int time, const char *msg, int red /*= 255*/, int green /*= 255*/, int blue /*= 255*/, int alpha /*= 255*/, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS2(msg, alpha);

	bool result = Top(mrf, time, string, red, green, blue, alpha);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Print a top message to player.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Top(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *msg, int red /*= 255*/, int green /*= 255*/, int blue /*= 255*/, int alpha /*= 255*/, ...)
{
	if(!mrf.GetRecipientCount()) return false;
	MULTIARGS2(msg, alpha);

	KeyValues *kv = new KeyValues( "msg" );
	kv->SetString( "title", "msg" );
	kv->SetString( "msg", string);
	kv->SetColor( "color", Color( red, green, blue, alpha ));
	kv->SetInt( "level", 5);
	kv->SetInt( "time", time);
	for(int i = 0; i < mrf.GetRecipientCount(); i++)
		VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(mrf.GetRecipientEdict(i), DIALOG_MSG, kv, SERVERPLUGIN_CALLBACKS_VAR);

	kv->deleteThis();
	return true;
}

// Print a top message to player.
bool LIB_MESSAGE_CLASS::Top(edict_t *pEntity, int time, const char *msg, int red /*= 255*/, int green /*= 255*/, int blue /*= 255*/, int alpha /*= 255*/, ...)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	MULTIARGS2(msg, alpha);

	KeyValues *kv = new KeyValues( "msg" );
	kv->SetString( "title", "msg" );
	kv->SetString( "msg", string);
	kv->SetColor( "color", Color( red, green, blue, alpha ));
	kv->SetInt( "level", 5);
	kv->SetInt( "time", time);
	VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(pEntity, DIALOG_MSG, kv, SERVERPLUGIN_CALLBACKS_VAR);

	kv->deleteThis();
	return true;
}

// VGUI_TYPE (1 = special, 2 = url, )
// Sends a VGUI menu to player.
// Filters allowed
bool LIB_MESSAGE_CLASS::VGUI(const char *players, int VGUI_TYPE, const char *title, const char *text, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	MULTIARGS(text);
	
	bool result = VGUI(mrf, VGUI_TYPE, title, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// VGUI_TYPE (1 = special, 2 = url, )
// Sends a VGUI menu to player.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::VGUI(LIB_MRECIPIENTFILTER_CLASS &mrf, int VGUI_TYPE, const char *title, const char *text, ...)
{
	if(!mrf.GetRecipientCount()) return false;
	int vguiIndex = GetMsgNum("VGUIMenu");
	if(vguiIndex == -1) return false;
	
	bf_write *pWrite = VAR_IFACE_ENGINE->UserMessageBegin((IRecipientFilter *) &mrf, vguiIndex);
	if(!pWrite) return false;
	MULTIARGS(text);
	pWrite->WriteString("info"); // the HUD message itself
	pWrite->WriteByte(1);
	pWrite->WriteByte(3); // I don't know yet the purpose of this byte, it can be 1 or 0
	pWrite->WriteString("type"); // the HUD message itself
	pWrite->WriteString(LIB_STRING_CLASS::StrFormat("%i", VGUI_TYPE)); // the HUD message itself
	pWrite->WriteString("title"); // the HUD message itself
	pWrite->WriteString(title); // the HUD message itself

	pWrite->WriteString("msg"); // the HUD message itself
	pWrite->WriteString(string); // the HUD message itself
	VAR_IFACE_ENGINE->MessageEnd();
	return true;
}

// Sends a VGUI menu to player.
bool LIB_MESSAGE_CLASS::VGUI(edict_t *pEntity, int VGUI_TYPE, const char *title, const char *text, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByEntity(pEntity)) return false;

	MULTIARGS(text);
	
	bool result = VGUI(mrf, VGUI_TYPE, title, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Redirect a player to another ip.
// Filters allowed
bool LIB_MESSAGE_CLASS::Redirect(const char *players, int time, const char *ip)
{
#if SOURCE_ENGINE <= SE_DARKMESSIAH
	return false;
#else
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;

	bool result = Redirect(mrf, time, ip);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
#endif
}

// Redirect a player to another ip.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Redirect(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *ip)
{
#if SOURCE_ENGINE <= SE_DARKMESSIAH
	return false;
#else
	int count = mrf.GetRecipientCount();
	if(!count) return false;

	KeyValues *kv = new KeyValues("Redirect");
	kv->SetInt( "time", time );
	kv->SetString( "title", ip );
	for(int i = 0; i < count; i++)
		VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(mrf.GetRecipientEdict(i), (DIALOG_TYPE)DIALOG_ASKCONNECT, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
#endif
}

// Redirect a player to another ip.
bool LIB_MESSAGE_CLASS::Redirect(edict_t *pEntity, int time, const char *ip)
{
#if SOURCE_ENGINE <= SE_DARKMESSIAH
	return false;
#else
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	KeyValues *kv = new KeyValues("Redirect");
	kv->SetInt( "time", time );
	kv->SetString( "title", ip );
	VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(pEntity, DIALOG_ASKCONNECT, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
#endif
}

// Show a RichBox to a player.
// Filers allowed
bool LIB_MESSAGE_CLASS::RichBox(const char *players, int time, const char *title, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS(msg);

	bool result = RichBox(mrf, time, title, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Show a RichBox to a player.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::RichBox(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *title, const char *msg, ...)
{
	int count = mrf.GetRecipientCount();
	if(!count) return false;
	MULTIARGS(msg);

	KeyValues *kv = new KeyValues( "RichBox" );
	kv->SetString( "title", title );
	kv->SetInt( "level", 1 );
	kv->SetInt( "time", time );
	kv->SetString( "msg", string );

	for(int i = 0; i < count; i++)
		VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(mrf.GetRecipientEdict(i), DIALOG_TEXT, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
}

// Show a RichBox to a player.
bool LIB_MESSAGE_CLASS::RichBox(edict_t *pEntity, int time, const char *title, const char *msg, ...)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	MULTIARGS(msg);

	KeyValues *kv = new KeyValues( "RichBox" );
	kv->SetString( "title", title );
	kv->SetInt( "level", 1 );
	kv->SetInt( "time", time );
	kv->SetString( "msg", string );

	VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(pEntity, DIALOG_TEXT, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
}

// Display a Entry box to player.
// Filters allowed
bool LIB_MESSAGE_CLASS::Entry(const char *players, int time, const char *title, const char *cmd, const char *msg, ...)
{
	LIB_MRECIPIENTFILTER_CLASS mrf;
	if(!mrf.AddByFilter(players, false)) return false;
	MULTIARGS(msg);

	bool result = Entry(mrf, time, title, cmd, string);
	mrf.~LIB_MRECIPIENTFILTER_CLASS();

	return result;
}

// Display a Entry box to player.
// You must free MRecipientFilter object yourself
bool LIB_MESSAGE_CLASS::Entry(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *title, const char *cmd, const char *msg, ...)
{
	int count = mrf.GetRecipientCount();
	if(!count) return false;
	MULTIARGS(msg);

	KeyValues *kv = new KeyValues( "Entry" );
	kv->SetString( "title", title );
	kv->SetString( "msg", string );
	kv->SetString( "command", cmd );
	kv->SetInt( "level", 1 );
	kv->SetInt( "time", time );
	for(int i = 0; i < count; i++)
		VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(mrf.GetRecipientEdict(i), DIALOG_ENTRY, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
}

// Display a Entry box to player.
bool LIB_MESSAGE_CLASS::Entry(edict_t *pEntity, int time, const char *title, const char *cmd, const char *msg, ...)
{
	if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity)) return false;
	MULTIARGS(msg);

	KeyValues *kv = new KeyValues( "Entry" );
	kv->SetString( "title", title );
	kv->SetString( "msg", string );
	kv->SetString( "command", cmd );
	kv->SetInt( "level", 1 );
	kv->SetInt( "time", time );
	VAR_IFACE_SERVERPLUGINHELPERS->CreateMessage(pEntity, DIALOG_ENTRY, kv, SERVERPLUGIN_CALLBACKS_VAR);
	kv->deleteThis();
	return true;
}
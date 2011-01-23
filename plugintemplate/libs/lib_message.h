#ifndef LIB_MESSAGE_H
#define LIB_MESSAGE_H
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
#define LIB_MESSAGE_VERSION "1.0"
#define LIB_MESSAGE_CLASS CMessageLib

/*#ifndef DIALOG_ASKCONNECT
#define DIALOG_ASKCONNECT 4		// Im not updating all the sdk around so we do this.
#endif
*/

#define SAY_MAX_COLORS 6
#define SAY_DEFAULT "\x01"
#define SAY_GREEN "\x04"
#define SAY_LIGHTGREEN "\x03"
#define SAY_RED "\x03"
#define SAY_BLUE "\x03"
#define SAY_OLIVE "\x05"

static const char *Say_TagColors[SAY_MAX_COLORS] = {"{default}", "{green}", "{lightgreen}", "{red}", "{blue}", "{olive}"};
static const char *Say_Colors[SAY_MAX_COLORS] = {SAY_DEFAULT, SAY_GREEN, SAY_LIGHTGREEN, SAY_RED, SAY_BLUE, SAY_OLIVE};

//=================================================================================
// Class
//=================================================================================
class LIB_MESSAGE_CLASS
{
public:
	// Get Message Index
	static int GetMsgNum(const char *Msg);

	// Print text to client console.
	// Filters allowed
	static bool CPrint(const char *players, const char *msg, ...);

	// Print text to client console.
	// You must free MRecipientFilter object yourself
	static bool CPrint(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...);

	// Print text to client console.
	static bool CPrint(edict_t *pEntity, const char *msg, ...);

	// Send a message and log.
	static void MsgALog(const char *msg, bool isWarning = false, ...);

	// Shake player screen.
	// Filters allowed
	static bool Shake(const char *players, float fTime = 10, int nType = SHAKE_START, float fMagnitude = 25, float fNoise = 150);

	// Shake player screen.
	// You must free MRecipientFilter object yourself
	static bool Shake(LIB_MRECIPIENTFILTER_CLASS &mrf, float fTime = 10, int nType = SHAKE_START, float fMagnitude = 25, float fNoise = 150);

	// Shake player screen.
	static bool Shake(edict_t *pEntity, float fTime = 10, int nType = SHAKE_START, float fMagnitude = 25, float fNoise = 150);

	// Fade player screen.
	// Filters allowed
	static bool Fade(const char *players, short nFlags = (FFADE_OUT | FFADE_STAYOUT), float fFadeTime = 5, float fHoldTime = 30, int red = 0, int green = 0, int blue = 0, int alpha = 255);

	// Fade player screen.
	// You must free MRecipientFilter object yourself
	static bool Fade(LIB_MRECIPIENTFILTER_CLASS &mrf, short nFlags = (FFADE_OUT | FFADE_STAYOUT), float fFadeTime = 5, float fHoldTime = 30, int red = 0, int green = 0, int blue = 0, int alpha = 255);
	
	// Fade player screen.
	static bool Fade(edict_t *pEntity, short nFlags = (FFADE_OUT | FFADE_STAYOUT), float fFadeTime = 5, float fHoldTime = 30, int red = 0, int green = 0, int blue = 0, int alpha = 255);

	// Send text to player chat.
	// Filters allowed
	static bool Say(const char *players, const char *msg, ...);

	// Send text to player chat.
	// You must free MRecipientFilter object yourself
	static bool Say(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...);

	// Send text to player chat.
	static bool Say(edict_t *pEntity, const char *msg, ...);

	// Escape say colors '\x01' '\x03' '\x04' '\x05'
	// Use only when you need to!
	static void SayEscapeColors(char *str, unsigned int len);

	// Print text to player on center screen.
	// Filters allowed
	static bool CenterSay(const char *players, const char *msg, ...);

	// Print text to player on center screen.
	// You must free MRecipientFilter object yourself
	static bool CenterSay(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...);

	// Print text to player on center screen.
	static bool CenterSay(edict_t *pEntity, const char *msg, ...);

	// Print a hint to player.
	// Filters allowed
	static bool Hint(const char *players, const char *msg, ...);

	// Print a hint to player.
	// You must free MRecipientFilter object yourself
	static bool Hint(LIB_MRECIPIENTFILTER_CLASS &mrf, const char *msg, ...);

	// Print a hint to player.
	static bool Hint(edict_t *pEntity, const char *msg, ...);

	// Transform a numeric string into int keys to use with menus
	// eg. "01239"
	// 0 = 1 Key
	// ...
	// 8 = 9 Key
	// 9 = 0 Key AKA Exit
	// No digit character is ignored
	static int MenuOptionsFromString(const char *options = "0123456789");

	// Shows a menu to player.
	// Allow filters
	static bool Menu(const char *players, int time, const char *msg, const char *options = "0123456789", ...);

	// Shows a menu to player.
	static bool Menu(edict_t *pEntity, int time, const char *msg, int keys = (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)| (1<<8) | (1<<9), ...);

	// Shows a menu to player.
	static bool Menu(edict_t *pEntity, int time, const char *msg, const char *options = "0123456789", ...);

	// Print a top message to player.
	// Filters allowed
	static bool Top(const char *players, int time, const char *msg, int red = 255, int green = 255, int blue = 255, int alpha = 255, ...);

	// Print a top message to player.
	// You must free MRecipientFilter object yourself
	static bool Top(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *msg, int red = 255, int green = 255, int blue = 255, int alpha = 255, ...);

	// Print a top message to player.
	static bool Top(edict_t *pEntity, int time, const char *msg, int red = 255, int green = 255, int blue = 255, int alpha = 255, ...);

	// Sends a VGUI menu to player.
	// Filters allowed
	static bool VGUI(const char *players, int VGUI_TYPE, const char *title, const char *text, ...);

	// VGUI_TYPE (1 = special, 2 = url, )
	// Sends a VGUI menu to player.
	// You must free MRecipientFilter object yourself
	static bool VGUI(LIB_MRECIPIENTFILTER_CLASS &mrf, int VGUI_TYPE, const char *title, const char *text, ...);

	// Sends a VGUI menu to player.
	static bool VGUI(edict_t *pEntity, int VGUI_TYPE, const char *title, const char *text, ...);

	// Redirect a player to another ip.
	// Filters allowed
	static bool Redirect(const char *players, int time, const char *ip);

	// Redirect a player to another ip.
	// You must free MRecipientFilter object yourself
	static bool Redirect(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *ip);

	// Redirect a player to another ip.
	static bool Redirect(edict_t *pEntity, int time, const char *ip);

	// Show a RichBox to a player.
	// Filers allowed
	static bool RichBox(const char *players, int time, const char *title, const char *msg, ...);

	// Show a RichBox to a player.
	// You must free MRecipientFilter object yourself
	static bool RichBox(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *title, const char *msg, ...);

	// Show a RichBox to a player.
	static bool RichBox(edict_t *pEntity, int time, const char *title, const char *msg, ...);

	// Display a Entry box to player.
	// Filters allowed
	static bool Entry(const char *players, int time, const char *title, const char *cmd, const char *msg, ...);

	// Display a Entry box to player.
	// You must free MRecipientFilter object yourself
	static bool Entry(LIB_MRECIPIENTFILTER_CLASS &mrf, int time, const char *title, const char *cmd, const char *msg, ...);

	// Display a Entry box to player.
	static bool Entry(edict_t *pEntity, int time, const char *title, const char *cmd, const char *msg, ...);


};

#endif
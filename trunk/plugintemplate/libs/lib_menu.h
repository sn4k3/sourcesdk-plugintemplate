#ifndef LIB_MENU_H
#define LIB_MENU_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#define LIB_MENU_VERSION "1.0"
#define LIB_MENU_CLASS CMenuLib

class LIB_MENU_CLASS
{
public:
	enum MenuType
	{
		SIMPLE = 0,
		PAGED
	};
	struct PlayerMenuState_t
	{
		int PlayerIndex;
		const char *Menu;
		unsigned int MenuPage;
	};
	struct MenuLine_t
	{
		const char *Text;
		bool Enable;
		void *Argument;
	};
	struct Menu_t
	{
		MenuType Type;
		const char *Name;
		BasicStr Head;
		BasicStr Bottom;
		CUtlVector<MenuLine_t> Lines;
	};

	LIB_MENU_CLASS();
	~LIB_MENU_CLASS();

	// Set sounds for menu actions
	// NULL disable a sound from being played
	// Sounds will not play on SIMPLE menus
	void SetSounds(const char *itemSound, const char *backSound, const char *nextSound, const char *exitSound);

	// Create a new menu
	bool Create(const char *menu, MenuType menuType = SIMPLE, const char *head = NULL, const char *bottom = NULL);

	// Set menu title
	bool SetHead(const char *menu, const char *text);

	// Add a text line to menu
	bool AddLine(const char *menu, const char *text, void *argument = NULL, bool addToTail = true);

	// Add a text line to menu, use that for paged menus
	bool AddLineEx(const char *menu, const char *text, void *argument = NULL, bool enable = true, bool addToTail = true);

	// Set menu bottom
	bool SetBottom(const char *menu, const char *text);

	// Remove a menu
	bool Remove(const char *menu);

	// Get the numer of possible pages on a menu
	unsigned int GetPages(const char *menu);

	// Get number of pages needed for a number of lines
	static unsigned int GetMenuPageFromLines(unsigned int lines);

	// Get menu index
	int GetIndex(const char *menu);

	// Send a menu to a player
	bool Send(edict_t *pEntity, const char *menu, int time = 0, int startFromLine = 1);

	// Check and handle players, when they choose a menu option
	bool ClientCommand_MenuSelected(edict_t *pEntity, int option);

	// Print menu to console
	virtual void Print(const char *menu);

	// Store all menus
	CUtlVector<Menu_t> vec_menus;

	// Player menus
	CUtlVector<PlayerMenuState_t> vec_playermenustate;

	// Options that a menu can hold per page
	// 8 = Back, 9 = Next, 0 = Exit
	static const unsigned int OptionsPerPage = 7;

	static const unsigned int OneOption = 1;
	static const unsigned int TwoOption = 2;
	static const unsigned int ThreeOption = 3;
	static const unsigned int FourOption = 4;
	static const unsigned int FiveOption = 5;
	static const unsigned int SixOption = 6;
	static const unsigned int SevenOption = 7;
	static const unsigned int BackOption = 8;
	static const unsigned int NextOption = 9;
	static const unsigned int ExitOption = 10;

private:
	bool SendPaged(edict_t *pEntity, const char *menu, int time = 0, int page = 1);

	// Create or update player state for a menu
	void CreateOrUpdatePlayerState(edict_t *pEntity, const char *menu, unsigned int menupage);

	char m_ItemSound[512];
	char m_BackSound[512];
	char m_NextSound[512];
	char m_ExitSound[512];
};

extern LIB_MENU_CLASS *VAR_LIB_MENU;

#endif
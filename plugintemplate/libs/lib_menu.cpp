//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_message.h"
#include "libs/lib_player.h"
#include "libs/lib_menu.h"
#include "libs/lib_sound.h"
#include "plugin_gameevents.h"
#include "tier0/memdbgon.h"

LIB_MENU_CLASS::LIB_MENU_CLASS()
{
	memset(m_ItemSound, '\0', sizeof(m_ItemSound));
	memset(m_BackSound, '\0', sizeof(m_BackSound));
	memset(m_NextSound, '\0', sizeof(m_NextSound));
	memset(m_ExitSound, '\0', sizeof(m_ExitSound));
}
LIB_MENU_CLASS::~LIB_MENU_CLASS()
{
	vec_menus.RemoveAll();
	vec_menus.~CUtlVector();
	vec_playermenustate.RemoveAll();
	vec_playermenustate.~CUtlVector();
}

// Set sounds for menu actions
// NULL disable a sound from being played
// Sounds will not play on SIMPLE menus
void LIB_MENU_CLASS::SetSounds(const char *itemSound, const char *backSound, const char *nextSound, const char *exitSound)
{
	if(itemSound)
		strncpy(m_ItemSound, itemSound, sizeof(m_ItemSound));
	else
		memset(m_ItemSound, '\0', sizeof(m_ItemSound));
	if(backSound)
		strncpy(m_BackSound, backSound, sizeof(m_BackSound));
	else
		memset(m_BackSound, '\0', sizeof(m_BackSound));
	if(nextSound)
		strncpy(m_NextSound, nextSound, sizeof(m_NextSound));
	else
		memset(m_NextSound, '\0', sizeof(m_NextSound));
	if(exitSound)
		strncpy(m_ExitSound, exitSound, sizeof(m_ExitSound));
	else
		memset(m_ExitSound, '\0', sizeof(m_ExitSound));
}

// Create a new menu
bool LIB_MENU_CLASS::Create(const char *menu, MenuType menuType /*= SIMPLE*/, const char *head /*= NULL*/, const char *bottom /*= NULL*/)
{
	int index = GetIndex(menu);
	if(index != -1) return false;
	index = vec_menus.AddToTail();
	vec_menus[index].Name = menu;
	vec_menus[index].Type = menuType;
	vec_menus[index].Head = BasicStr(head);
	vec_menus[index].Bottom = BasicStr(bottom);
/*	if(head)
		strncpy(vec_menus[index].Head, head, MAX_MENU_LEN);
	else
		memset(vec_menus[index].Head, '\0', sizeof(vec_menus[index].Head));
	if(bottom)
		strncpy(vec_menus[index].Bottom, bottom, MAX_MENU_LEN);
	else
		memset(vec_menus[index].Bottom, '\0', sizeof(vec_menus[index].Bottom));*/
	return true;
}

// Set menu title
bool LIB_MENU_CLASS::SetHead(const char *menu, const char *text)
{
	int index = GetIndex(menu);
	if(index == -1) return false;
	vec_menus[index].Head = BasicStr(text);
	/*if(text)
		strncpy(vec_menus[index].Head, text, MAX_MENU_LEN);
	else
		memset(vec_menus[index].Head, '\0', sizeof(vec_menus[index].Head));*/
	return true;
}

// Add a text line to menu
bool LIB_MENU_CLASS::AddLine(const char *menu, const char *text, void *argument /*= NULL*/, bool addToTail /*= true*/)
{
	return AddLineEx(menu, text, argument, true, addToTail);
}

// Add a text line to menu, use that for paged menus
bool LIB_MENU_CLASS::AddLineEx(const char *menu, const char *text, void *argument /*= NULL*/, bool enable /*= true*/, bool addToTail /*= true*/)
{
	if(!menu) return false;
	int index = GetIndex(menu);
	if(index == -1) return false;
	MenuLine_t line;
	line.Text = text;
	line.Argument = argument;
	line.Enable = enable;
	if(addToTail)
		vec_menus[index].Lines.AddToTail(line);
	else
		vec_menus[index].Lines.AddToHead(line);
	return true;
}

// Set menu bottom
bool LIB_MENU_CLASS::SetBottom(const char *menu, const char *text)
{
	int index = GetIndex(menu);
	if(index == -1) return false;
	vec_menus[index].Bottom = BasicStr(text);
	/*if(text)
		strncpy(vec_menus[index].Bottom, text, MAX_MENU_LEN);
	else
		memset(vec_menus[index].Bottom, '\0', sizeof(vec_menus[index].Bottom));*/
	return true;
}

// Remove a menu
bool LIB_MENU_CLASS::Remove(const char *menu)
{
	int index = GetIndex(menu);
	if(index == -1) return false;
	vec_menus.Remove(index);
	return true;
}

// Get the numer of possible pages on a menu
unsigned int LIB_MENU_CLASS::GetPages(const char *menu)
{
	int index = GetIndex(menu);
	if(index == -1) return false;
	unsigned int pages = 1;
	int linesCount = vec_menus[index].Lines.Count();
	int check = OptionsPerPage;
	while(check < linesCount)
	{
		check += OptionsPerPage;
		pages++;
	}
	return pages;
}

// Get number of pages needed for a number of lines
unsigned int LIB_MENU_CLASS::GetMenuPageFromLines(unsigned int lines)
{
	unsigned int pages = 1;
	unsigned int check = OptionsPerPage;
	while(check < lines)
	{
		check += OptionsPerPage;
		pages++;
	}
	return pages;
}

// Get menu index
int LIB_MENU_CLASS::GetIndex(const char *menu)
{
	FOR_EACH_VEC(vec_menus, i)
	{
		if(LIB_STRING_CLASS::FStrEq(vec_menus[i].Name, menu))
		{
			return i;
		}
	}
	return -1;
}

// Send a menu to a player
bool LIB_MENU_CLASS::Send(edict_t *pEntity, const char *menu, int time /*= 0*/, int startFromLine /*= 1*/)
{
	if(!LIB_PLAYER_CLASS::IsPlayer(pEntity, true))
		return false;
	int index = GetIndex(menu);
	if(index == -1) return false;
	int linesCount = vec_menus[index].Lines.Count();
	if(startFromLine > linesCount)
		startFromLine = linesCount-OptionsPerPage;
	if(startFromLine <= 0) startFromLine = 1;
	char menuText[MAX_STR_LENGTH];
	if(!vec_menus[index].Head.IsNULL())
	{
		strncat(menuText, vec_menus[index].Head.str, MAX_MENU_LEN);
		strcat(menuText, "\n");
	}
	switch (vec_menus[index].Type)
	{
	case SIMPLE:	
		for(int i = startFromLine-1; i < linesCount; i++)
		{
			strcat(menuText, vec_menus[index].Lines[i].Text);
			strcat(menuText, "\n");
		}
		CreateOrUpdatePlayerState(pEntity, menu, 1);
		break;
	case PAGED:
		return SendPaged(pEntity, menu, time, 1);
		break;
	}
	if(!vec_menus[index].Bottom.IsNULL())
		strcat(menuText, vec_menus[index].Bottom.str);
	return LIB_MESSAGE_CLASS::Menu(pEntity, time, menuText, "0123456789");
}

bool LIB_MENU_CLASS::SendPaged(edict_t *pEntity, const char *menu, int time /*= 0*/, int page /*= 1*/)
{
	int index = GetIndex(menu);
	if(index == -1) return false;
	char menuText[MAX_STR_LENGTH];
	int linesCount = vec_menus[index].Lines.Count();
	if(!vec_menus[index].Head.IsNULL())
	{
		strncat(menuText, vec_menus[index].Head.str, MAX_MENU_LEN);
		strcat(menuText, "\n");
		//strncat_s(menuText, vec_menus[index].Head, MAX_MENU_LEN);
		//strcat_s(menuText, "\n");
	}
	unsigned int menuPages = GetPages(menu);
	unsigned int count = 1;
	int startFromLine = 0;
	if(page > (int)menuPages)
		page = menuPages;
	if(page > 1)
		startFromLine = ((page*OptionsPerPage)-OptionsPerPage);
	else if (page < 1)
		page = 1;
	int menuOptions = 0;
	sprintf(menuText, "%sPage: [%i/%u]\n", menuText, page, menuPages);
	for(int i = startFromLine; i < linesCount; i++)
	{
		if(count > OptionsPerPage)
			break;
		if(vec_menus[index].Lines[i].Enable)
		{
			menuOptions |= 1<<(count-1);
			sprintf(menuText, "%s->%i. %s\n", menuText, count, vec_menus[index].Lines[i].Text);
		}
		else
		{
			sprintf(menuText, "%s%i. %s\n", menuText, count, vec_menus[index].Lines[i].Text);
		}
		count++;
	}
	if(page > 1)
	{
		strcat(menuText, " \n->8. Back");
		menuOptions |= 1<<(BackOption-1);
	}
	else
	{
		strcat(menuText, " \n8. Back");
	}
	if(page < (int)menuPages)
	{
		strcat(menuText, "\n->9. Next");
		menuOptions |= 1<<(NextOption-1);
	}
	else
	{
		strcat(menuText, "\n9. Next");
	}
	strcat(menuText, "\n0. Exit");
	menuOptions |= 1<<(ExitOption-1);
	if(!vec_menus[index].Bottom.IsNULL())
		strcat(menuText, vec_menus[index].Bottom.str);
	CreateOrUpdatePlayerState(pEntity, menu, page);
	return LIB_MESSAGE_CLASS::Menu(pEntity, time, menuText, menuOptions);
}

// Check and handle players, when they choose a menu option
bool LIB_MENU_CLASS::ClientCommand_MenuSelected(edict_t *pEntity, int option)
{
	if(option < 1 || option > 10)
		return false;
	int playerindex = IndexOfEdict(pEntity);
	if(playerindex < 0) return false;
	FOR_EACH_VEC(vec_playermenustate, i)
	{
		if(vec_playermenustate[i].PlayerIndex == playerindex)
		{
			if(!vec_playermenustate[i].Menu) return false;
			int index = GetIndex(vec_playermenustate[i].Menu);
			if(index == -1) return false;
			switch(vec_menus[index].Type)
			{
			case SIMPLE:
				VAR_PLUGIN_GAMEEVENTS->FireMenuHandle(vec_playermenustate[i].Menu, pEntity, option, vec_playermenustate[i].MenuPage, NULL);
				vec_playermenustate.Remove(i);
				return true;
			case PAGED:
				if(option > 0 && option <= (int)OptionsPerPage)
				{
					if(m_ItemSound)
						LIB_SOUND_CLASS::Play(pEntity, m_ItemSound);
					int lineindex = (OptionsPerPage * (vec_playermenustate[i].MenuPage-1)) + option - 1; // Calculate line index
					bool useargument = (lineindex >= 0 && lineindex < vec_menus[index].Lines.Count());
					VAR_PLUGIN_GAMEEVENTS->FireMenuHandle(vec_playermenustate[i].Menu, pEntity, option, vec_playermenustate[i].MenuPage, useargument ? vec_menus[index].Lines[lineindex].Argument : NULL);
					vec_playermenustate.Remove(i);
					return true;
				}
				if(option == (int)BackOption)
				{
					if(m_BackSound)
						LIB_SOUND_CLASS::Play(pEntity, m_BackSound);
					SendPaged(pEntity, vec_playermenustate[i].Menu, 0, vec_playermenustate[i].MenuPage-1);
					return true;
				}
				if(option == (int)NextOption)
				{
					if(m_NextSound)
						LIB_SOUND_CLASS::Play(pEntity, m_NextSound);
					SendPaged(pEntity, vec_playermenustate[i].Menu, 0, vec_playermenustate[i].MenuPage+1);
					return true;
				}
				if(option == (int)ExitOption)
				{
					if(m_ExitSound)
						LIB_SOUND_CLASS::Play(pEntity, m_ExitSound);
					vec_playermenustate.Remove(i);
					return true;
				}
				return true;
			}
			return false;
		}
	}
	return false;
}

// Create or update player state for a menu
void LIB_MENU_CLASS::CreateOrUpdatePlayerState(edict_t *pEntity, const char *menu, unsigned int menupage)
{
	int playerindex = IndexOfEdict(pEntity);
	if(playerindex < 0) return;
	FOR_EACH_VEC(vec_playermenustate, i)
	{
		if(vec_playermenustate[i].PlayerIndex == playerindex)
		{
			vec_playermenustate[i].Menu = menu;
			vec_playermenustate[i].MenuPage = menupage;
			return;
		}
	}
	PlayerMenuState_t playerstate;
	playerstate.PlayerIndex = playerindex;
	playerstate.Menu = menu;
	playerstate.MenuPage = menupage;
	vec_playermenustate.AddToTail(playerstate);
}


// Print menu to console
void LIB_MENU_CLASS::Print(const char *menu)
{
	int index = GetIndex(menu);
	if(index == -1) return;
	Msg("Menu: %s\nLines: %i\n \n", menu, vec_menus[index].Lines.Count());
	if(!vec_menus[index].Head.IsNULL())
		Msg("%s\n", vec_menus[index].Head.str);
	FOR_EACH_VEC(vec_menus[index].Lines, i)
	{
		Msg("%s\n", vec_menus[index].Lines[i].Text);
	}
	if(!vec_menus[index].Bottom.IsNULL())
		Msg("%s\n", vec_menus[index].Bottom.str);
}


LIB_MENU_CLASS *VAR_LIB_MENU = NULL;

//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================
//
// Mani Admin Plugin
//
// Copyright (c) 2010 Giles Millward (Mani). All rights reserved.
//
// This file is part of ManiAdminPlugin.
//
// Mani Admin Plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Mani Admin Plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Mani Admin Plugin.  If not, see <http://www.gnu.org/licenses/>.
//

#define LIB_LINUXUTILS_VERSION "1.0"
#define LIB_LINUXUTILS_CLASS CLIB_LINUXUTILS_CLASS

#if !defined ( WIN32 )
#ifndef LIB_LINUXUTILS_H
#define LIB_LINUXUTILS_H

struct symbol_t
{
        void *ptr;
        char *mangled_name;
        char *demangled_name;
};

class LIB_LINUXUTILS_CLASS
{
public:

	LIB_LINUXUTILS_CLASS();
	~LIB_LINUXUTILS_CLASS();

	static void GetLinuxBins(char *game, char *engine);
	static void GetLinuxBins();
	bool GetLib(const char *lib_name);
	symbol_t *GetAddr(void *ptr);
	symbol_t *GetAddr(int index);

	symbol_t *GetMangled(char *mangled_name);
	symbol_t *GetMangled(int index);

	symbol_t *GetDeMangled(char *demangled_name);
	symbol_t *GetDeMangled(int index);

	int GetMapSize() { return symbol_list_size; };
	void *FindAddress(char *name_ptr);
	
private:
	void FreeSymbols();

	// This is the main unsorted list
	symbol_t *addr_list;
	symbol_t *mangled_list;
	symbol_t *demangled_list;
	int    symbol_list_size;
};

extern char		linux_game_bin[256];
extern char		linux_engine_bin[256];

#endif
#endif // !defined WIN32
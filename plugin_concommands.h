#ifndef PLUGIN_CONCOMMANDS_H
#define PLUGIN_CONCOMMANDS_H
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
#define PLUGIN_CONCOMMANDS_VERSION "1.0"
#define PLUGIN_CONCOMMANDS_CLASS CPluginConCommands


//=================================================================================
// Usefull Macros
//=================================================================================
#if SOURCE_ENGINE <= SE_DARKMESSIAH
#define PLUGIN_CON_COMMAND( name, description ) \
   static void name(); \
   static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description ); \
   static void name()

#define PLUGIN_CON_COMMAND_F( name, description, flags ) \
   static void name(); \
   static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description, flags ); \
   static void name()

#define PLUGIN_CON_COMMAND_F_COMPLETION( name, description, flags, completion ) \
	static void name(); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description, flags, completion ); \
	static void name()

#define PLUGIN_CON_COMMAND_EXTERN( name, _funcname, description ) \
	void _funcname(); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", _funcname, description ); \
	void _funcname()

#define PLUGIN_CON_COMMAND_EXTERN_F( name, _funcname, description, flags ) \
	void _funcname(); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", _funcname, description, flags ); \
	void _funcname()
#else
#define PLUGIN_CON_COMMAND( name, description ) \
   static void name( const CCommand &args ); \
   static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description ); \
   static void name( const CCommand &args )

#define PLUGIN_CON_COMMAND_F( name, description, flags ) \
   static void name( const CCommand &args ); \
   static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description, flags ); \
   static void name( const CCommand &args )

#define PLUGIN_CON_COMMAND_F_COMPLETION( name, description, flags, completion ) \
	static void name( const CCommand &args ); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", name, description, flags, completion ); \
	static void name( const CCommand &args )

#define PLUGIN_CON_COMMAND_EXTERN( name, _funcname, description ) \
	void _funcname( const CCommand &args ); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", _funcname, description ); \
	void _funcname( const CCommand &args )

#define PLUGIN_CON_COMMAND_EXTERN_F( name, _funcname, description, flags ) \
	void _funcname( const CCommand &args ); \
	static ConCommand PLUGIN_CONCOMMAND_PREFIX##name( ""PLUGIN_CONCOMMAND_NAME_PREFIX""#name"", _funcname, description, flags ); \
	void _funcname( const CCommand &args )
#endif

#define REGISTER_CONCOMMAND(name) \
	VAR_PLUGIN_CONVARS->concommands[#name] = &PLUGIN_CONCOMMAND_PREFIX##name;

//=================================================================================
// Class
//=================================================================================
class PLUGIN_CONCOMMANDS_CLASS
{

};

#endif
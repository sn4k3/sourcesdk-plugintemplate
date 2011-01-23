

Understanding game configs:

common.txt loads in every game
once it loads, game config will load ie. cstrike.txt

If cstrike have a sigscan or a vfunc with same name in common.txt, offsets will be replaced with the cstrike ones

KeyValue file must have that format:

"Game Name"
{
	"GamePlayer"	"CSSPlayer"
	
	"SigScan"
	{
		"CLASS::NAME OR NAME"
		{
			"sig"		"53 68 ? ? ? ? 6A 00 B9 ? ? ? ? 32 DB"
			"symbol"	"_LinuxSymbol"
			"enable"	"1 or 0"
		}
	}
	"VFuncs"
	{
		"CLASS::NAME OR NAME"
		{
			"windows"	"95"
			"linux"		"100"
			"enable"	"1 or 0"
		}
	}
}

Understanding file format:

@ GamePlayer = Each game change the game player name ie. CCSPlayer, CDODPlayer, CHL2MP_Player, CTFPlayer
               So if you name a vfunc as CCSPlayer::GiveNamedItem for cstrike and CDODPlayer::GiveNamedItem for dods, you must compare the game and call correct function
			   So so can go simple and do on your plugin: "%s::GiveNamedItem" %s will got replaced by the GamePlayer
			   Otherwise i recommend you name your vfunc as: CBaseEntity::GiveNamedItem or more simple: GiveNamedItem, names are only names, and you can set them as you want
			   You can skip this, but i recommend that you set the correct game player

@ SigScan - http://wiki.alliedmods.net/Signature_Scanning

@@ sig = (WINDOWS) Pair of bytes, extract hex bytes from a dissambler, ie. IDA
         There are no manual mask here, to use WildCard use '?' where it should be 0x2A
		 
@@ symbol = (LINUX) Linux symbol, easy to get, just open server.so with a dissambler, ie. IDA, you will get the name list, just extract the symbol

@@ enable = If enable is set to 0 plugin will skip from search for the signature
            If enable key was not present, plugin will considere as enabled

@ VFuncs - http://wiki.alliedmods.net/Virtual_Offsets_(Source_Mods)

@@ windows = Windows offset, for the named virtual function

@@ linux = Linux offset, for the named virtual function
           If linux key was not present, offset will be equal to: windows+1, because linux offsets are 1 greater than windows (Not all)
		   
@@ enable = If enable is set to 0 plugin will not store vfunc name and offset, that prevents plugin from use the vfunc
            If enable key was not present, plugin will considere as enabled
#ifndef INCLUDES_DEFAULT_H
#define INCLUDES_DEFAULT_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#include "includes/precommun.h"

#include "interface.h"
#include "filesystem.h"
#include "shake.h"
#include "engine/iserverplugin.h"
#include "iplayerinfo.h"
#include "eiface.h"
#include "igameevents.h"
#include "convar.h"
#include "Color.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"
#include "tier2/tier2.h"
#include "ctype.h"
#include "networkstringtabledefs.h"
#include "UtlStringMap.h"
#include "utlmap.h"
#include "shareddefs.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "engine/IEngineSound.h"
#include "bitbuf.h"
#include "inetchannelinfo.h"
#include "inetchannel.h"
#include "iclient.h"
#include "iserver.h"
#include "ivoiceserver.h"
#include "IEffects.h"

#include "itempents.h"

#include <KeyValues.h>

#include "externlibs/Callback.h"
#include "serverplugin/serverplugin_engine.h"
#include "libs/lib_string.h"
#include "libs/lib_entity.h"
#include "libs/MRecipientFilter.h"
#include "libs/lib_globals.h"
#ifndef NO_INCLUDE_LIBRARIES
#include "includes/sufcommun.h"
#endif

#endif
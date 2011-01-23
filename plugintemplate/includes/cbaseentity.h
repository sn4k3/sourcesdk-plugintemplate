#ifndef INCLUDES_CBASEENTITY_H
#define INCLUDES_CBASEENTITY_H
//========= Copyright � 2010-2011, Tiago Concei��o, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

#include "includes/precommun.h"

#define GAME_DLL 1
#include "cbase.h"
#include "globalstate.h"
#include "isaverestore.h"
#include "client.h"
#include "decals.h"
#include "gamerules.h"
#include "entityapi.h"
#include "entitylist.h"
#include "eventqueue.h"
#include "hierarchy.h"
#include "basecombatweapon.h"
#include "const.h"
#include "player.h"
#include "ndebugoverlay.h"
#include "physics.h"
#include "model_types.h"
#include "team.h"
#include "sendproxy.h"
#include "IEffects.h"
#include "vstdlib/random.h"
#define GAME_DLL 1
#include "networkvar.h"
#include "baseentity.h"
#include "collisionutils.h"
#include "coordsize.h"
#include "strtools.h"
#include "engine/IEngineSound.h"
#include "physics_saverestore.h"
#include "saverestore_utlvector.h"
#include "bone_setup.h"
#include "vcollide_parse.h"
#include "filters.h"
#include "te_effect_dispatch.h"
#include "AI_Criteria.h"
#include "AI_ResponseSystem.h"
#include "world.h"
#include "globals.h"
#include "saverestoretypes.h"
#include "SkyCamera.h"
#include "sceneentity.h"
#include "game.h"
#include "tier0/vprof.h"
#ifndef __linux__
#include "ai_basenpc.h"
#endif
#include "iservervehicle.h"
#include "eventlist.h"
#include "scriptevent.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "UtlCachedFileData.h"
#include "utlbuffer.h"
#include "positionwatcher.h"
#include "movetype_push.h"
#include "icommandline.h"
#include "vphysics/friction.h"
#include "engine/iserverplugin.h"
#include "iplayerinfo.h"
#include "UtlStringMap.h"
#include "utlmap.h"

#ifndef NO_INCLUDE_LIBRARIES
#include "includes/sufcommun.h"
#endif

#endif
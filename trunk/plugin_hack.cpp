//=================================================================================
// Includes
//=================================================================================
#include "includes/default.h"
#include PLUGIN_MAIN_INCLUDE

//=================================================================================
//									Props Class
// Write your own functions
// Access to functions using: VAR_LIB_HACK
//=================================================================================
PLUGIN_PROP_CLASS::PLUGIN_PROP_CLASS(){}
PLUGIN_PROP_CLASS::~PLUGIN_PROP_CLASS(){}

//=================================================================================
//									VFuncs Class
// Write your own functions
// Access to functions using: VAR_LIB_HACK
//=================================================================================

//=================================================================================
// Constructor / Destructor
//=================================================================================
PLUGIN_VFUNCS_CLASS::PLUGIN_VFUNCS_CLASS(){}
PLUGIN_VFUNCS_CLASS::~PLUGIN_VFUNCS_CLASS(){}

//=================================================================================
// Functions
//=================================================================================

/* .ie REMOVE ME, see lib_vfuncs.cpp and lib_vfuncs.h
* Teleports a entity
* virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
*bool PLUGIN_VFUNCS_CLASS::CBaseEntity_Teleport(edict_t *pEntity, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName)
*{
*	return CBaseEntity_Teleport(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), newPosition, newAngles, newVelocity, addressName);
*}

* Teleports a entity
* virtual void	Teleport( const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity );
*bool PLUGIN_VFUNCS_CLASS::CBaseEntity_Teleport(CBaseEntity *pBase, const Vector *newPosition, const QAngle *newAngles, const Vector *newVelocity, const char *addressName)
{
	VFUNC_ASSERT_FUNCTION("CBaseEntity::Teleport", false)
	VFUNC_3(pBase, iOffset, , void, const Vector *, newPosition, const QAngle *, newAngles, const Vector *, newVelocity)
	return true;
}
*/

//=================================================================================
//									SigScan Class
// Write your own functions
// Access to functions using: VAR_LIB_HACK
//=================================================================================

//=================================================================================
// Constructor / Destructor
//=================================================================================
PLUGIN_SIGSCAN_CLASS::PLUGIN_SIGSCAN_CLASS(){}
PLUGIN_SIGSCAN_CLASS::~PLUGIN_SIGSCAN_CLASS(){}

//=================================================================================
// Functions
//=================================================================================

/* .ie REMOVE ME, See lib_sigscan.cpp and lib_sigscan.h
* Respawn a player (CSS)
* void RoundRespawn(void);
*bool LIB_SIGSCAN_CLASS::CSSPlayer_RoundRespawn(edict_t *pEntity, const char *addressName)
*{
*	return CSSPlayer_RoundRespawn(LIB_ENTITY_CLASS::GetBaseEntityfromEntity(pEntity), addressName);
*}
*
* Respawn a player (CSS)
* void RoundRespawn(void);
*bool LIB_SIGSCAN_CLASS::CSSPlayer_RoundRespawn(CBaseEntity *pBase, const char *addressName)
*{
*	SIGSCAN_ASSERT_FUNCTION("CSSPlayer::RoundRespawn", false)
*	SIGSCAN_0(pBase, pAddr, , void);
*	return true;
*}
*/
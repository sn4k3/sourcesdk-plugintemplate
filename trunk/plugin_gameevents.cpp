//=================================================================================
// Includes
//=================================================================================
#include "includes/default.h"
#include PLUGIN_MAIN_INCLUDE

//=================================================================================
// Constructor/Destructor
//=================================================================================
PLUGIN_GAMEEVENTS_CLASS::PLUGIN_GAMEEVENTS_CLASS(){}
PLUGIN_GAMEEVENTS_CLASS::~PLUGIN_GAMEEVENTS_CLASS(){}

//=================================================================================
// Functions
//=================================================================================
void PLUGIN_GAMEEVENTS_CLASS::FireGameEvent(IGameEvent *event)
{
	const char *name = event->GetName();
	if(LIB_STRING_CLASS::FStrEq(name, "round_end"))
	{
#ifdef USE_LIB_TIMER
		VAR_LIB_TIMER->RemoveRoundEndTimers();
#endif
		return;
	}
}

void PLUGIN_GAMEEVENTS_CLASS::FireMenuHandle(const char *menu, edict_t *pEntity, unsigned int option, unsigned int page, void *arg)
{
	Msg("Menu %s got a click in slot %u on the %u page\n", menu, option, page);
	if(arg != NULL)
	{
		Msg("Argument: %s\n", arg);
	}
}

//=================================================================================
// Global variable, never touch
//=================================================================================
PLUGIN_GAMEEVENTS_CLASS *VAR_PLUGIN_GAMEEVENTS;
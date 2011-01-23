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
// Includes
//=================================================================================
#include "includes/default.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
// Constructor
LIB_TIMERINFO_CLASS::LIB_TIMERINFO_CLASS(const char *name, float time, unsigned int repeats /*= 0*/, bool removeAtRoundEnd /*= false*/)
{
	Reset();
	this->startTime = VAR_IFACE_ENGINE->Time();
	this->name = name;
	this->time = time;
	this->repeats = repeats;
	this->removeAtRoundEnd = removeAtRoundEnd;
	sender = name;
	//i_CallbackOutput.SetCallback5(VAR_PLUGIN_TIMERS, &LIB_TIMERIMPL_CLASS::TimerCallback);
}

// Destructor, clean all resources.
LIB_TIMERINFO_CLASS::~LIB_TIMERINFO_CLASS()
{
	Reset();
	sender = NULL;
	if(Param1)
		free(Param1);
	if(Param2)
	{
		Param2->RemoveAll();
		Param2->~CUtlVector();
	}
	if(Param3)
	{
		Param3->RemoveAll();
		Param3->~CUtlVector();
	}
	Param4 = 0;
	//i_CallbackOutput;
}

//=================================================================================
// Reset
//=================================================================================
// Set timer back to original.
// NEVER RUN DIRECTLY
void LIB_TIMERINFO_CLASS::Reset()
{
	name = NULL;
	time = 0;
	startTime = 0;
	repeats = 0;
	repeatsCount = 0;
	removeAtRoundEnd = false;
	
	sender = name;
	Param1 = NULL;
	Param2 = NULL;
	Param3 = NULL;
	Param4 = 0;
}

// Set callback arguments.
void LIB_TIMERINFO_CLASS::SetArguments(void *Param1 /*= NULL*/, CUtlVector<void *>* Param2 /*= NULL*/, CUtlVector<void *>* Param3 /*= NULL*/, int Param4 /*= 0*/)
{
	this->Param1 = Param1;
	this->Param2 = Param2;
	this->Param3 = Param3;
	this->Param4 = Param4;
}

// Execute callback.
// Note: NEVER RUN DIRECTLY.
void LIB_TIMERINFO_CLASS::CallCallback()
{
	//i_CallbackOutput.Execute5(sender, Param1, Param2, Param3, Param4);
	VAR_PLUGIN_TIMERS->TimerCallback(sender, Param1, Param2, Param3, Param4);
}


//=================================================================================
// CLASS LIB_TIMER_CLASS
//=================================================================================
// Constructor
LIB_TIMER_CLASS::LIB_TIMER_CLASS(){}
// Destructor
LIB_TIMER_CLASS::~LIB_TIMER_CLASS(){}

// Reset Timers.
void LIB_TIMER_CLASS::Reset()
{
	FOR_EACH_VEC(vec_timers, i)
	{
		vec_timers[i]->~LIB_TIMERINFO_CLASS();
	}
	vec_timers.RemoveAll();
}

// Add a named timer to list.
// Time is in seconds.
bool LIB_TIMER_CLASS::Add(const char *name, float time, unsigned int repeats /*= 0*/, bool removeAtRoundEnd /*= false*/, void *Param1 /*= NULL*/, CUtlVector<void *>* Param2 /*= NULL*/, CUtlVector<void *>* Param3 /*= NULL*/, int Param4 /*= 0*/)
{
	if(GetIndex(name) != -1)
		return false;
	if (time < 0.1f) time = 0.1f;
	LIB_TIMERINFO_CLASS *timer = new LIB_TIMERINFO_CLASS(name, time, repeats, removeAtRoundEnd);
	timer->SetArguments(Param1, Param2, Param3, Param4);
	vec_timers.AddToTail(timer);
	return true;
}

// Remove a timer by name.
// Returns false, if name doesnt't exists.
bool LIB_TIMER_CLASS::Remove(const char *name)
{
	int index = GetIndex(name);
	if(index == -1)
		return false;
	return Remove(index);
}

// Remove a timer by index.
// Returns false, if index doesnt't exists.
bool LIB_TIMER_CLASS::Remove(int index)
{
	if (index < 0 || index >= vec_timers.Count())
		return false;

	vec_timers[index]->~CTimerInfo();
	vec_timers.Remove(index);
	return true;
}

// Remove all timers, flagged with round end.
// Return the number of removed timers.
unsigned int LIB_TIMER_CLASS::RemoveRoundEndTimers()
{
	unsigned int num = 0;
	FOR_EACH_VEC(vec_timers, i)
	{
		if(vec_timers[i]->removeAtRoundEnd)
		{
			vec_timers.Remove(i);
			num++;
		}
	}
	return num;
}

// Loop all timers and execute ready timers.
// Call on GameFrame.
void LIB_TIMER_CLASS::CheckTimers()
{
	float time = VAR_IFACE_ENGINE->Time(); //effects->Time();
	
	FOR_EACH_VEC(vec_timers, i)
	{
		if ((time - vec_timers[i]->startTime) >= vec_timers[i]->time)
		{
			ExecuteTimer(i);
		}
    }
}

// Execute timer, INTERNAL
void LIB_TIMER_CLASS::ExecuteTimer(int id)
{ 
	if (id < 0 || id >= vec_timers.Count())
		return;

	bool removeit = true;
		   
	LIB_TIMERINFO_CLASS* timer = vec_timers[id];
	if(timer->repeats > 0)
	{
		if(timer->repeats > timer->repeatsCount)
		{
			vec_timers[id]->startTime = VAR_IFACE_ENGINE->Time();
			vec_timers[id]->repeatsCount++;
			removeit = false; // Continue the repeats
		}
	}
	if(removeit)
		vec_timers.Remove(id);
		
	// Tigger callback here	
	timer->CallCallback();
	
	if (removeit)
		timer->~CTimerInfo();
}

// Get timer index from name.
// Returns -1 on invalid name.
int LIB_TIMER_CLASS::GetIndex(const char *name)
{
	FOR_EACH_VEC(vec_timers, i)
	{
		if (!strcmp(vec_timers[i]->GetName(), name))
			return i;
	}
	return -1;
}

// Check if a timer name exists.
bool LIB_TIMER_CLASS::Exists(const char *name)
{
	return GetIndex(name) != -1;
}

// Get a CTimerInfo from name.
// Returns NULL on invalid name.
LIB_TIMERINFO_CLASS *LIB_TIMER_CLASS::GetTimer(const char *name)
{
	int index = GetIndex(name);
	return index == -1 ? NULL : vec_timers[index];
}

// Get how many repeats left for timer end.
// Returns -1 on invalid name.
int LIB_TIMER_CLASS::GetRepeatsLeft(const char *name)
{
	int index = GetIndex(name);
	return index == -1 ? -1 : vec_timers[index]->GetRepeatsLeft();
}

//=================================================================================
// CLASS LIB_TIMERIMPL_CLASS
//=================================================================================
LIB_TIMERIMPL_CLASS::LIB_TIMERIMPL_CLASS(){}
LIB_TIMERIMPL_CLASS::~LIB_TIMERIMPL_CLASS(){}

/*bool LIB_TIMERIMPL_CLASS::TimerCallback(void *sender, void *Param1, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4)
{
	return TimerCallback((const char*)sender, Param1, Param2, Param3, Param4);
}*/

// Check GameFrame
#ifdef SOURCEMM
#ifdef WIN32
#ifdef USE_LIB_TIMER
#ifndef SM_HOOK_PLUGINCALLBACK_GAMEFRAME
#pragma message("WARNING: You are using CTimerLib class, to ensure timers work, you need to enable GameFrame callback with MMS.")
#pragma message("       : Go to configs/sourcemm_config.h and enable SM_HOOK_PLUGINCALLBACK_GAMEFRAME")
#endif
#endif
#endif
#endif

LIB_TIMER_CLASS *VAR_LIB_TIMER = NULL;
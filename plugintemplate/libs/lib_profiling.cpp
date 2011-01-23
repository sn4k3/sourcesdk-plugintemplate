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
#define NO_INCLUDE_LIBRARIES
#include "includes/default.h"
#include "libs/lib_profiling.h"
#include "tier0/memdbgon.h"

//=================================================================================
// Constructor / Destructor
//=================================================================================
// Constructor
// Set 'startNow' to true, to start profiling
// name does nothing, its just to name your profiling func if you want
LIB_PROFILINGDATA_CLASS::LIB_PROFILINGDATA_CLASS(bool startNow /*= true*/, const char *name /*= NULL*/)
{
	Reset();
	szname = name;
	if(startNow)
		Start();
}

// Destructor
LIB_PROFILINGDATA_CLASS::~LIB_PROFILINGDATA_CLASS(void)
{
	Reset();
}

//=================================================================================
// Functions
//=================================================================================
// Reset class as a new instance
void LIB_PROFILINGDATA_CLASS::Reset()
{
	szname = NULL;
	b_isstarted = false;
	b_isfinished = false;
	f_starttime = 0;
	f_endtime = 0;
}

// Start a profiling
// If force is true, resets the current/finished profiling
bool LIB_PROFILINGDATA_CLASS::Start(bool force /*= false*/)
{
	if(b_isstarted)
		if(!force)
			return false;
	b_isstarted = true;
	b_isfinished = false;
	f_starttime = VAR_IFACE_ENGINE->Time();
	f_endtime = 0;
	return true;
}

// Stops a profiling
// Returns -1, if profiling was not started, otherwise returns time taken, in seconds
float LIB_PROFILINGDATA_CLASS::Stop()
{
	if(!b_isstarted)
			return -1;
	f_endtime = VAR_IFACE_ENGINE->Time();
	b_isstarted = false; // ready to use again
	b_isfinished = true;
	return f_endtime-f_starttime;
}

// Get profiling time taken in seconds
// If mustFinish is true then profiling must be finished fist to obtain time, otherwise return time util now.
// Returns -1 if profiling not started yet
float LIB_PROFILINGDATA_CLASS::GetTime(bool mustFinish /*= false*/)
{
	if(!b_isstarted)
			return -1;
	if(!b_isfinished)
		if(!mustFinish)
			return VAR_IFACE_ENGINE->Time()-f_starttime;
	return f_endtime-f_starttime;
}


//=================================================================================
// CLASS CProfilingLib
//=================================================================================

// Get wrapper
LIB_PROFILINGDATA_CLASS *LIB_PROFILING_CLASS::operator[](const char *name)
{
	return Get(name);
}

// Add a profiling function to list.
// Returns false if alread exist one with same name.
bool LIB_PROFILING_CLASS::Add(const char *name, bool startNow /*= true*/)
{
	if(Exists(name)) return false;
	LIB_PROFILINGDATA_CLASS *profile = new LIB_PROFILINGDATA_CLASS(startNow, name);
	v_profiling.AddToTail(profile);
	return true;
}

// Remove a profiling functions from list.
bool LIB_PROFILING_CLASS::Remove(const char *name)
{
	int index = GetIndex(name);
	if(index == -1) return false;
	v_profiling[index]->~CProfilingData();
	v_profiling.Remove(index);
	return true;
}

// Remove all profiling function from list.
void LIB_PROFILING_CLASS::RemoveAll()
{
	FOR_EACH_VEC(v_profiling, i)
	{
		v_profiling[i]->~CProfilingData();
	}
	v_profiling.RemoveAll();
}

// Get a named CProfilingData instance from list.
LIB_PROFILINGDATA_CLASS *LIB_PROFILING_CLASS::Get(const char *name)
{
	int index = GetIndex(name);
	if(index == -1) return false;
	return v_profiling[index];
}

// Get profiling index from name.
int LIB_PROFILING_CLASS::GetIndex(const char *name)
{
	FOR_EACH_VEC(v_profiling, i)
	{
		if(v_profiling[i]->GetName() == name)
			return i;
	}
	return -1;
}

// Check if a profiling name exists.
int LIB_PROFILING_CLASS::Exists(const char *name)
{
	return GetIndex(name) != -1;
}

// Get how many profiling functions there are in list.
int LIB_PROFILING_CLASS::Count() const
{
	return v_profiling.Count();
}

LIB_PROFILING_CLASS *VAR_LIB_PROFILING = NULL;
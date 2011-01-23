#ifndef LIB_PROFILING_H
#define LIB_PROFILING_H
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
#define LIB_PROFILING_VERSION "1.0"
#define LIB_PROFILING_CLASS CProfilingLib

#define LIB_PROFILINGDATA_CLASS CProfilingData

//=================================================================================
// Class
//=================================================================================
// Profiling class
class LIB_PROFILINGDATA_CLASS
{
public:
	// Constructor
	// Set 'startNow' to true, to start profiling
	// name does nothing, its just to name your profiling func if you want
	LIB_PROFILINGDATA_CLASS(bool startNow = true, const char *name = NULL);

	// Destructor
	~LIB_PROFILINGDATA_CLASS(void);

	// Reset class as a new instance
	void Reset();

	// Start a profiling
	// If force is true, resets the current/finished profiling
	bool Start(bool force = false);

	// Stops a profiling
	// Returns -1, if profiling was not started, otherwise returns time taken, in seconds
	float Stop();

	// Get profiling time taken in seconds
	// If mustFinish is true then profiling must be finished fist to obtain time, otherwise return time util now.
	// Returns -1 if profiling not started yet
	float GetTime(bool mustFinish = false);

	// Set profiling name
	// name does nothing, its just to name your profiling func if you want
	inline void SetName(const char *name){
		szname = name;
	}

	// Get profiling name
	inline const char *GetName(){
		return szname;
	}

	// Does profiling already start?
	inline bool IsStarted(){
		return b_isstarted;
	}

	// Does profiling already finish?
	inline bool IsFinished(){
		return b_isfinished;
	}

private:
	const char *szname;

	bool b_isstarted;
	bool b_isfinished;

	float f_starttime;
	float f_endtime;
};

//=================================================================================
// Class
//=================================================================================
// Provide a collection of CProfilingData
class LIB_PROFILING_CLASS
{
public:
	// Get wrapper
	LIB_PROFILINGDATA_CLASS *operator[](const char *name);

	// Add a profiling function to list.
	// Returns false if alread exist one with same name.
	bool Add(const char *name, bool startNow = true);

	// Remove a profiling function from list.
	bool Remove(const char *name);

	// Remove all profiling functions from list.
	void RemoveAll();

	// Get a named CProfilingData instance from list.
	LIB_PROFILINGDATA_CLASS *Get(const char *name);

	// Get profiling index from name.
	int GetIndex(const char *name);

	// Check if a profiling name exists.
	int Exists(const char *name);

	// Get how many profiling functions there are in list.
	int Count() const;

private:
	CUtlVector<LIB_PROFILINGDATA_CLASS *> v_profiling;
};

extern LIB_PROFILING_CLASS *VAR_LIB_PROFILING;


#endif

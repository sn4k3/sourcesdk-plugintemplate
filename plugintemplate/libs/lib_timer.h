#ifndef LIB_TIMER_H
#define LIB_TIMER_H
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
#define LIB_TIMER_VERSION "1.0"
#define LIB_TIMER_CLASS CTimerLib

#define LIB_TIMERINFO_CLASS CTimerInfo
#define LIB_TIMERIMPL_CLASS CTimerImpl

//=================================================================================
// CLASS LIB_TIMERINFO_CLASS
//=================================================================================
class LIB_TIMERINFO_CLASS
{
public:
	// Constructor
	LIB_TIMERINFO_CLASS(const char *name, float time, unsigned int repeats = 0, bool removeAtRoundEnd = false);

	// Destructor, clean all resources.
	~LIB_TIMERINFO_CLASS();

	// Set timer back to original.
	// NEVER RUN DIRECTLY
	void Reset();

	// Set callback arguments.
	void SetArguments(void *Param1 = NULL, CUtlVector<void *>* Param2 = NULL, CUtlVector<void *>* Param3 = NULL, int Param4 = 0);

	// Execute callback.
	// Note: NEVER RUN DIRECTLY.
	void CallCallback();

	// Get timer name.
	inline const char *GetName()
	{
		return name;
	}

	// Get how many repeats left for timer end. 
	inline const int GetRepeatsLeft()
	{
		return (repeats-repeatsCount);
	}


public:
	float time;
	float startTime;
	unsigned int repeats;
	unsigned int repeatsCount;
	bool removeAtRoundEnd;

private:
	const char *name;
	const char *sender;
	void *Param1;
	CUtlVector<void *>* Param2;
	CUtlVector<void *>* Param3;
	int Param4;

	// The callback engine.
	//TCallback<CPluginTimers> i_CallbackOutput;
};

//=================================================================================
// CLASS LIB_TIMER_CLASS
//=================================================================================
class LIB_TIMER_CLASS
{
public:
	// Constructor
	LIB_TIMER_CLASS();

	// Destructor
	~LIB_TIMER_CLASS();

	// Reset Timers.
	void Reset();

	// Add a named timer to list.
	// time is in seconds.
	bool Add(const char *name, float time, unsigned int repeats = 0, bool removeAtRoundEnd = false, void *Param1 = NULL, CUtlVector<void *>* Param2 = NULL, CUtlVector<void *>* Param3 = NULL, int Param4 = 0);

	// Remove a timer by name.
	// Returns false, if name doesnt't exists.
	bool Remove(const char *name);

	// Remove a timer by index.
	// Returns false, if index doesnt't exists.
	bool Remove(int index);

	// Remove all timers, flagged with round end.
	// Return the number of removed timers.
	unsigned int RemoveRoundEndTimers();

	// Loop all timers and execute ready timers.
	// Call on GameFrame.
	void CheckTimers();
	
	// Get timer index from name.
	// Returns -1 on invalid name.
	int GetIndex(const char *name);

	// Check if a timer name exists.
	bool Exists(const char *name);

	// Get a CTimerInfo from name.
	// Returns NULL on invalid name.
	LIB_TIMERINFO_CLASS *GetTimer(const char *name);

	// Get how many repeats left for timer end.
	// Returns -1 on invalid name.
	int GetRepeatsLeft(const char *name);
private:
	// Execute timer, INTERNAL
	void ExecuteTimer(int id);

	CUtlVector<LIB_TIMERINFO_CLASS*> vec_timers;
};

//=================================================================================
// CLASS LIB_TIMERIMPL_CLASS
//=================================================================================
class LIB_TIMERIMPL_CLASS
{
public:
	LIB_TIMERIMPL_CLASS();
	~LIB_TIMERIMPL_CLASS();

	//virtual bool TimerCallback(void *sender, void *Param1, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4);
	virtual bool TimerCallback(const char *sender, void *Param1, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4) = 0;
};

//=================================================================================
// Extern global variable
//=================================================================================
extern LIB_TIMER_CLASS *VAR_LIB_TIMER;

#endif
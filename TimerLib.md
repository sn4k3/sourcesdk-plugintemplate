# Introduction #

Timer library is a class, you can delay a action, ie. give weapons after 2s player spawn, the names and comments are self explanatory<br>
This class can be disabled by comment out <b>USE_LIB_TIMER</b>

<h1>How To Use</h1>

Never use <b>CTimerLib</b> directly, instead we use <b>LIB_TIMER_CLASS</b><br>
This class must be initialized first, so if you are using that library you can use: <b>VAR_LIB_TIMER</b> variable or your short define to it ie. <b>vlTimer</b>

<pre><code>// Add a new timer, named test, will repeat 3 times from 10s to 10s<br>
VAR_LIB_TIMER-&gt;Add("test", 10, 3, false, (void*)"Hi there from plugin");<br>
<br>
// Dynamic call from rcon command<br>
PLUGIN_CON_COMMAND(countdown, "Show a count down in console")<br>
{<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;positive-number&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	int repeats = atoi(args.Arg(1));<br>
	if(repeats &lt; 1)<br>
	{<br>
		Msg("Syntax: %s &lt;positive-number&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
#ifndef USE_LIB_TIMER<br>
	Msg("Timers are disabled, can't count down\n");<br>
#else<br>
	if(VAR_LIB_TIMER-&gt;Exists("countdown"))<br>
	{<br>
		Msg("Currently there are one count down, wait for his termination!\n");<br>
	}<br>
	else<br>
		VAR_LIB_TIMER -&gt;Add("countdown", 1, repeats, false, NULL, NULL, NULL, repeats);<br>
#endif<br>
}<br>
</code></pre>

Timers got added, now you must handle<br>
Open your <b>plugin_timers.cpp</b>

<pre><code>// You should have something like:<br>
// Global timers callback, all timers triggers came to here<br>
bool PLUGIN_TIMERS_CLASS::TimerCallback(const char *sender, void *Param0, CUtlVector&lt;void *&gt;* Param2, CUtlVector&lt;void *&gt;* Param3, int Param4)<br>
{<br>
	LIB_TIMERINFO_CLASS *timer = VAR_LIB_TIMER-&gt;GetTimer(sender);	// Timer class, NULL if not alive (Repeats ends)<br>
	// From here treat other arguments as you need.<br>
	// You can create your own functions and redirect from here<br>
	if(LIB_STRING_CLASS::FStrEq(sender, "test"))<br>
	{<br>
		const char *arg1 = (const char *)Param0; // I know Param0 is a const char*, so lets convert it<br>
		<br>
		Msg("Lets see what plugin says: %s\n", arg1);<br>
		if(timer != NULL)<br>
			Msg("Repeats: %u of %u\n", timer-&gt;repeatsCount, timer-&gt;repeats);<br>
		else<br>
			Msg("Good bye for now.\n");<br>
		return true;<br>
	}<br>
	if(LIB_STRING_CLASS::FStrEq(sender, "countdown"))<br>
	{<br>
		// Note: we simply can use repeats, but i will show you, now to use dynamic arguments.<br>
		Msg("CountDown: %i\n", Param4);<br>
		if(timer)<br>
			timer-&gt;SetArguments(NULL, NULL, NULL, Param4-1);<br>
		else<br>
			Msg("COUNTDOWN ENDS.\n");<br>
		return true;<br>
	}<br>
	return false;<br>
}<br>
</code></pre>

Feel free to explore :)
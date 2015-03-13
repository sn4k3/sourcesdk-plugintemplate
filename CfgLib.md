# Introduction #

Cfg library is a class, you can handle .cfg files (write, read, remove, exec, ...), the names and comments are self explanatory<br>
This library idea came from Eventscripts <a href='http://python.eventscripts.com/pages/Cfglib'>cfglib</a>

<h1>How To Use</h1>

Never use <b>CCfgLib</b> directly, instead we use <b>LIB_CFG_CLASS</b>

<pre><code>// Initalize class<br>
LIB_CFG_CLASS *config = new LIB_CFG_CLASS("addons/plugintemplate/cfg/config.cfg");<br>
// We will create a config file, if don't exists one already<br>
// Make sure your text cvar and command names exists, otherwise it will be treated like Text in Load()<br>
if(!config-&gt;Load())<br>
{<br>
	// Can't load, procede to creation<br>
	config-&gt;Text("//***********************************//"); // Append a text line<br>
	config-&gt;Text("//      PLUGIN TEMPLATE CONFIG       //"); <br>
	config-&gt;Text("//***********************************//");<br>
<br>
	config-&gt;CVar("pt_rounds", "10", "Mod is only active in first 10 rounds"); // Append a cvar<br>
	config-&gt;CVar("pt_enableclasses", "1", "Enable or not the plugin classes");<br>
	config-&gt;CVar("pt_speed", "1", "Speed up gameplay up to defined value");<br>
	config-&gt;Command("pt_addclass", "\"weapon_ak47, weapon_deagle\""); // Append an command<br>
	config-&gt;Command(VAR_IFACE_ICVAR-&gt;FindCommand("mani_sethealth"), "#all 1000"); // Append an command giving and ConCommand*<br>
	// Don't have mani? not a problem, command must exists to be written first<br>
<br>
	config-&gt;CVar(VAR_IFACE_ICVAR-&gt;FindVar("mp_restartgame"), "3"); // Append a var giving and ConVar*<br>
	// Save to file<br>
	config-&gt;Write();<br>
}<br>
// Change speed, we need more!<br>
config-&gt;CVar("pt_speed", "2", "Speed up gameplay up to defined value");<br>
// After load or create, execute cvars and commands<br>
config-&gt;Execute();<br>
// Save new configs<br>
config-&gt;Write(NULL, true, true, true, true/*We need to overwrite file*/, true);<br>
// If no longer needed, object should be free<br>
config-&gt;~LIB_CFG_CLASS();<br>
</code></pre>

Now lets check our "addons/plugintemplate/cfg/config.cfg"<br>
<br>
<pre><code>//***********************************//<br>
//      PLUGIN TEMPLATE CONFIG       //<br>
//***********************************//<br>
// Mod is only active in first 10 rounds<br>
pt_rounds 10<br>
<br>
// Enable or not the plugin classes<br>
pt_enableclasses 1<br>
<br>
// Speed up gameplay up to defined value<br>
pt_speed 2<br>
<br>
pt_addclass "weapon_ak47, weapon_deagle"<br>
<br>
// Don't have mani? not a problem, command must exists to be written first<br>
// Yes i dont have mani-admin-plugin installed!<br>
 <br>
// If non-zero, game will restart in the specified number of seconds<br>
mp_restartgame 3<br>
</code></pre>

Its possible exec files, to do so:<br>
<br>
<pre><code>// exec a cfg file using rcon exec method<br>
// all files must be under cfg/ folder<br>
LIB_CFG_CLASS::Exec("server.cfg"); // LIB_CFG_CLASS::Exec("server"); also works<br>
<br>
// To exec a cfg in other folder we can use ExecEx<br>
LIB_CFG_CLASS::ExecEx("addons/plugintemplate/cfg/config.cfg");<br>
<br>
// if you need exec and handle file you can try ExecEx2, it will return a LIB_CFG_CLASS* object<br>
LIB_CFG_CLASS *servercfg = LIB_CFG_CLASS::ExecEx2("cfg/server.cfg");<br>
if(servercfg)<br>
{<br>
	Msg("Config Lines: %i\n", servercfg-&gt;vec_file.Count());<br>
	servercfg-&gt;Print(); // Print output file to console text<br>
	servercfg-&gt;Write("cfg/serverCOPY.cfg", true, true, true, true); // Create a server.cfg copy under cfg/ folder<br>
	servercfg-&gt;~LIB_CFG_CLASS(); // Free resources when are no longer needed<br>
}<br>
else<br>
{<br>
	Msg("No server.cfg file found\n");<br>
}<br>
</code></pre>

Feel free to explore :)
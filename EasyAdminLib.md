# Introduction #

Easy Admin library is a class, all methods are related to simple admin checks, the names and comments are self explanatory<br>
Easy Admin its a simple administration class, only works by steamid and there aren't any type of permissions.<br>
This class can be disabled by comment out <b>USE_LIB_EASYADMIN</b>


<h2>How To Use</h2>

Never use <b>CEasyAdminLib</b> directly, instead we use <b>LIB_EASYADMIN_CLASS</b><br>
This class must be initialized fist, so if you are using that library you can use: <b>VAR_LIB_EASYADMIN</b> variable or your short define to it ie. <b>vlEasyAdmin</b>

<h2>Tips</h2>

When using Easy Admin by plugintemplate <b>USE_LIB_EASYADMIN</b> admin files got saved and loaded when its need to, you don't need to care about that<br>
Auto save can also be desactivated by set <b>SETTING_LIB_EASYADMIN_AUTOSAVE</b> to false or comment<br>
<br>
Sample:<br>
<br>
<pre><code>PLUGIN_CON_COMMAND(makeadmin, "Add a steam id as admin")<br>
{<br>
	if(!VAR_LIB_EASYADMIN)<br>
	{<br>
		Msg("Easy Admin features are disabled.");<br>
		return;<br>
	}<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;steamid&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	VAR_LIB_EASYADMIN-&gt;Add(args.Arg(1));<br>
}<br>
<br>
PLUGIN_CON_COMMAND(isadmin, "Check if a steam id was an admin")<br>
{<br>
	if(!VAR_LIB_EASYADMIN)<br>
	{<br>
		Msg("Easy Admin features are disabled.");<br>
		return;<br>
	}<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;steamid&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	if(VAR_LIB_EASYADMIN-&gt;IsAdmin(args.Arg(1)))<br>
		Msg("%s is an admim\n", args.Arg(1));<br>
	else<br>
		Msg("%s is not an admim\n", args.Arg(1));<br>
}<br>
<br>
PLUGIN_CON_COMMAND(printadmins, "Show all admins steamids")<br>
{<br>
	if(!VAR_LIB_EASYADMIN)<br>
	{<br>
		Msg("Easy Admin features are disabled.");<br>
		return;<br>
	}<br>
	VAR_LIB_EASYADMIN-&gt;PrintAdmins();<br>
}<br>
</code></pre>


Fell free to explore :)
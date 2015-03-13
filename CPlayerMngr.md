# Introduction #

Player Manager library is collection of **PLUGIN\_PLAYER\_CLASS** classes, when enabled plugin will automatically add and remove clients from list when they disconnect / connect, the names and comments are self explanatory<br>
This class can be disabled by comment out <b>USE_LIB_PLAYERMNGR</b>

The purpose of this library its for keep the current list of players inside a player class<br>
When using this library by plugintemplate, never use Add or Remove clients functions<br>
<br>
<h1>How To Use</h1>

Never use <b>CPlayerMngr</b> directly, instead we use <b>LIB_PLAYERMNGR_CLASS</b><br>
This class must be initialized fist, so if you are using that library you can use: <b>VAR_LIB_PLAYERMNGR</b> variable or your short define to it ie. <b>vlPlayermngr</b>

Some examples:<br>
<br>
loop all players<br>
<br>
<pre><code>// foreach players inside PLAYERMNGR<br>
for(int i = 0; i &lt; VAR_LIB_PLAYERMNGR-&gt;Count(); i++)<br>
{<br>
	PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR-&gt;vec_players[i];<br>
	// Its just a way to loop all players, but lets kill all<br>
	player-&gt;Kill();<br>
	<br>
	/*<br>
	Never do that since its a pointer, doing such will make player invalid on the list<br>
	player-&gt;~PLUGIN_PLAYER_CLASS();<br>
	*/<br>
}<br>
</code></pre>

Easy way to retrieve a player<br>
<br>
<pre><code>// Choose one<br>
PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR-&gt;GetPlayer(pEntity);<br>
PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR-&gt;GetPlayerByName("sn4k3");<br>
PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR-&gt;GetPlayerByUserID(2);<br>
PLUGIN_PLAYER_CLASS *player = VAR_LIB_PLAYERMNGR-&gt;GetPlayerBySteamID("STEAM_ID_LAN");<br>
</code></pre>


Feel free to explore :)
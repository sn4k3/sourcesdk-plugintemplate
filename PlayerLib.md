# Introduction #

Player library is a class, you can handle players by using static methods or create an instance that points to a player, the names and comments are self explanatory<br>


<h1>How To Use</h1>

Never use <b>CPlayerLib</b> directly, instead we use <b>LIB_PLAYER_CLASS</b><br>
<b>NOTE:</b> You may notice there are a <b>plugin_player.cpp</b> in your main files, this one is if you want to create your own player lib, it also extendes <b>LIB_PLAYER_CLASS</b><br>
So instead use <b>LIB_PLAYER_CLASS</b> we can use <b>PLUGIN_PLAYER_CLASS</b>

Some examples using static methods:<br>
<br>
<pre><code>// Is player alive?<br>
PLUGIN_PLAYER_CLASS::IsAlive(pEntity);<br>
<br>
// Check if player is valid and not a bot (false argument), and return the IPlayerInfo object<br>
IPlayerInfo *pinfo = PLUGIN_PLAYER_CLASS::IsPlayer(pEntity, true);<br>
if(pinfo)<br>
	Msg("Player: %s\n", pinfo-&gt;GetName());<br>
<br>
// Kill Player<br>
PLUGIN_PLAYER_CLASS::Kill(pEntity);<br>
<br>
// Force client to reconnect without droping the netchannel<br>
PLUGIN_PLAYER_CLASS::Reconnect(pEntity);<br>
<br>
// Execute a command in every player<br>
PLUGIN_PLAYER_CLASS::Sexec("#a", "say hi");<br>
</code></pre>

Getting a random player:<br>
<br>
<pre><code>PLUGIN_CON_COMMAND(randplayer, "Get a random player")<br>
{<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(LIB_ENTITY_CLASS::GetEntityOfRandPlayer(args.Arg(1)));<br>
	if(!player-&gt;IsValid())<br>
	{<br>
		Msg("No player found\n");<br>
		return;<br>
	}<br>
<br>
	Msg("Rand player: %s\n", player-&gt;PlayerInfo()-&gt;GetName());<br>
}<br>
</code></pre>

Print a player list to console<br>
<br>
<pre><code>PLUGIN_CON_COMMAND(playerlist, "List players")<br>
{<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	Msg(""PLUGIN_HEADER"Player List\n_____________________________\nTotal Players: %i\n", mrf.GetRecipientCount());<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));<br>
		Msg("Player '%s' [%s]:\nIndex = %i\nUserid: %i\n----------------------\n", <br>
			player-&gt;PlayerInfo()-&gt;GetName(), player-&gt;SteamID(), player-&gt;Index(), player-&gt;UserID());<br>
		player-&gt;~LIB_PLAYER_CLASS();<br>
	}<br>
}<br>
</code></pre>

Set player health:<br>
<br>
<pre><code>PLUGIN_CON_COMMAND(sethealth, "Set player health")<br>
{<br>
	if(args.ArgC() &lt; 3)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;amount&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	int amount = atoi(args.Arg(2));<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		LIB_PLAYER_CLASS *player = new LIB_PLAYER_CLASS(mrf.GetRecipientIndex(i));<br>
		if(!player-&gt;IsAlive())<br>
		{<br>
			Msg("ERROR: Dead player, can't set health to: %s\n", player-&gt;PlayerInfo()-&gt;GetName());<br>
			player-&gt;~LIB_PLAYER_CLASS();<br>
			continue;<br>
		}<br>
		VAR_LIB_PROP-&gt;Prop_SetInt(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), "CBasePlayer", "m_iHealth", amount);<br>
		int health = VAR_LIB_PROP-&gt;Prop_GetInt(player-&gt;Edict(), "CBasePlayer", "m_iHealth");<br>
		Msg("Player '%s', have now %i Health\n", player-&gt;PlayerInfo()-&gt;GetName(), health);<br>
		player-&gt;~LIB_PLAYER_CLASS();<br>
	}<br>
}<br>
</code></pre>

Feel free to explore :)
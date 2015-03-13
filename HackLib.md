# Introduction #

Hack library is a class, all methods are related to plugin hacks like vfuncs, props and sigscan, the names and comments are self explanatory<br>
Hack Library will always load with your plugin.<br>
<br>
<br>
<h2>How To Use</h2>

Never use <b>CHackLib</b> directly, instead we use <b>LIB_HACK_CLASS</b><br>
This class must be initialized first, so if you are using that library you can use: <b>VAR_LIB_HACK</b> variable or your short define to it ie. <b>vlHack</b>

<h2>Tips</h2>

Hack Library is linked to your <b>PLUGIN_PROP_CLASS</b>, <b>PLUGIN_VFUNCS_CLASS</b> and <b>PLUGIN_SIGSCAN_CLASS</b> if you want access any of them call <b>VAR_LIB_HACK</b>.<br>
You also can access commun and game configurations if they are avaliable.<br>
<br>
<br>
<h2>Samples</h2>

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
<br>
PLUGIN_CON_COMMAND(health, "Math player health")<br>
{<br>
	if(args.ArgC() &lt; 4)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;amount&gt; &lt;operator&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	int amount = atoi(args.Arg(2));<br>
	char coperator = *args.Arg(3);<br>
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
		int currenthealth = VAR_LIB_PROP-&gt;Prop_GetInt(player-&gt;Edict(), "CBasePlayer", "m_iHealth");<br>
		switch(coperator)<br>
		{<br>
		case '+':<br>
			amount += currenthealth;<br>
			break;<br>
		case '-':<br>
			amount = currenthealth-amount;<br>
			break;<br>
		case '*':<br>
			amount *= currenthealth;<br>
			break;<br>
		case '/':<br>
			amount = currenthealth/amount;<br>
			break;<br>
		}<br>
		if(amount &lt; 0)<br>
		{<br>
			Msg("Can't set player '%s' Health, value is negative\n", player-&gt;PlayerInfo()-&gt;GetName());<br>
			return;<br>
		}<br>
		VAR_LIB_PROP-&gt;Prop_SetInt(player-&gt;Edict(), "CBasePlayer", "m_iHealth", amount);<br>
		Msg("Player '%s', have now %i Health\n", player-&gt;PlayerInfo()-&gt;GetName(), amount);<br>
		player-&gt;~LIB_PLAYER_CLASS();<br>
	}<br>
<br>
}<br>
<br>
PLUGIN_CON_COMMAND(setplayerprop, "Set player property")<br>
{<br>
	if(args.ArgC() &lt; 4)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;prop&gt; &lt;value&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		VAR_LIB_PROP-&gt;Prop_SetDynamic(mrf.GetRecipientEdict(i), args.Arg(2), NULL, args.Arg(3));<br>
	}<br>
}<br>
<br>
PLUGIN_CON_COMMAND(setplayerdmap, "Set player datamap")<br>
{<br>
	if(args.ArgC() &lt; 4)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;datamap_name&gt; &lt;value&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		VAR_LIB_PROP-&gt;Map_SetDynamic(mrf.GetRecipientBaseEntity(i), args.Arg(2), args.Arg(3));<br>
	}<br>
}<br>
<br>
PLUGIN_CON_COMMAND(getplayerprop, "Get player property")<br>
{<br>
	if(args.ArgC() &lt; 3)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;prop&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		Msg("Player %i: %s\n", mrf.GetRecipientIndex(i), VAR_LIB_PROP-&gt;Prop_GetDynamic(mrf.GetRecipientEdict(i), args.Arg(2), NULL));<br>
	}<br>
}<br>
<br>
PLUGIN_CON_COMMAND(getplayerdmap, "Get player datamap")<br>
{<br>
	if(args.ArgC() &lt; 3)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;datamap_name&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		Msg("Player %i: %s\n", mrf.GetRecipientIndex(i), VAR_LIB_PROP-&gt;Map_GetDynamic(mrf.GetRecipientBaseEntity(i), args.Arg(2)));<br>
	}<br>
}<br>
</code></pre>

More samples:<br>
<br>
<pre><code>PLUGIN_CON_COMMAND(teleport, "Teleport a player")<br>
{<br>
	if(!VAR_LIB_VFUNCS)<br>
	{<br>
		Msg("VFuncs features are disabled.");<br>
		return;<br>
	}<br>
	if(args.ArgC() &lt; 3)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;\"x y z Position\"&gt; [\"x y z Velocity\"]\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	Vector vec = LIB_STRING_CLASS::StrToVec(args.Arg(2));<br>
	Vector velocity = args.ArgC() &lt; 4 ? NULL : LIB_STRING_CLASS::StrToVec(args.Arg(3));<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		VAR_LIB_VFUNCS-&gt;CBaseEntity_Teleport(PEntityOfEntIndex(mrf.GetRecipientIndex(i)), &amp;vec, NULL, &amp;velocity, "CBaseEntity::Teleport");<br>
	}<br>
}<br>
<br>
PLUGIN_CON_COMMAND(spawn, "Spanws a player")<br>
{<br>
	if(!VAR_LIB_SIGSCAN)<br>
	{<br>
		Msg("SigScan features are disabled.");<br>
		return;<br>
	}<br>
	if(args.ArgC() &lt; 2)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; [force]\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	bool force = args.ArgC() &gt;= 3;<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		edict_t *pEntity = PEntityOfEntIndex(mrf.GetRecipientIndex(i));<br>
		if(!pEntity) continue;<br>
		if (force)<br>
		{<br>
			VAR_LIB_SIGSCAN-&gt;CSSPlayer_RoundRespawn(pEntity, "CSSPlayer::RoundRespawn");<br>
			continue;<br>
		}<br>
		if(!LIB_PLAYER_CLASS::IsAlive(pEntity))<br>
		{<br>
			VAR_LIB_SIGSCAN-&gt;CSSPlayer_RoundRespawn(pEntity, "CSSPlayer::RoundRespawn");<br>
		}<br>
	}<br>
}<br>
<br>
PLUGIN_CON_COMMAND(switchteam, "Switch a player fro other team")<br>
{<br>
	if(!VAR_LIB_SIGSCAN)<br>
	{<br>
		Msg("SigScan features are disabled.");<br>
		return;<br>
	}<br>
	if(args.ArgC() &lt; 3)<br>
	{<br>
		Msg("Syntax: %s &lt;players&gt; &lt;team&gt;\n",args.Arg(0)); // Error Message<br>
		return;<br>
	}<br>
	LIB_MRECIPIENTFILTER_CLASS mrf;<br>
	mrf.AddByFilter(args.Arg(1), false);<br>
	int team = atoi(args.Arg(2));<br>
	for(int i = 0; i &lt; mrf.GetRecipientCount(); i++)<br>
	{<br>
		VAR_LIB_SIGSCAN-&gt;CSSPlayer_SwitchTeam(mrf.GetRecipientEdict(i), team, "CSSPlayer::SwitchTeam");<br>
	}<br>
}<br>
</code></pre>



Fell free to explore :)
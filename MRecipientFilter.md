# Introduction #

We all know MRecipientFilter class, all methods are related to add players index to a list, the names and comments are self explanatory<br>
This class is always compiled and can't be disabled<br>
<br>
<br>
<h1>How To Use</h1>

Never use <b>MRecipientFilter</b> directly, instead we use <b>LIB_MRECIPIENTFILTER_CLASS</b>


<pre><code>// MRecipientFilter is familiar to all, so im showing new implementations, Add by player filter<br>
<br>
// we have:<br>
	// Add players by filter.<br>
	// # for begin a player filter.<br>
	// ! for remove a player filter.<br>
	// a = All players.<br>
	// u or 0 = Unsigned Team.<br>
	// s or 1 = Spectator Team.<br>
	// t or 2 = Terrorist Team (Team 2)<br>
	// c or 3 = Countert-Terrorist Team (Team 3)<br>
	// b = Bots<br>
	// h = humman players.<br>
	// l = Living players.<br>
	// d = Dead players.<br>
	//<br>
	// if '|' is the first char on the filter string, partial will be activated (set to true)<br>
	// Set 'forceDisablePartial' to true for disable so, (filter string can't activate partial '|' itself)<br>
	//<br>
	// Also support player names, userid, steamid with multi players.<br>
	// "2 3 4 playername STEAM_1:1:25416446" OR "2" OR "STEAM_0:0:1111" OR "nameonly"<br>
	// Multi players are only recomendate for Userids and SteamIds, players name sometimes have spaces.<br>
	//<br>
	// 'Partial' allow you add players by steam or by name with partial name eg<br>
	// eg. true player name: "my name is player" in partial can be "my " or "my name" ...<br>
	//<br>
	// Return player count.<br>
	// int AddByFilter(const char *filter, bool partial = true, bool forceDisablePartial = false); <br>
<br>
LIB_MRECIPIENTFILTER_CLASS mrf;<br>
// Lets add all humans and not dead<br>
mrf.AddByFilter("#h!d"); /*SAME AS*/ mrf.AddByFilter("#a!b!d"); /*SAME AS*/ mrf.AddByFilter("#l!b");<br>
<br>
// Lets add a complex one<br>
// This one will add players: not bots, not unsigned, not dead<br>
mrf.AddByFilter("#a!b!u!d");<br>
<br>
// Add by userid<br>
// Support multiple<br>
mrf.AddByFilter("2 5 6 10");<br>
<br>
// Add by name<br>
// Support multiple<br>
mrf.AddByFilter("sn4k3 dev plugin");<br>
<br>
// Add by SteamID<br>
// Support multiple<br>
mrf.AddByFilter("STEAM_ID_LAN STEAM_0:1:54643 STEAM_1:1:25416446");<br>
<br>
// Add by mix (userid, name, steamid)<br>
// Support multiple<br>
mrf.AddByFilter("sn4k3 5 STEAM_ID_LAN 9 STEAM_0:1:54643 STEAM_1:1:25416446 myname 40");<br>
<br>
// Add by partial<br>
// If you want to type only a partial name or steamid<br>
// Imagine if there are 5 sn4k3 at the server (sn4k3_1, sn4k3_2, sn4k3_3, sn4k3_4)<br>
// Result = All players with name started with 'sn' will got added to list, same to SteamIDS<br>
mrf.AddByFilter("sn", true, false);<br>
<br>
// Add by partial string way<br>
// Same as previous example<br>
// Partial is disable, but '|' will activate partial to entire string<br>
mrf.AddByFilter("|sn", false, false);<br>
<br>
<br>
// Add within a radius<br>
Vector vec = Vector("-6954.33 6125.99 1056.11");<br>
mrf.AddWithinRadius(vec, 100);<br>
<br>
</code></pre>

<b>Note:</b> AddByFilter can get you to add wrong players, look:<br>
<pre><code>// You may think that will add All humans alive<br>
mrf.AddByFilter("#hl");<br>
<br>
// Thats wrong, you are overriding all humans to all living (including bots)<br>
// To get it correct must be:<br>
mrf.AddByFilter("#h!d");<br>
<br>
// A sample usage without !<br>
// Add team 2 and team 3 to list<br>
// Here we doesn't override a rule<br>
mrf.AddByFilter("#23);<br>
<br>
<br>
// Always think on: if i do 'h2' it will add all humans and after all players from team 2 don't care if it is a bot, so humans rule got override.<br>
// so it must be '2!b'<br>
</code></pre>

Feel free to explore and don't fear the filters :)
# Introduction #

Entity library is a static class, all methods are related to entities and conversions, the names and comments are self explanatory<br>
This class is always compiled and can't be disabled<br>
<br>
<br>
<h1>How To Use</h1>

Never use <b>CEntityLib</b> directly, instead we use <b>LIB_ENTITY_CLASS</b>

<pre><code>// some examples<br>
<br>
// check if edict is safe to use<br>
if(!LIB_ENTITY_CLASS::IsEntitySafe(pEntity))<br>
   return false;<br>
<br>
// Get player index from userid<br>
int playerIndex = LIB_ENTITY_CLASS::GetIndexFromUserID(2);<br>
<br>
// Get IPlayerinfo from edict<br>
IPlayerinfo pinfo = LIB_ENTITY_CLASS::GetPlayerinfoFromEntity(pEntity);<br>
if(!pinfo) return; // Not safe<br>
pinfo-&gt;GetName(); // Player name<br>
<br>
// Get entities count on the map by name<br>
unsigned int count = LIB_ENTITY_CLASS::GetEntityCount("weapon_deagle");<br>
</code></pre>

Feel free to explore :)
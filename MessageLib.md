# Introduction #

Message library is a static class, all methods are related with UserMessages and others ways to message a player, the names and comments are self explanatory<br>
This class is always compiled and can't be disabled<br>
<br>
<br>
<h1>How To Use</h1>

Never use <b>CMessageLib</b> directly, instead we use <b>LIB_MESSAGE_CLASS</b>

<pre><code>// Lets print text on player chat<br>
LIB_MESSAGE_CLASS::Say(pEntity, "Hello\n");<br>
<br>
// Lets print text on all players chat<br>
// Filters<br>
LIB_MESSAGE_CLASS::Say("#h", "Hello\n");<br>
<br>
// Shake player screen for 10s<br>
LIB_MESSAGE_CLASS::Shake(pEntity, 10, SHAKE_START, 25, 200);<br>
<br>
// Show a Hint to player<br>
LIB_MESSAGE_CLASS::Hint(pEntity, "testing messages\nHint may bip");<br>
<br>
// Send a menu to players<br>
// Only numbers 1, 2 and 0 will  interact with the menu<br>
LIB_MESSAGE_CLASS::Menu("#h!l", "Im a menu\n \n-&gt;1. Option One\n-&gt;2. Option Two\n \n0. Exit", "019");<br>
<br>
// Redirect player to other server (OB Only)<br>
// Player have 20s to accept or deny<br>
LIB_MESSAGE_CLASS::Redirect(pEntity, 20, "82.64.11.64:27015");<br>
<br>
// Send a rich box to player, it shows for last 60s<br>
// No its not MS Word :P<br>
LIB_MESSAGE_CLASS::RichBox(pEntity, 60, "Title: hi player", "Today we are offering 16k cash each round\nBut if you buy awp, your salary will be cut\n \nEnjoy");<br>
<br>
// Entry player, ask something<br>
LIB_MESSAGE_CLASS::Entry(pEntity, 0, "You will die", "kill", "On quit you will die, so think how you can avoid your death\nHint: Deads cant die again.");<br>
</code></pre>

Feel free to explore :)
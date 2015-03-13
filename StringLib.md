# Introduction #

String library is a static class, all methods are related to strings, the names and comments are self explanatory<br>
This class is always compiled and can't be disabled<br>
<br>
<h1>How To Use</h1>

Never use <b>CStringLib</b> directly, instead we use <b>LIB_STRING_CLASS</b>

<pre><code>// Some examples<br>
<br>
// Compare two strings (const char *)<br>
if(LIB_STRING_CLASS::FStrEq("mytext", "mytext"))<br>
   return true;<br>
<br>
// Convert a string into a Vector<br>
Vector vec = LIB_STRING_CLASS::StrToVec("-85463.23 5621.54 16478.64");<br>
<br>
// Convert to upper case<br>
// Result = PLUGINTEMPLATE<br>
const char *upperCase = LIB_STRING_CLASS::StrToUpper("plugintemplate");<br>
<br>
// Returns the portion of string specified by the start and length parameters.<br>
// Result = "phrase to test"<br>
const char *result = LIB_STRING_CLASS::SubStr("a cool phrase to test", 7, strlen("a cool phrase to test"));<br>
</code></pre>

Feel free to explore :)
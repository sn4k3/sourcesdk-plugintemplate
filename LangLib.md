# Introduction #

Lang library is a class, all methods are related to languages and translations, the names and comments are self explanatory<br>
This class can be disabled by comment out <b>USE_LIB_LANG</b>


<h2>Configure</h2>

<b>configs/libs_config.h</b>
<pre><code>// Files WildCard, search for files<br>
// ie. *.phrases.txt<br>
#define SETTING_LIB_LANG_WILDCARD "*.phrases.txt"<br>
<br>
// Directory to search for translation files<br>
// Use a full path to file, to use a single file instead ie. ""PLUGIN_DATA_DIR"translations.txt"<br>
#define SETTING_LIB_LANG_PATH ""PLUGIN_DATA_DIR"translations/"<br>
</code></pre>

<h2>Translation Files Format</h2>

<pre><code>// Avaliable Languages<br>
	enum Languages<br>
	{<br>
		DEFAULT = 0,<br>
		EN,<br>
		ES,<br>
		FR,<br>
		IT,<br>
		DE,<br>
		KO,<br>
		ZHCN,<br>
		ZHTW,<br>
		RU,<br>
		TH,<br>
		JA,<br>
		PT,<br>
		PL,<br>
		DA,<br>
		NL,<br>
		FI,<br>
		NB,<br>
		SV,<br>
		INVALIDLANG<br>
	};<br>
<br>
// main.phrases.txt<br>
"translation"<br>
{<br>
	"#namespace"	"main"<br>
	"one"<br>
	{<br>
		"default"	"EN"<br>
		"EN"		"one"<br>
		"PT"		"um"<br>
	}<br>
	"two"<br>
	{<br>
		"DEFAULT"	"EN"<br>
		"EN"		"two"<br>
		"PT"		"dois"<br>
	}<br>
	"translateme"<br>
	{<br>
		"DEFAULT"	"EN"<br>
		"EN"		"Hi! You wan't me to translate"<br>
		"PT"		"Olá! Tu queres que eu traduza"<br>
	}<br>
}<br>
<br>
// menu.phrases.txt<br>
"translation"<br>
{<br>
	"#namespace"	"menu"<br>
	"next"<br>
	{<br>
		"default"	"EN"<br>
		"EN"		"Next"<br>
		"PT"		"Seguinte"<br>
	}<br>
	"back"<br>
	{<br>
		"DEFAULT"	"EN"<br>
		"EN"		"Back"<br>
		"PT"		"Anterior"<br>
	}<br>
	"exit"<br>
	{<br>
		"DEFAULT"	"EN"<br>
		"EN"		"Exit"<br>
		"PT"		"Sair"<br>
	}<br>
}<br>
</code></pre>

<h1>How To Use</h1>

Never use <b>CLangLib</b> directly, instead we use <b>LIB_LANG_CLASS</b><br>
This class must be initialized fist, so if you are using that library you can use: <b>VAR_LIB_LANG</b> variable or your short define to it ie. <b>vlLang</b>

<pre><code>// some examples<br>
<br>
// Get a translation for a language<br>
// Deafult translation returns if the requested one is not present<br>
// Result = "Seguinte" (Portguese) (next in english)<br>
const char *phrase = VAR_LIB_LANG-&gt;GetLangStr("menu", "next", "pt");<br>
Msg("Translated 'menu' to: %s\n", phrase);<br>
<br>
// Also is possible get translation according player game language<br>
// ie. Result = "Hi there, welcome to our server."<br>
const char *phrase = VAR_LIB_LANG-&gt;GetLangStr(pEntity, "greetings", "playerjoin");<br>
Msg("%s\n", phrase);<br>
</code></pre>

Feel free to explore :)
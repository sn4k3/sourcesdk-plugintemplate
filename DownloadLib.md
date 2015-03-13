# Introduction #

Download library is a class, all methods are related to client downloads, the names and comments are self explanatory<br>
When enabled all files on download list will be added to server downloads on <b>LevelInit</b> and when plugin <b>loads</b> after map change<br>
This class can be disabled by comment out <b>USE_LIB_DOWNLOAD</b>


<h2>How To Use</h2>

Never use <b>CDownloadLib</b> directly, instead we use <b>LIB_DOWNLOAD_CLASS</b><br>
This class must be initialized fist, so if you are using that library you can use: <b>VAR_LIB_DOWNLOAD</b> variable or your short define to it ie. <b>vlDownload</b>

On your <b>PLUGIN_CLASS::Load()</b> you can add your files to be downloaded every map<br>
To do so:<br>
<br>
<pre><code>bool PLUGIN_CLASS::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)<br>
{<br>
	// Add files if exists<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/join.mp3", true);<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/mapchange.mp3", true);<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/vote.mp3", true);<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/kick.mp3", true);<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/hi.mp3", true);<br>
	// Tired of adding one by one?, try this<br>
	VAR_LIB_DOWNLOAD-&gt;Add("sound/plugintemplate/", LIB_DOWNLOAD_CLASS::DOWNLOAD_FOLDER, "*.mp3", false);<br>
	// You also can create a list in a text file (one file per line)<br>
	VAR_LIB_DOWNLOAD-&gt;Add("addons/plugintemplate/data/downloads.txt", LIB_DOWNLOAD_CLASS::DOWNLOAD_FROMFILE);<br>
}<br>
// Done, every time the map change the previous files will be added to server downloads automatically<br>
</code></pre>

Not using <b>Donwload library</b> but you need to add client downloads?<br>
Not a problem, <b>LIB_DOWNLOAD_CLASS</b> provide some static methods to add downloads to clients<br>

Must be used every <b>LevelInit</b>

<pre><code>//---------------------------------------------------------------------------------<br>
// Purpose: called on level start<br>
//---------------------------------------------------------------------------------<br>
void PLUGIN_CLASS::LevelInit(char const *pMapName, const char *pOldMapName)<br>
{<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/join.mp3");<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/mapchange.mp3");<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/vote.mp3");<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/kick.mp3");<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/hi.mp3");<br>
	// Tired of adding one by one?, try this<br>
	LIB_DOWNLOAD_CLASS::AddDownload("sound/plugintemplate/", LIB_DOWNLOAD_CLASS::DOWNLOAD_FOLDER, "*.mp3", false);<br>
	// You also can create a list in a text file (one file per line)<br>
	LIB_DOWNLOAD_CLASS::AddDownload("addons/plugintemplate/data/downloads.txt", LIB_DOWNLOAD_CLASS::DOWNLOAD_FROMFILE);<br>
}<br>
</code></pre>


Fell free to explore :)
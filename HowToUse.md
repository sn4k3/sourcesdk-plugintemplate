# How to use #

## After Install ##

After install you should rename main folder, and project name in VS20xx if you want<br>
Next step, you must configure your plugin, by edit files under <b>./config/</b> folder, each config contain a comment that will help you understand what it do on your plugin<br>
<br>
<h2>PluginTemplate Files</h2>

You should never touch PluginTemplate libraries or files<br>
All files inside './plugintemplate/' folder should never be altered, otherwise you can lost your patches when update plugintemplate core.<br>
<br>
You should only use 'plugin<code>_*</code>' files to code<br>
<br>
<h2>Additional Folders</h2>

<ul><li><b>./GameFolder/</b> inside your project folder contains your plugin ready for upload to a server<br>You can create your folders, configs (cfg), etc etc.<br>bin files are automatically copied</li></ul>


<ul><li><b>./extensions/</b> folder can be used for libraries like SQlite, MySQL, GeoIP, ... whatever you like
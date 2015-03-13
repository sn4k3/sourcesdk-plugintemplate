# Introduction #

Here you will learn now to install the plugintemplate and turn it into your plugin.


# Installation #

  1. You need a copy of HL2SDK, i recommend you get it from here: http://hg.alliedmods.net/hl2sdks/
  1. Copy '**plugintemplate**' folder to: **HL2SDK/utils/** or where you want (You can rename the folder)
  1. Get metamod sources, if you don't want to use Metamod, you must have at same.<br>Download fom: <a href='http://sourcemm.net/downloads'>http://sourcemm.net/downloads</a> (plugintemplate was compiled with Metamod:Source 1.8.5)<br>
<ol><li>Unrar metamod to: <b>HL2SDK/</b> or other folder<br>
</li><li>On Windows, there is no particular directory layout required -- environment variables are used instead. The directions below apply to Windows XP, and are assumed to be similar for other versions of Windows.<br>
<ol><li>Open the Control Panel (for example, via Start -> Settings).<br>
</li><li>Open the System control. If you don't see it, you may need to switch to "Classic view" (either via the left-hand pane or by going to Tools -> Folder Options).<br>
</li><li>Click the Advanced tab.<br>
</li><li>Click the Environment Variables button.</li></ol></li></ol>

<blockquote>You can add your environment variables to either your User settings or your System settings. Create a new variable for each item in the list below. The item names are in fixed-width font and their value descriptions follow.</blockquote>

<ul><li><b>MMSOURCE</b> - Path to Metamod:Source source code.<br>
</li><li><b>HL2SDK</b> - Path to HL2SDK for Ep1/Original<br>
</li><li><b>HL2SDK-DARKM</b> - Path to HL2SDK for Dark Messiah<br>
</li><li><b>HL2SDKOB</b> - Path to HL2SDK for Ep2/OrangeBox<br>
</li><li><b>HL2SDKOBVALVE</b> - Path to HL2SDK for Ep2/OrangeBox Valve<br>
</li><li><b>HL2SDKL4D</b> - Path to HL2SDK for Left 4 Dead<br>
</li><li><b>HL2SDKL4D2</b> - Path to HL2SDK for Left 4 Dead 2<br>
</li><li><b>HL2SDKSWARM</b> - Path to HL2SDK for Alien Swarm</li></ul>

<blockquote>Installation done<br>
Open the plugin project and start codding.</blockquote>

<b>Final Note:</b> If you use sourcehook on your VSP plugin you must include it in your Windows Project
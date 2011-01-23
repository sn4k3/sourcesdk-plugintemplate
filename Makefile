# (C)2004-2010 Metamod:Source Development Team
# Makefile written by David "BAILOPAN" Anderson

###########################################
### EDIT THESE PATHS FOR YOUR OWN SETUP ###
###########################################

HL2SDK_ORIG = ../..
HL2SDK_DARKMESSIAH = ../..
HL2SDK_OB = ../..
HL2SDK_OB_VALVE = ../..
HL2SDK_L4D = ../../hl2sdk-l4d
HL2SDK_L4D2 = ../../hl2sdk-l4d2
HL2SDK_ALIENSWARM = ../../hl2sdk-alienswarm
MMSOURCE = ../../mmsource

# setup plugin folder
PLUGIN_ADDONS_FOLDER = GameFolder/addons/plugintemplate

#####################################
### EDIT BELOW FOR OTHER PROJECTS ###
#####################################

# Compile to metamod source-Werror
COMPILE_MM = false
# Compile plugin with python Eventscripts support
ENABLE_PYTHON = false
# Include SourceHook?
INCLUDE_SOURCEHOOK = true

PROJECT = plugintemplate
OBJECTS = serverplugin_main.cpp plugin_python.cpp plugin_gameevents.cpp plugin_convars.cpp plugin_concommands.cpp \
	plugin_player.cpp plugin_hack.cpp plugin_timers.cpp plugin_globals.cpp

PLUGINTEMPLATE_OBJECTS = plugintemplate/others/oslink.cpp \
	plugintemplate/extensions/demangle/cp-demangle.cpp plugintemplate/extensions/demangle/cp-demint.cpp plugintemplate/extensions/demangle/cplus-dem.cpp plugintemplate/extensions/demangle/safe-ctype.cpp plugintemplate/extensions/demangle/xmalloc.cpp plugintemplate/extensions/demangle/xstrdup.cpp \
	plugintemplate/serverplugin/serverplugin_engine.cpp plugintemplate/serverplugin/serverplugin_enginepython.cpp \
	plugintemplate/libs/lib_admin.cpp plugintemplate/libs/lib_cfg.cpp plugintemplate/libs/lib_convar.cpp plugintemplate/libs/lib_download.cpp \
	plugintemplate/libs/lib_entity.cpp plugintemplate/libs/lib_globals.cpp plugintemplate/libs/lib_hack.cpp plugintemplate/libs/lib_ini.cpp plugintemplate/libs/lib_lang.cpp \
	plugintemplate/libs/lib_linuxutils.cpp plugintemplate/libs/lib_memory.cpp \
	plugintemplate/libs/lib_menu.cpp plugintemplate/libs/lib_message.cpp plugintemplate/libs/lib_player.cpp plugintemplate/libs/lib_profiling.cpp \
	plugintemplate/libs/lib_prop.cpp plugintemplate/libs/lib_sigscan.cpp plugintemplate/libs/lib_sound.cpp plugintemplate/libs/lib_string.cpp \
	plugintemplate/libs/lib_timer.cpp plugintemplate/libs/lib_unitconverter.cpp plugintemplate/libs/lib_vfuncs.cpp plugintemplate/libs/libraries.cpp \
	plugintemplate/libs/MRecipientFilter.cpp 

# SourceHook files
SOURCEHOOK_FILES = sourcehook.cpp sourcehook_impl_chookidman.cpp sourcehook_impl_chookmaninfo.cpp sourcehook_impl_cproto.cpp sourcehook_impl_cvfnptr.cpp
	
##############################################
### CONFIGURE ANY OTHER FLAGS/OPTIONS HERE ###
##############################################

OPT_FLAGS = -O3 -funroll-loops -s -pipe
GCC4_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden
DEBUG_FLAGS = -g -ggdb3 -D_DEBUG
CPP = gcc
OBJECTS += $(PLUGINTEMPLATE_OBJECTS)

##########################
### SDK CONFIGURATIONS ###
##########################

PROJECT := $(PROJECT)_
ifeq "$(DEBUG)" "true"
	PROJECT := $(PROJECT)d
endif

override ENGSET = false

# Check for valid list of engines
ifneq (,$(filter original darkmessiah orangebox orangeboxvalve left4dead left4dead2 alienswarm,$(ENGINE)))
	override ENGSET = true
endif

ifeq "$(ENGINE)" "original"
	HL2SDK = $(HL2SDK_ORIG)
	CFLAGS += -DSOURCE_ENGINE=1
	PROJECT := $(PROJECT)ep1
endif
ifeq "$(ENGINE)" "darkmessiah"
	HL2SDK = $(HL2SDK_DARKMESSIAH)
	CFLAGS += -DSOURCE_ENGINE=2
	PROJECT := $(PROJECT)darkm
endif
ifeq "$(ENGINE)" "orangebox"
	HL2SDK = $(HL2SDK_OB)
	CFLAGS += -DSOURCE_ENGINE=3
	PROJECT := $(PROJECT)ep2
endif
ifeq "$(ENGINE)" "orangeboxvalve"
	HL2SDK = $(HL2SDK_OB_VALVE)
	CFLAGS += -DSOURCE_ENGINE=4
	PROJECT := $(PROJECT)ep2v
endif
ifeq "$(ENGINE)" "left4dead"
	HL2SDK = $(HL2SDK_L4D)
	CFLAGS += -DSOURCE_ENGINE=5
	PROJECT := $(PROJECT)l4d
endif
ifeq "$(ENGINE)" "left4dead2"
	HL2SDK = $(HL2SDK_L4D2)
	CFLAGS += -DSOURCE_ENGINE=6
	PROJECT := $(PROJECT)l4d2
endif
ifeq "$(ENGINE)" "alienswarm"
	HL2SDK = $(HL2SDK_ALIENSWARM)
	CFLAGS += -DSOURCE_ENGINE=7
	PROJECT := $(PROJECT)alienswarm
endif

PLUGIN_ENGINE = VSP
ifeq "$(COMPILE_MM)" "true"
	PROJECT := $(PROJECT)_mm
	CFLAGS += -DSOURCEMM
	PLUGIN_ENGINE = MMS
endif

HL2PUB = $(HL2SDK)/public

ifeq "$(ENGINE)" "original"
	INCLUDE += -I$(HL2SDK)/dlls -I$(HL2PUB)/dlls -I$(HL2SDK)/game_shared 
	METAMOD = $(MMSOURCE)/core-legacy
else
	INCLUDE += -I$(HL2SDK)/game/server -I$(HL2SDK)/game/shared -I$(HL2PUB)/game/server -I$(HL2PUB)/game/shared
	METAMOD = $(MMSOURCE)/core
endif

SOURCEHOOK = $(METAMOD)/sourcehook


ifeq "$(INCLUDE_SOURCEHOOK)" "true"
	OBJECTS += $(SOURCEHOOK_FILES)
endif

OS := $(shell uname -s)

ifeq "$(OS)" "Darwin"
	LIB_EXT = dylib
	HL2LIB = $(HL2SDK)/lib/mac
else
	LIB_EXT = so
	ifeq "$(ENGINE)" "original"
		HL2LIB = $(HL2SDK)/linux_sdk
	else
		HL2LIB = $(HL2SDK)/lib/linux
	endif
endif

# if ENGINE is orig, OB, or L4D
ifneq (,$(filter original orangebox left4dead,$(ENGINE)))
	LIB_SUFFIX = _i486.$(LIB_EXT)
else
	LIB_PREFIX = lib
	LIB_SUFFIX = .$(LIB_EXT)
endif

ifeq "$(ENABLE_PYTHON)" "true"
	INCLUDE += plugintemplate/externlibs/python/linux/include
	CFLAGS += -DPYTHON
	LINK += plugintemplate/externlibs/python/libs/libpython2.5.so.1.0 
endif

CFLAGS += -DSE_EPISODEONE=1 -DSE_DARKMESSIAH=2 -DSE_ORANGEBOX=3 -DSE_ORANGEBOXVALVE=4 \
	-DSE_LEFT4DEAD=5 -DSE_LEFT4DEAD2=6 -DSE_ALIENSWARM=7

LINK += $(HL2LIB)/tier1_i486.a $(HL2LIB)/tier2_i486.a $(HL2LIB)/mathlib_i486.a \
	$(LIB_PREFIX)vstdlib$(LIB_SUFFIX) $(LIB_PREFIX)tier0$(LIB_SUFFIX) \
	-static-libgcc

INCLUDE += -I. -I.. -I$(HL2PUB) -I$(HL2PUB)/common -I$(HL2PUB)/engine \
	-I$(HL2PUB)/mathlib -I$(HL2PUB)/vstdlib -I$(HL2PUB)/tier0 -I$(HL2PUB)/tier1 \
	-I. -I$(METAMOD) -I$(METAMOD)/sourcehook \
	-Iconfig -Iplugintemplate -Iplugintemplate/macros -Iplugintemplate/extensions/demangle

################################################
### DO NOT EDIT BELOW HERE FOR MOST PROJECTS ###
################################################

BINARY = $(PROJECT).$(LIB_EXT)

ifeq "$(DEBUG)" "true"
	BIN_DIR = bin/linux/Debug.$(PLUGIN_ENGINE).$(ENGINE)
	CFLAGS += $(DEBUG_FLAGS)
else
	BIN_DIR = bin/linux/Release.$(PLUGIN_ENGINE).$(ENGINE)
	CFLAGS += $(OPT_FLAGS)
endif

GCC_VERSION := $(shell $(CPP) -dumpversion >&1 | cut -b1)

ifeq "$(OS)" "Darwin"
	LIB_EXT = dylib
	CFLAGS += -isysroot /Developer/SDKs/MacOSX10.5.sdk
	LINK += -dynamiclib -lstdc++ -mmacosx-version-min=10.5
else
	LIB_EXT = so
	CFLAGS += -D_LINUX
	LINK += -shared
endif

CFLAGS += -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp \
	-Dstrnicmp=strncasecmp -D_snprintf=snprintf -D_vsnprintf=vsnprintf -D_alloca=alloca \
	-Dstrcmpi=strcasecmp -Wall -Wno-non-virtual-dtor -Wfatal-errors -fPIC -fno-exceptions \
	-fno-rtti -msse -m32 -fno-strict-aliasing
#-Werror
ifeq "$(GCC_VERSION)" "4"
	CFLAGS += $(GCC4_FLAGS)
endif

OBJ_BIN := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all: check
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/plugintemplate/extensions/demangle
	mkdir -p $(BIN_DIR)/plugintemplate/others
	mkdir -p $(BIN_DIR)/plugintemplate/serverplugin
	mkdir -p $(BIN_DIR)/plugintemplate/libs
	mkdir -p $(PLUGIN_ADDONS_FOLDER)/bin
	ln -sf $(HL2LIB)/$(LIB_PREFIX)vstdlib$(LIB_SUFFIX)
	ln -sf $(HL2LIB)/$(LIB_PREFIX)tier0$(LIB_SUFFIX)
	if [ "$(INCLUDE_SOURCEHOOK)" = "true" ]; then \
		for number in $(SOURCEHOOK_FILES) ; do \
			ln -sf $(SOURCEHOOK)/$$number ; \
		done \
	fi
	$(MAKE) -f Makefile plugin
	$(MAKE) -f Makefile plugin_clean
	
check:
	if [ "$(ENGSET)" = "false" ]; then \
		echo "You must supply one of the following values for ENGINE:"; \
		echo "alienswarm, left4dead2, left4dead, orangeboxvalve, orangebox, darkmessiah or original"; \
		exit 1; \
	fi
	
plugin: check $(OBJ_BIN)
	echo "start";
	$(CPP) $(INCLUDE) -m32 $(OBJ_BIN) $(LINK) -ldl -lm -o $(BIN_DIR)/$(BINARY)
	cp -f $(BIN_DIR)/$(BINARY) $(PLUGIN_ADDONS_FOLDER)/bin/$(BINARY)

default: all

clean: check
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/$(BINARY)
	rm -rf $(BIN_DIR)

plugin_clean:
	for number in $(SOURCEHOOK_FILES) ; do \
		rm -rf $$number ; \
	done
	rm -rf $(LIB_PREFIX)vstdlib$(LIB_SUFFIX)
	rm -rf $(LIB_PREFIX)tier0$(LIB_SUFFIX)


//-----------------------------------------------------------------------------------
//
// Bitfighter - A multiplayer vector graphics space game
// Based on Zap demo released for Torque Network Library by GarageGames.com
//
// Derivative work copyright (C) 2008-2009 Chris Eykamp
// Original work copyright (C) 2004 GarageGames.com, Inc.
// Other code copyright as noted
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//------------------------------------------------------------------------------------

#ifndef _CONFIG_H_
#define _CONFIG_H_

// This file contains definitions of two structs that are used to store our
// INI settings and command line param settings, which are read separately,
// but processed jointly.  Some default values are provided here as well,
// especially for the INI settings...  if the INI is deleted, these defaults
// will be used to rebuild it.

#include <SDL_types.h>

#include "tnlTypes.h"
#include "tnlNetStringTable.h"
#include "tnlVector.h"

#include "color.hpp"      // For Color def
#include "ConfigEnum.hpp" // For sfxSets, DisplayMode

//#include "input.h"
#include <string>

namespace bitfighter {

	// As soon as I figure out where this is set, it will be moved inside a class
	//extern const char *MASTER_SERVER_LIST_ADDRESS;
	// Changed into a function, because global variables are bad!
	const char *MASTER_SERVER_LIST_ADDRESS( void );

	////////////////////////////////////
	////////////////////////////////////

	class GameSettings;
	struct CmdLineSettings;

	class FolderManager {
	public:
	   FolderManager();
	   FolderManager(const std::string &levelDir, const std::string &robotDir,
					const std::string &sfxDir, const std::string &musicDir, 
					const std::string &iniDir, const std::string &logDir,
					const std::string &screenshotDir, const std::string &luaDir,
					const std::string &rootDataDir,  const std::string &pluginDir);

	   std::string levelDir;
	   std::string robotDir;
	   std::string sfxDir;
	   std::string musicDir;
	   std::string iniDir;
	   std::string logDir;
	   std::string screenshotDir;
	   std::string luaDir;
	   std::string rootDataDir;
	   std::string pluginDir;

	   void resolveDirs(GameSettings *settings);                                  
	   void resolveLevelDir(GameSettings *settings);                                 
	   std::string resolveLevelDir(const std::string &levelDir);

	   std::string findLevelFile(const std::string &filename) const;
	   std::string findLevelFile(const std::string &levelDir, const std::string &filename) const;

	   TNL::Vector<std::string> getScriptFolderList() const;
	   TNL::Vector<std::string> getPluginFolderList() const;
	   TNL::Vector<std::string> getHelperScriptFolderList() const;

	   std::string findLevelGenScript(const std::string &fileName) const;
	   std::string findPlugin(const std::string &filename) const;
	   std::string findBotFile(const std::string &filename) const;
	   std::string findScriptFile(const std::string &filename) const;
	};


	////////////////////////////////////////
	////////////////////////////////////////

	class GameSettings;

	struct CmdLineSettings
	{
	   CmdLineSettings();      // Constructor

	   void init();
   
	   bool dedicatedMode;     // Will server be dedicated?

	   std::string server;
	   std::string masterAddress;   // Use this master server

	   float loss;              // Simulate packet loss (0-1)
	   Uint32 lag;                // Simulate server lag (in ms)
	   Uint32 stutter;            // Simulate VPS CPU stutter (0-1000)

	   bool forceUpdate;       // For testing updater
	   std::string dedicated;       // Holds bind address specified on cmd line following -dedicated parameter
	   std::string name;
	   std::string password;

	   std::string hostname;
	   std::string hostaddr;        // Address to listen on when we're host (e.g. IP:localhost:1234 or IP:Any:6666 or whatever)
	   std::string hostdescr;       // One-line description of server
	   std::string serverPassword;  // Password required to connect to server
	   std::string adminPassword;   // Password required to perform certain admin functions
	   std::string levelChangePassword;   // Password required to change levels and such

	   FolderManager dirs;

	   Sint32 maxPlayers;

	   DisplayMode displayMode;    // Fullscreen param supplied

	   Sint32 winWidth;
	   Sint32 xpos;
	   Sint32 ypos;

	   TNL::Vector<std::string> specifiedLevels;
	};


	// Keep track of which keys editor plugins have been bound to
	struct PluginBinding
	{
	   std::string key;          // Key user presses
	   std::string script;       // Plugin script that gets run
	   std::string help;         // To be shown in help
	};


	////////////////////////////////////////
	////////////////////////////////////////

	struct IniSettings {      // With defaults specified
	public:
	   IniSettings();       // Constructor

	   bool controlsRelative;
	   DisplayMode displayMode;
	   DisplayMode oldDisplayMode;
	   std::string joystickType;
	   bool joystickLinuxUseOldDeviceSystem;
	   bool alwaysStartInKeyboardMode;
	   bool echoVoice;

	   float sfxVolLevel;                 // SFX volume (0 = silent, 1 = full bore)
	   float musicVolLevel;               // As above
	   float voiceChatVolLevel;           // Ditto
	   float alertsVolLevel;              // And again

	   sfxSets sfxSet;                  // Which set of SFX does the user want?

	   bool starsInDistance;            // True if stars move in distance behind maze, false if they are in fixed location
	   bool diagnosticKeyDumpMode;      // True if want to dump keystrokes to the screen

	   bool showWeaponIndicators;       // True if we show the weapon indicators on the top of the screen
	   bool verboseHelpMessages;        // If true, we'll show more handholding messages
	   bool showKeyboardKeys;           // True if we show the keyboard shortcuts in joystick mode

	   bool enableExperimentalAimMode;  // True if we want to show an aim vector in joystick mode

	   bool allowGetMap;                // allow '/GetMap' command
	   bool allowDataConnections;       // Specify whether data connections are allowed on this computer

	   Uint32 maxDedicatedFPS;
	   Uint32 maxFPS;

	   std::string masterAddress;            // Default address of our master server
	   std::string name;                     // Player name (none by default)    ==> will only be present if the user added it manually
	   std::string password;                 // Player pasword (none by default) ==> will only be present if the user added it manually
	   std::string defaultName;              // Name used if user hits <enter> on name entry screen
	   std::string lastName;                 // Name user entered last time the game was run -- will be used as default on name entry screen
	   std::string lastPassword;
	   std::string lastEditorName;           // Name of file most recently edited by the user

	   std::string hostname;                 // Server name when in host mode
	   std::string hostaddr;                 // User-specified address/port of server
	   std::string hostdescr;                // One-line description of server
	   std::string serverPassword;
	   std::string adminPassword;
	   std::string levelChangePassword;      // Password to allow access to level changing functionality on non-local server
	   std::string levelDir;                 // Folder where levels are stored, by default
	   Sint32 maxPlayers;                  // Max number of players that can play on local server
	   Sint32 maxBots;

	   Sint32 connectionSpeed;

	   bool randomLevels;
	   bool skipUploads;

	   bool allowMapUpload;
	   bool allowAdminMapUpload;

	   bool voteEnable;
	   Uint32 voteLength;
	   Uint32 voteLengthToChangeTeam;
	   Uint32 voteRetryLength;
	   Sint32 voteYesStrength;
	   Sint32 voteNoStrength;
	   Sint32 voteNothingStrength;

	   bool useUpdater;                 // Use updater system (windows only)

	   TNL::Vector<PluginBinding> pluginBindings;  // Keybindings for the editor plugins

	   // Game window location when in windowed mode
	   Sint32 winXPos;
	   Sint32 winYPos;
	   float winSizeFact;

	   // Use 'fake fullscreen' vs real fullscreen
	   bool useFakeFullscreen;

	   // Testing values
	   bool neverConnectDirect;
	   Color wallFillColor;
	   Color wallOutlineColor;
	   Uint16 clientPortNumber;

	   // Logging options   --   true will enable logging these events, false will disable
	   bool logConnectionProtocol;
	   bool logNetConnection;
	   bool logEventConnection;
	   bool logGhostConnection;
	   bool logNetInterface;
	   bool logPlatform;
	   bool logNetBase;
	   bool logUDP;

	   bool logFatalError;        
	   bool logError;             
	   bool logWarning;    
	   bool logConfigurationError;
	   bool logConnection;        
	   bool logLevelLoaded;    
	   bool logLevelError;
	   bool logLuaObjectLifecycle;
	   bool luaLevelGenerator;    
	   bool luaBotMessage;        
	   bool serverFilter;  
	   bool logStats;

	   std::string mySqlStatsDatabaseServer;
	   std::string mySqlStatsDatabaseName;
	   std::string mySqlStatsDatabaseUser;
	   std::string mySqlStatsDatabasePassword;

	   std::string defaultRobotScript;
	   std::string globalLevelScript;

	   TNL::Vector<TNL::StringTableEntry> levelList;

	   TNL::Vector<std::string> reservedNames;
	   TNL::Vector<std::string> reservedPWs;

	   Uint32 version;

	   bool oldGoalFlash;

	   TNL::Vector<std::string> prevServerListFromMaster;
	   TNL::Vector<std::string> alwaysPingList;
	};


	class CIniFile;
	class InputCodeManager;

	void saveSettingsToINI  (CIniFile *ini, GameSettings *settings);
	void loadSettingsFromINI(CIniFile *ini, GameSettings *settings);

	void writeSkipList(CIniFile *ini, const TNL::Vector<std::string> *levelSkipList);

};

#endif

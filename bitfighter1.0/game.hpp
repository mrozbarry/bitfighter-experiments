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
// This program is distributed in the hope that it will be useful (and fun!),
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//------------------------------------------------------------------------------------

/*#include "gridDB.h"
#include "Timer.h"
#include "gameLoader.h"
#include "Rect.h"
#include "Colors.h"
#include "shipItems.h"           // For moduleInfos
#include "dataConnection.h"      // For DataSender
#include "SharedConstants.h"     // For badges enum

#include "GameTypesEnum.h"
#include "GameSettings.h"*/

#include <SDL_types.h>

#include "tnlNetObject.h"
#include "tnlTypes.h"
#include "tnlThread.h"

#include <string>

#ifndef bitfighter_game_hpp
#define bitfighter_game_hpp	1

namespace bitfighter {

// Some forward declarations
class MasterServerConnection;
class GameNetInterface;
class GameType;
class BfObject;
class GameObject;
class GameConnection;
class Ship;
class GameUserInterface;
struct UserInterfaceData;
class WallSegmentManager;

class AbstractTeam;
class Team;
class EditorTeam;
class UIManager;

struct IniSettings;

// Modes the player could be in during the game
enum UIMode {
   PlayMode,               // Playing
   ChatMode,               // Composing chat message
   QuickChatMode,          // Showing quick-chat menu
   LoadoutMode,            // Showing loadout menu
   EngineerMode,           // Showing engineer overlay mode
   TeamShuffleMode         // Player shuffling teams
};

enum VolumeType {
   SfxVolumeType,
   MusicVolumeType,
   VoiceVolumeType,
   ServerAlertVolumeType,
};


// DNS resolve ("bitfighter.org:25955") will freeze the game unless this is done as a seperate thread
class NameToAddressThread : public TNL::Thread {
private:
   std::string mAddress_string;
public:
   TNL::Address mAddress;
   bool mDone;
   bool mUsed;

   NameToAddressThread(const char *address_string);  // Constructor
   virtual ~NameToAddressThread();                   // Destructor

   Uint32 run();
};


/// Base class for server and client Game subclasses.  The Game
/// base class manages all the objects in the game simulation on
/// either the server or the client, and is responsible for
/// managing the passage of time as well as rendering.

class ClientRef;
class TeamManager;
class ClientInfo;

class Game : public LevelLoader {
public:
	static const int MAX_GAME_NAME_LEN = 32;
	static const int MAX_GAME_DESCR_LEN = 60;

   static const Sint32 DefaultGridSize = 255;   // Size of "pages", represented by floats for intrapage locations (i.e. pixels per integer)
   static const Sint32 MIN_GRID_SIZE = 5;       // Ridiculous, it's true, but we step by our minimum value, so we can't make this too high
   static const Sint32 MAX_GRID_SIZE = 1000;    // A bit ridiculous too...  250-300 seems about right for normal use.  But we'll let folks experiment.

   static const Sint32 PLAYER_VISUAL_DISTANCE_HORIZONTAL = 600;    // How far player can see normally horizontally...
   static const Sint32 PLAYER_VISUAL_DISTANCE_VERTICAL = 450;      // ...and vertically

   static const Sint32 PLAYER_SCOPE_MARGIN = 150;

   static const Sint32 PLAYER_SENSOR_PASSIVE_VISUAL_DISTANCE_HORIZONTAL = 800;    // How far player can see with sensor equipped horizontally...
   static const Sint32 PLAYER_SENSOR_PASSIVE_VISUAL_DISTANCE_VERTICAL = 600;      // ...and vertically

   static const Sint32 PLAYER_SENSOR_ACTIVE_VISUAL_DISTANCE_HORIZONTAL = 1060;   // How far player can see with sensor activated horizontally...
   static const Sint32 PLAYER_SENSOR_ACTIVE_VISUAL_DISTANCE_VERTICAL = 795;      // ...and vertically

   Game(const Address &theBindAddress, GameSettings *settings);         // Constructor
   virtual ~Game();                                                     // Destructor

   void setActiveTeamManager(TeamManager *teamManager);

   S32 getClientCount() const;                                          // Total number of players, human and robot
   S32 getPlayerCount() const;                                          // Returns number of human players
   S32 getAuthenticatedPlayerCount() const;                             // Number of authenticated human players
   S32 getRobotCount() const;                                           // Returns number of bots

   ClientInfo *getClientInfo(S32 index) const;
   const Vector<RefPtr<ClientInfo> > *getClientInfos();

   void addToClientList(ClientInfo *clientInfo);               
   void removeFromClientList(const StringTableEntry &name);             // Client side
   void removeFromClientList(ClientInfo *clientInfo);                   // Server side
   void clearClientList();

   ClientInfo *findClientInfo(const StringTableEntry &name);            // Find client by name
   
   Rect getWorldExtents();

   virtual bool isTestServer();                                         // Overridden in ServerGame

   virtual const Color *getTeamColor(S32 teamId) const;                 // ClientGame will override

   static const ModuleInfo *getModuleInfo(ShipModule module);
   
   void computeWorldObjectExtents();
   Rect computeBarrierExtents();

   Point computePlayerVisArea(Ship *ship) const;

   U32 getTimeUnconnectedToMaster();
   void onConnectedToMaster();

   void resetLevelInfo();

   virtual void processLevelLoadLine(U32 argc, U32 id, const char **argv, GridDatabase *database, bool inEditor, const string &levelFileName);  
   bool processLevelParam(S32 argc, const char **argv);
   string toString();

   virtual bool processPseudoItem(S32 argc, const char **argv, const string &levelFileName, GridDatabase *database) = 0;

   void setGameTime(F32 time);                                          // Only used during level load process

   void addToDeleteList(GameObject *theObject, U32 delay);

   void deleteObjects(U8 typeNumber);
   void deleteObjects(TestFunc testFunc);

   F32 getGridSize() const;
   void setGridSize(F32 gridSize);

   U32 getCurrentTime();
   virtual bool isServer() = 0;              // Will be overridden by either clientGame (return false) or serverGame (return true)
   virtual void idle(U32 timeDelta) = 0;

   void checkConnectionToMaster(U32 timeDelta);
   MasterServerConnection *getConnectionToMaster();

   GameNetInterface *getNetInterface();
   virtual GridDatabase *getGameObjDatabase();

   const Vector<SafePtr<GameObject> > &getScopeAlwaysList();

   void setScopeAlwaysObject(GameObject *theObject);
   GameType *getGameType() const;

   // Team functions
   S32 getTeamCount() const;
   AbstractTeam *getTeam(S32 teamIndex) const;
   Vector<Team *> *getSortedTeamList_score() const;

   S32 getTeamIndex(const StringTableEntry &playerName);

   void countTeamPlayers();      // Makes sure that the mTeams[] structure has the proper player counts

   void addTeam(AbstractTeam *team);
   void addTeam(AbstractTeam *team, S32 index);
   void replaceTeam(AbstractTeam *team, S32 index);
   void removeTeam(S32 teamIndex);
   void clearTeams();

   StringTableEntry getTeamName(S32 teamIndex) const;   // Return the name of the team

   void setGameType(GameType *theGameType);
   void processDeleteList(U32 timeDelta);

   GameSettings *getSettings();

   bool isSuspended();

   void resetMasterConnectTimer();

   void setReadyToConnectToMaster(bool ready);

   // Objects in a given level, used for status bar.  On server it's objects loaded from file, on client, it's objects dl'ed from server.
   S32 mObjectsLoaded;  

   Point getScopeRange(S32 sensorStatus);

   string makeUnique(const char *name);

private:
   F32 mGridSize;  

   U32 mTimeUnconnectedToMaster;                         // Time that we've been disconnected to the master
   bool mHaveTriedToConnectToMaster;

   TeamManager *mActiveTeamManager;

   // Functions for handling individual level parameters read in processLevelParam; some may be game-specific
   virtual void onReadTeamParam(S32 argc, const char **argv);
   void onReadTeamChangeParam(S32 argc, const char **argv);
   void onReadSpecialsParam(S32 argc, const char **argv);
   void onReadScriptParam(S32 argc, const char **argv);
   void onReadLevelNameParam(S32 argc, const char **argv);
   void onReadLevelDescriptionParam(S32 argc, const char **argv);
   void onReadLevelCreditsParam(S32 argc, const char **argv);

   S32 mPlayerCount;     // Humans only, please!
   S32 mRobotCount;

   NameToAddressThread *mNameToAddressThread;

protected:
   virtual void cleanUp();
   U32 mNextMasterTryTime;
   bool mReadyToConnectToMaster;

   Rect mWorldExtents;     // Extents of everything

   string mLevelFileHash;  // MD5 hash of level file

   struct DeleteRef
   {
      SafePtr<GameObject> theObject;
      U32 delay;

      DeleteRef(GameObject *o = NULL, U32 d = 0);
   };

   boost::shared_ptr<GridDatabase> mGameObjDatabase;                // Database for all normal objects

   Vector<DeleteRef> mPendingDeleteObjects;
   Vector<SafePtr<GameObject> > mScopeAlwaysList;
   U32 mCurrentTime;

   RefPtr<GameNetInterface> mNetInterface;

   SafePtr<MasterServerConnection> mConnectionToMaster;
   SafePtr<GameType> mGameType;

   bool mGameSuspended;       // True if we're in "suspended animation" mode

   GameSettings *mSettings;

   S32 findClientIndex(const StringTableEntry &name);

   // On the Client, this list will track info about every player in the game.  Note that the local client will also be represented here,
   // but the info in these records will only be managed by the server.  E.g. if the local client's name changes, the client's record
   // should not be updated directly, but rather by notifying the server, and having the server notify us.
   Vector<RefPtr<ClientInfo> > mClientInfos;

   TeamManager *mTeamManager;

   virtual AbstractTeam *getNewTeam() = 0;

public:
};


////////////////////////////////////////
////////////////////////////////////////

struct LevelInfo
{
public:
   StringTableEntry levelFileName;  // File level is stored in
   StringTableEntry levelName;      // Level "in-game" names
   GameTypeId levelType;      
   S32 minRecPlayers;               // Min recommended number of players for this level
   S32 maxRecPlayers;               // Max recommended number of players for this level

   LevelInfo();      // Default constructor used on server side

   // Constructor, used on client side where we don't care about min/max players
   LevelInfo(const StringTableEntry &name, GameTypeId type);

   // Constructor, used on server side, augmented with setInfo method below
   LevelInfo(const string &levelFile);

   void initialize();      // Called by constructors

   string getLevelTypeName();
};


};


#endif


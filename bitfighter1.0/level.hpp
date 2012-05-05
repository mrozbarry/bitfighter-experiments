
#include <chipmunk/chipmunk.h>
#include <vector>
#include <string>

#include "physics.hpp"

#ifndef bitfighter_level_hpp
#define bitfighter_level_hpp	1

namespace bitfighter {

	namespace objective {
		enum Who {
			a_player,
			a_team
		};
		// ... must ...
		enum What {
			stay_alive,
			kill_players,
			capture_the_flag,
			capture_zones,
			disable_a_core,
			retrieve_flags,
			move_a_ball_to_the_goal,
			hold_the_flag,
		};
	}

	class Level {
	public:
		/* Public Sub-Structs and Enums */
		struct Meta {
			std::string credits;
			std::string name;
			std::string description;
			std::string gamemode;
			Sint32		min_players;
			Sint32		max_players;
		};

		enum LevelObjectiveWho {
			LOW_player,
			LOW_team,
		}
		enum LevelObjectiveWhat {
			LOW_
		}

		/* Class Declares */
		Level( );
		Level( std::string path );
		~Level( );

		bool load( std::string path );
		void unload( void );
		bool save( void );
		bool saveAs( std::string path );

		bool addObject( physics::Object *obj );				// Add object to space
		physics::Object *popObject( physics::Object *obj );	// Remove object from space, don't delete
		physics::Object *popObject( std::string obj_name );	// ^ same
		void deleteObject( std::string obj_name );			// Remove and delete object

		Meta							meta;				// Get the author and level information
	
	private:
		cpSpace							*space;				// Physics space
		std::vector<physics::Object *>	objects;			// Objects in the space
		Uint32							currentTime;		// Physics helper
		Uint32							accumulator;		// Physics helper
	};

}

#endif

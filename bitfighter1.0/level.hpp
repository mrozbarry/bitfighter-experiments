
#include <chipmunk/chipmunk.h>
#include <vector>
#include <string>

#include "physics.hpp"

#ifndef bitfighter_level_hpp
#define bitfighter_level_hpp	1

namespace bitfighter {

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

		const float spaceDamping = 2.0f;

		/* Class Declares */
		Level( );
		Level( std::string path );
		~Level( );

		bool load( std::string path );
		void unload( void );
		bool save( void );
		bool saveAs( std::string path );
		Meta							meta;				// Get the author and level information
	
		bool addObject( physics::Object *obj );				// Add object to space
		physics::Object *popObject( physics::Object *obj );	// Remove object from space, don't delete
		physics::Object *popObject( std::string obj_name );	// ^ same
		void deleteObject( std::string obj_name );			// Remove and delete object

		void simulatePhysics( bool eraseAccumulator = false );

	private:
		cpSpace							*space;				// Physics space
		std::vector<physics::Object *>	objects;			// Objects in the space
		Uint32							currentTime;		// Physics helper (time between iterations)
		Uint32							accumulator;		// Physics helper (helps pickup missed iterations)
		float							physTick;			// Physics tick rate
	};

}

#endif

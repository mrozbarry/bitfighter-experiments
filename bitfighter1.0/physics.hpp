
#include <SDL_types.h>
#include <chipmunk/chipmunk.h>
#include <vector>
#include <string>

#ifndef bitfighter_physics_hpp
#define bitfighter_physics_hpp	1

namespace bitfighter {

	namespace physics {

		// This should be subclassed for different physics objects
		class Object {
		public:
			Object( std::string name );
			~Object( );

			void createCopy( Object *dest );
			std::string toString( void );

			virtual bool addToSpace( cpSpace *space );
			virtual void removeFromSpace( void );

			bool isNamed( std::string name );
			const std::string name( void );

			bool isStatic( void );

			virtual void draw( void ) = 0;

			cpBody					*body;
			std::vector<cpShape *>	shapes;
		
		private:

			std::string body2string( );
			std::string shapes2string( );

			std::string				m_name;
			cpSpace					*m_space;
		};

		class Wall : public Object {
		public:
			Wall( cpVect position, std::vector< cpVect > vertices );
			~Wall( );

			bool addToSpace( cpSpace *space );
			void removeFromSpace( cpSpace *space );

			void draw( void );
		};

		class Asteroid : public Object {
		public:
			Asteroid( cpVect position, float size );
			~Asteroid( );

			bool addToSpace( cpSpace *space );
			void removeFromSpace( cpSpace *space );

			void draw( void );
		};

		class Ball : public Object {
		public:
			Ball( cpVect position, float size );
			~Ball( );

			bool addToSpace( cpSpace *space );
			void removeFromSpace( cpSpace *space );

			void draw( void );
		};

		class Ship : public Object {
		public:
			Ship( cpVect position, Sint32 team );
			~Ship( );

			Sint32 getTeam( void );

			void rotateLeft( void );
			void rotateRight( void );
			void forwardThrust( void );
			void backwardThrust( void );

			bool addToSpace( cpSpace *space );
			void removeFromSpace( cpSpace *space );

			void draw( void );

		private:
			Sint32			m_team;
			Uint32			model;
		};

		class FixedTurret : public Object {
		public:
			FixedTurret( cpVect position, Sint32 team, std::string weapon = "" );
			~FixedTurret( );

			bool addToSpace( cpSpace *space );
			void removeFromSpace( cpSpace *space );

			void draw( void );

		private:
			Sint32		m_team;
			bool		m_canChangeTeam;
		};

	}

}

#endif

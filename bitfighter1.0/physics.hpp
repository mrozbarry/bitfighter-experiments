
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

			virtual bool addToSpace( cpSpace *space );
			virtual void removeFromSpace( void );

			bool isNamed( std::string name );
			const std::string name( void );

			bool isStatic( void );
			bool willCollideOnMask( cpLayers layers );
			void collideOnMask( cpLayers layers );
			cpLayers collisionMask( void );

			const cpBody *getBody( void );
			const std::vector<cpShape *> getShapes( void );

			virtual void draw( void ) = 0;

		private:
			std::string				m_name;
			cpSpace					*m_space;
			cpBody					*m_body;
			std::vector<cpShape *>	m_shapes;
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

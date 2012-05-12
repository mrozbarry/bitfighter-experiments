
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

	}

}

#endif

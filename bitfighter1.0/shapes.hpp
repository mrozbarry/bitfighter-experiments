
#include <chipmunk/chipmunk.h>
#include <vector>
#include <string>

#ifndef bitfighter_shapes_hpp
#define bitfighter_shapes_hpp	1

namespace bitfighter {

	namespace physics {

		class shape {
		public:
			shape();
			~shape();

			virtual std::string identifyShape( void ) const;
			virtual std::string shape2string( void );

			const cpShape *getShape( void );
			
			bool addToSpace( cpSpace *space );
			bool removeFromSpace( void );
			const cpSpace *getSpace( void );

			cpBody *body( void );
			void body( cpBody *body );

			bool sensor( void );
			void sensor( bool toggle );

			cpFloat elasticity( void );
			void elasticity( cpFloat e );

			cpFloat friction( void );
			void friction( cpFloat f );

			cpVect surfaceVelocity( void );
			void surfaceVelocity( cpVect sv );

			cpCollisionType collisionType( void );
			void collisionType( cpCollisionType ct );

			cpGroup group( void );
			void group( cpGroup group );

		protected:
			cpShape		*m_shape;
			cpSpace		*m_space;
			cpVect		m_offset;
		};

	}

}

#endif /* bitfighter_shapes_hpp */

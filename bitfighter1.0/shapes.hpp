
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

		class circle : public shape {
		public:
			circle( cpBody *body, cpFloat radius, cpVect offset = cpvzero );
			~circle( );

			std::string identifyShape( void ) const;
			std::string shape2string( void );

			cpFloat radius( void );
			cpVect offset( void );
		};

		class segment : public shape {
		public:
			segment( cpBody *body, cpVect a, cpVect b, cpFloat radius = 1.0f );
			~segment( );

			std::string identifyShape( void ) const;
			std::string shape2string( void );

			cpVect a( void );
			cpVect b( void );
			cpVect normal( void );
			cpFloat radius( void );
		};

		// Note: all polygons need to be convex!  An exception gets thrown if they aren't!
		class polygon : public shape {
		public:
			polygon( cpBody *body, std::vector< cpVect > vertices, cpVect offset = cpvzero );		// Generic constructor
			polygon( cpBody *body, cpVect a, cpVect b, cpVect c, cpVect offset = cpvzero );			// Triangle
			polygon( cpBody *body, cpFloat width, cpFloat height, cpVect offset = cpvzero );		// Box
			polygon( cpBody *body, unsigned int count, cpFloat radius, cpVect offset = cpvzero );	// Generic equalateral polygon
			~polygon( );

			std::string identifyShape( void ) const;
			std::string shape2string( void );

			static std::vector< polygon * > decompose( cpBody *body, std::vector<cpVect> vertices );

		};
	}

}

#endif /* bitfighter_shapes_hpp */

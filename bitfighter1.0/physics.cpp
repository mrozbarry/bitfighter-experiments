
#include "physics.hpp"

#include <iostream>
#include <sstream>

namespace bitfighter {

	namespace physics {

		Object::Object( std::string name )
			: body( NULL )
			, shapes(1)
			, m_name( name )
			, m_space( NULL )
		{	}

		Object::~Object( )
		{
			this->removeFromSpace();
		}

		void Object::createCopy( Object *dest )
		{
			// Copy this sucker
		}

		std::string Object::toString( void )
		{
			std::stringstream objstr;

			objstr << "BODY `" << this->m_name << "` ";
			objstr << "mass=" << this->body->m << " ";
			objstr << "invmass=" << this->body->m_inv << " ";
			objstr << "inertia=" << this->body->i << " ";
			objstr << "invinertia=" << this->body->i_inv << " ";
			objstr << "position=" << this->body->p.x << "," << this->body->p.y << " ";
			objstr << "velocity=" << this->body->v.x << "," << this->body->v.y << " ";
			objstr << "force=" << this->body->f.x << "," << this->body->f.y << " ";
			objstr << "angle=" << this->body->a << " ";
			objstr << "anglevel=" << this->body->w << " ";
			objstr << "torque=" << this->body->t << " ";
			objstr << "rot=" << this->body->rot.x << "," << this->body->rot.y << " ";
			objstr << "v_limit=" << this->body->v_limit << " ";
			objstr << "w_limit=" << this->body->w_limit << std::endl;

			return (std::string)objstr.str();
		}

		bool Object::addToSpace( cpSpace *space )
		{
			if( space == NULL ) return false;
			this->m_space = space;
			if( this->body ) cpSpaceAddBody( this->m_space, this->body );
			if( this->shapes.size() ) {
				for( unsigned int i = 0; i < this->shapes.size(); i++ ) {
					cpSpaceAddShape( this->m_space, this->shapes[i] );
				}
			}

		}

		void Object::removeFromSpace( void )
		{
			if( this->m_space == NULL ) return;
			if( this->shapes.size() ) {
				for( unsigned int i = 0; i < this->shapes.size(); i++ ) {
					cpSpaceRemoveShape( this->m_space, this->shapes[i] );
				}
			}
			if( this->body ) cpSpaceRemoveBody( this->m_space, this->body );
		}

		bool Object::isNamed( std::string name )
		{
			return this->m_name.compare( name ) == 0;
		}

		const std::string Object::name( void )
		{
			return this->m_name;
		}

		bool Object::isStatic( void )
		{
			return (body == NULL);
		}

		std::string Object::body2string( )
		{
			std::stringstream objstr;

			objstr << "BODY `" << this->m_name << "` ";
			objstr << "mass=" << this->body->m << " ";
			objstr << "invmass=" << this->body->m_inv << " ";
			objstr << "inertia=" << this->body->i << " ";
			objstr << "invinertia=" << this->body->i_inv << " ";
			objstr << "position=" << this->body->p.x << "," << this->body->p.y << " ";
			objstr << "velocity=" << this->body->v.x << "," << this->body->v.y << " ";
			objstr << "force=" << this->body->f.x << "," << this->body->f.y << " ";
			objstr << "angle=" << this->body->a << " ";
			objstr << "anglevel=" << this->body->w << " ";
			objstr << "torque=" << this->body->t << " ";
			objstr << "rot=" << this->body->rot.x << "," << this->body->rot.y << " ";
			objstr << "v_limit=" << this->body->v_limit << " ";
			objstr << "w_limit=" << this->body->w_limit << std::endl;

			return (std::string)objstr.str();
		}

		std::string Object::shapes2string( )
		{
			for( unsigned int i = 0; i < this->shapes.size(); i++ ) {
				switch( this->shapes[i]->klass->type ) {
				}
			}
		}

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

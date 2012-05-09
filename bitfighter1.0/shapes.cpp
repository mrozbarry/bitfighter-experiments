
#include "shapes.hpp"

namespace bitfighter {

	namespace physics {

		/* Basic shape skeleton */
		shape::shape()
			: m_shape( NULL )
			, m_space( NULL )
			, m_offset( cpvzero )
		{ }

		shape::~shape()
		{	}

		const cpShape *shape::getShape( void )
		{
			return this->m_shape;
		}
			
		bool shape::addToSpace( cpSpace *space )
		{
			if( space == NULL ) return false;
			if( cpSpaceIsLocked( space ) == cpTrue ) return false;
			this->m_space = space;
			cpSpaceAddShape( space, this->m_shape );
			return true;
		}

		bool shape::removeFromSpace( void )
		{
			if( this->m_space == NULL ) return false;
			if( cpSpaceIsLocked( this->m_space ) == cpTrue ) return false;
			cpSpaceRemoveShape( this->m_space, this->m_shape );
			this->m_space = NULL;
		}

		const cpSpace *shape::getSpace( void )
		{
			return (const cpSpace *)this->m_space;
		}

		cpBody *shape::body( void )
		{
			return cpShapeGetBody( this->m_shape );
		}

		void shape::body( cpBody *body )
		{
			// Can't change the body if it's in the space
			if( this->m_space ) return; // Maybe a throw is appropriate here?
			cpShapeSetBody( this->m_shape, body );
		}

		bool shape::sensor( void ) {	return (cpShapeGetSensor( this->m_shape ) == cpTrue) ? true : false;	}
		void shape::sensor( bool toggle ) {	cpShapeSetSensor( this->m_shape, ( toggle == true ) ? cpTrue : cpFalse );	}

		cpFloat shape::elasticity( void ) {	return cpShapeGetElasticity( this->m_shape );	}
		void shape::elasticity( cpFloat e ) {	cpShapeSetElasticity( this->m_shape, e );	}

		cpFloat shape::friction( void ) {	return cpShapeGetFriction( this->m_shape );	}
		void shape::friction( cpFloat f ) {	cpShapeSetFriction( this->m_shape, f ); }

		cpVect shape::surfaceVelocity( void ) {	return cpShapeGetSurfaceVelocity( this->m_shape ); }
		void shape::surfaceVelocity( cpVect sv ) {	cpShapeSetSurfaceVelocity( this->m_shape, sv ); }

		cpCollisionType shape::collisionType( void ) {	return cpShapeGetCollisionType( this->m_shape );	}
		void shape::collisionType( cpCollisionType ct ) {	cpShapeSetCollisionType( this->m_shape, ct );	}

		cpGroup shape::group( void ) {	return cpShapeGetGroup( this->m_shape );	}
		void shape::group( cpGroup group ) {	cpShapeSetGroup( this->m_shape, group );	}

	}

}
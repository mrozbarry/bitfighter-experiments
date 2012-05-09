
#include "level.hpp"

namespace bitfighter {

	Level::Level( )
	{
		this->space = cpSpaceNew();
		this->space->gravity = cpv( 0.0f, 0.0f );
		this->space->damping = this->spaceDamping;
	}

	Level::Level( std::string path )
	{
		this->space = cpSpaceNew();
		this->space->gravity = cpv( 0.0f, 0.0f );
		this->space->damping = this->spaceDamping;
	}

	Level::~Level( )
	{
		this->unload();
		cpSpaceFree( this->space );
	}

	bool Level::load( std::string path )
	{
	}

	void Level::unload( void )
	{
		if( this->objects.size() == 0 ) return;
		for( unsigned int i = 0; i < this->objects.size(); i++ ) {
			delete this->objects[i];
		}
	}

	bool Level::save( void )
	{
	}

	bool Level::saveAs( std::string path )
	{
	}
	
	bool Level::addObject( physics::Object *obj )
	{
	}

	physics::Object *Level::popObject( physics::Object *obj )
	{
	}

	physics::Object *Level::popObject( std::string obj_name )
	{
	}

	void Level::deleteObject( std::string obj_name )
	{
	}

	void Level::simulatePhysics( bool eraseAccumulator )
	{
	}

}

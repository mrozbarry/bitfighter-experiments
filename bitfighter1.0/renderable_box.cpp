
#include "renderable_box.hpp"

#include <iostream>

namespace bitfighter {

	RenderableBox::RenderableBox( Pointf topleft, Pointf bottomright, SDL::Color c )
		: RenderableObject( topleft, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_bottomright( bottomright )
		, m_color( c )
	{	}

	RenderableBox::~RenderableBox()
	{	}

	bool RenderableBox::handleEvent( SDL_Event *e )
	{ return true; }

	void RenderableBox::render( Uint32 delta )
	{
		glBegin( GL_QUADS );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_position.x, this->m_position.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_bottomright.x, this->m_position.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_bottomright.x, this->m_bottomright.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_position.x, this->m_bottomright.y, this->m_z );

		glEnd( );
	}

}
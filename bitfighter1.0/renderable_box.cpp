
#include "renderable_box.hpp"

#include <iostream>

namespace bitfighter {

	RenderableBox::RenderableBox( Pointf topleft, Pointf bottomright, SDL::Color c )
		: RenderableObject( topleft, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_bottomright( bottomright )
		, m_color( c )
		, m_surface( NULL )
	{	}

	RenderableBox::RenderableBox( Pointf topleft, Pointf bottomright, SDL::Surface *buffer )
		: RenderableObject( topleft, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_bottomright( bottomright )
		, m_surface( buffer )
		, m_color( 0 )
	{	}

	RenderableBox::~RenderableBox()
	{
		if( this->m_surface ) delete this->m_surface;
	}

	bool RenderableBox::handleEvent( SDL_Event *e )
	{ return true; }

	void RenderableBox::render( Uint32 delta )
	{
		if( this->m_surface ) this->m_surface->openglBindTexture();

		glBegin( GL_QUADS );

		if( this->m_surface ) {

			glTexCoord2f (0.0, 1.0);
			glVertex3f( this->m_position.x, this->m_position.y, this->m_z );

			glTexCoord2f (1.0, 1.0);
			glVertex3f( this->m_bottomright.x, this->m_position.y, this->m_z );

			glTexCoord2f (1.0, 0.0);
			glVertex3f( this->m_bottomright.x, this->m_bottomright.y, this->m_z );

			glTexCoord2f (0.0, 0.0);
			glVertex3f( this->m_position.x, this->m_bottomright.y, this->m_z );

		} else {

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_position.x, this->m_position.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_bottomright.x, this->m_position.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_bottomright.x, this->m_bottomright.y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( 0.5f ) );
			glVertex3f( this->m_position.x, this->m_bottomright.y, this->m_z );

		}
		glEnd( );
	}

}
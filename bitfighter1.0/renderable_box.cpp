
#include "renderable_box.hpp"

#include <iostream>

namespace bitfighter {

	RenderableBox::RenderableBox( Window *window, SDL::Rect bounds, SDL::Color c, float alpha )
		: RenderableObject(  window, bounds, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_color( c )
		, m_surface( NULL )
		, m_alpha( alpha )
	{	}

	RenderableBox::RenderableBox( Window *window, SDL::Rect bounds, SDL::Surface *buffer, float alpha, bool resize_to_buffer )
		: RenderableObject( window, bounds, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_surface( buffer )
		, m_color( 0 )
		, m_alpha( alpha )
	{
		if( resize_to_buffer ) {
			this->m_bound.w = (float)buffer->w_pow2();
			this->m_bound.h = (float)buffer->h_pow2();
		}
	}

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

			glColor4fv( (SDL::Color("white")).toGLColor4vf( this->m_alpha ) );
			glTexCoord2f (0.0, 1.0);
			glVertex3f( this->boundary().bottomleft().x, this->boundary().bottomleft().y, this->m_z );

			glTexCoord2f (1.0, 1.0);
			glVertex3f( this->boundary().bottomright().x, this->boundary().bottomright().y, this->m_z );

			glTexCoord2f (1.0, 0.0);
			glVertex3f( this->boundary().topright().x, this->boundary().topright().y, this->m_z );

			glTexCoord2f (0.0, 0.0);
			glVertex3f( this->boundary().topleft().x, this->boundary().topleft().y, this->m_z );

		} else {

			glColor4fv( this->m_color.toGLColor4vf( this->m_alpha ) );
			glVertex3f( this->boundary().topleft().x, this->boundary().topleft().y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( this->m_alpha ) );
			glVertex3f( this->boundary().topright().x, this->boundary().topright().y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( this->m_alpha ) );
			glVertex3f( this->boundary().bottomright().x, this->boundary().bottomright().y, this->m_z );

			glColor4fv( this->m_color.toGLColor4vf( this->m_alpha ) );
			glVertex3f( this->boundary().bottomleft().x, this->boundary().bottomleft().y, this->m_z );

		}
		glEnd( );
	}

}
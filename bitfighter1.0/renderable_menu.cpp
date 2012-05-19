
#include "renderable_menu.hpp"

namespace bitfighter {

	RenderableMenu::RenderableMenu( Window *window, Pointf position, SDL::Color *normal, SDL::Color *selected )
		: RenderableObject( window, SDL::Rect( position, 1, 1 ) )
		, m_alpha( 1.0 )
		, m_surface( NULL )
		, m_selection( 0 )
		, m_yoff( 0.0f )
	{
		this->m_colors[0] = normal;
		this->m_colors[1] = selected;
	}
	
	RenderableMenu::~RenderableMenu()
	{
		delete this->m_colors[0];
		delete this->m_colors[1];
		if( this->m_surface ) delete this->m_surface;
	}

	MenuItem *RenderableMenu::addItem( MenuItem *item )
	{
		if( !item ) throw new BitfighterException( "RenderableMenu", "item was NULL" );
		this->m_items.push_back( item );
		this->updateBuffer();
		return item;
	}

	bool RenderableMenu::handleEvent( SDL_Event *e )
	{
		if( this->m_items.size() == 0 ) return true;
		switch( e->type ) {
		case SDL_KEYDOWN:
			if( e->key.keysym.sym == SDLK_DOWN ) {
				this->m_selection++;
				if( this->m_selection >= (int)this->m_items.size() ) this->m_selection = 0;
			} else if( e->key.keysym.sym == SDLK_UP ) {
				this->m_selection--;
				if( this->m_selection < 0 ) this->m_selection = (int)this->m_items.size() - 1;
			}
			this->updateBuffer();
			break;
		}
		return true;
	}

	void RenderableMenu::render( Uint32 delta )
	{
		if( !this->m_surface ) return;

		this->m_surface->openglBindTexture();

		glBegin( GL_QUADS );

			glColor4fv( (SDL::Color("paleblue")).toGLColor4vf( 0.9f ) );
			glVertex3f( this->boundary().bottomleft().x, this->boundary().bottomleft().y - this->m_yoff, 0.0f );
			glColor4fv( (SDL::Color("paleblue")).toGLColor4vf( 0.9f ) );
			glVertex3f( this->boundary().bottomright().x, this->boundary().bottomright().y - this->m_yoff, 0.0f );
			glColor4fv( (SDL::Color("paleblue")).toGLColor4vf( 0.9f ) );
			glVertex3f( this->boundary().topright().x, this->boundary().topright().y - this->m_yoff, 0.0f );
			glColor4fv( (SDL::Color("paleblue")).toGLColor4vf( 0.9f ) );
			glVertex3f( this->boundary().topleft().x, this->boundary().topleft().y - this->m_yoff, 0.0f );

		glEnd( );

		glBegin( GL_QUADS );

			glColor4fv( (SDL::Color("white")).toGLColor4vf( this->m_alpha ) );
			glTexCoord2f (0.0, 1.0);
			glVertex3f( this->boundary().bottomleft().x, this->boundary().bottomleft().y - this->m_yoff, this->m_z );

			glTexCoord2f (1.0, 1.0);
			glVertex3f( this->boundary().bottomright().x, this->boundary().bottomright().y - this->m_yoff, this->m_z );

			glTexCoord2f (1.0, 0.0);
			glVertex3f( this->boundary().topright().x, this->boundary().topright().y - this->m_yoff, this->m_z );

			glTexCoord2f (0.0, 0.0);
			glVertex3f( this->boundary().topleft().x, this->boundary().topleft().y - this->m_yoff, this->m_z );
		
		glEnd();
	}

	void RenderableMenu::updateBuffer( void )
	{
		int h = 0;
		int w = 1;
		for(unsigned int i=0; i < this->m_items.size(); i++ ) {
			this->m_items[i]->render( (this->m_selection==i) ? *this->m_colors[1] : *this->m_colors[0] );
			h += this->m_items[i]->getBuffer()->h();
			if( this->m_items[i]->getBuffer()->w() > w ) w = this->m_items[i]->getBuffer()->w() + 20;
		}
		if( this->m_surface ) delete this->m_surface;
		this->m_surface = new SDL::Surface( w, h, 24 );
		
		int y = 0;
		for(unsigned int i=0; i < this->m_items.size(); i++ ) {
			SDL::Surface *buffer = this->m_items[i]->getBuffer();
			SDL_Rect drect = buffer->getClip();
			drect.x = 0;
			drect.y = y;
			buffer->blit( this->m_surface, &drect );
			y += buffer->h();
		}
		this->m_bound.w = (float)w;
		this->m_bound.h = (float)h;

		int diff = this->m_surface->h_pow2() - this->m_surface->h();
		this->m_yoff = (float)diff / 2.0f;
	}

}

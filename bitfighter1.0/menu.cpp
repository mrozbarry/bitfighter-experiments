
#include "menu.hpp"
#include "menuitem.hpp"

namespace bitfighter {
	Menu::Menu( )
	{
		this->m_buffer = NULL;
	}

	Menu::Menu( SDL_Rect boundaries )
		: m_bounds( boundaries )
	{
		this->m_buffer = new SDL::Surface( m_bounds.w, m_bounds.h, 24 );
	}

	Menu::Menu( int x, int y, int w, int h )
	{
		this->m_bounds.x = x;
		this->m_bounds.y = y;
		this->m_bounds.w = w;
		this->m_bounds.h = h;
		this->m_buffer = new SDL::Surface( m_bounds.w, m_bounds.h, 24 );
	}

	Menu::~Menu( )
	{
		if( this->m_buffer ) delete this->m_buffer;
	}

	MenuItem *Menu::addItem( MenuItem *item, void *callback )
	{
		this->m_items.push_back( item );
		return item;
	}

	bool Menu::dispatchEvents( void )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) ) {
			switch( e.type ) {
			case SDL_QUIT:
				return true;
				break;
			default:
				// Ignore it for now...
				break;
			}
		}
		return false;
	}

	void Menu::render( void )
	{
		unsigned int i = 0;
		int height = 0;
		for(i=0; i < this->m_items.size(); i++ ) {
			height += this->m_items[i]->getBuffer()->h();
		}
		int offset = (this->m_buffer->h() - height) / 2;
		SDL_Rect rect;
		rect.x = 5;
		rect.y = offset;
		for(i=0; i < this->m_items.size(); i++ ) {
			rect.w = this->m_items[i]->getBuffer()->w();
			rect.h = this->m_items[i]->getBuffer()->h();
			this->m_items[i]->getBuffer()->blit(this->m_buffer, &rect);
			rect.y += rect.h;
		}

		return;
	}

	void Menu::paint( void )
	{
		float bggray = 0.7f;
		float bgalpha = 0.2f;
		this->m_buffer->openglBindTexture( );
		glBegin( GL_QUADS );
			//glColor4f(bggray, bggray, bggray, bgalpha );
			//Bottom-left vertex (corner)
			glTexCoord2i( 0, 0 );
			glVertex3i( this->m_bounds.x, this->m_bounds.y - this->m_bounds.h, 0 );
 
			//glColor4f(bggray, bggray, bggray, bgalpha );
			//Bottom-right vertex (corner)
			glTexCoord2i( this->m_bounds.w, 0 );
			glVertex3i( this->m_bounds.x + this->m_bounds.w, this->m_bounds.y - this->m_bounds.h, 0 );
 
			//glColor4f(bggray, bggray, bggray, bgalpha );
			//Top-right vertex (corner)
			glTexCoord2i(  this->m_bounds.w,  this->m_bounds.h );
			glVertex3i( this->m_bounds.x + this->m_bounds.w, this->m_bounds.y, 0 );
 
			//glColor4f(bggray, bggray, bggray, bgalpha );
			//Top-left vertex (corner)
			glTexCoord2i( 0,  this->m_bounds.h );
			glVertex3i( this->m_bounds.x, this->m_bounds.y, 0 );
		glEnd();
		int glerror = GLException::glError();
		if( glerror != 0 ) throw new GLException( "Application", glerror, __FILE__, __LINE__ );
	}

	SDL::Surface *Menu::getBuffer( void ) {
		return this->m_buffer;
	}

}

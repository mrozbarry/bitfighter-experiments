
#include "menu.hpp"

namespace bitfighter {
	Menu::Menu( )
	{
		this->m_buffer = NULL;
	}

	Menu::Menu( SDL_Rect boundaries, bool canScroll )
		: m_bounds( boundaries )
		, m_scrollable( canScroll )
	{
		Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif
		this->m_buffer = SDL_CreateRGBSurface(
			0,
			m_bounds.w, m_bounds.h, 16,
			rmask, gmask, bmask, amask
		);
	}

	Menu::~Menu( )
	{
		if( this->m_buffer ) SDL_FreeSurface( this->m_buffer );
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

	void Menu::paint( void )
	{
		return;
	}

}

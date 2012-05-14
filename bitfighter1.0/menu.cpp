
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
		this->m_buffer = new SDL::Surface( m_bounds.w, m_bounds.x, 24 );
	}

	Menu::~Menu( )
	{
		if( this->m_buffer ) delete this->m_buffer;
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


#include <vector>
#include <string>
#include <SDL.h>
#include "sdlutil.hpp"

#ifndef bitfighter_menu_hpp
#define bitfighter_menu_hpp	1

namespace bitfighter {

	class MenuItem;

	class Menu {
	public:
		Menu( );
		Menu( SDL_Rect boundaries );
		Menu( int x, int y, int w, int h );

		~Menu( );

		MenuItem *addItem( MenuItem *item, void *callback );

		bool dispatchEvents( void );
		void render( void );
		void paint( void );

		SDL::Surface *getBuffer( void );

	private:
		SDL::Surface				*m_buffer;
		SDL_Rect					m_bounds;
		std::vector< MenuItem * >	m_items;
	};

}

#endif

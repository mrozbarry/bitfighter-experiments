
#include <vector>
#include <string>
#include <SDL.h>

#ifndef bitfighter_menu_hpp
#define bitfighter_menu_hpp	1

namespace bitfighter {

	class MenuItem;

	class Menu {
	public:
		Menu( );
		Menu( SDL_Rect boundaries, bool canScroll );
		~Menu( );

		bool dispatchEvents( void );
		void paint( void );

	private:
		SDL_Surface					*m_buffer;
		SDL_Rect					m_bounds;
		bool						m_scrollable;
		std::vector< MenuItem * >	m_items;
	};

}

#endif


#include "renderable.hpp"
#include "sdlutil.hpp"
#include <SDL.h>
#include <SDL_opengl.h>
#include "menuitem.hpp"
#include <vector>

#ifndef bitfighter_renderable_menu_hpp
#define bitfighter_renderable_menu_hpp	1

namespace bitfighter {

	class RenderableMenu : public RenderableObject {
	public:
		RenderableMenu( Window *window, Pointf position, SDL::Color *normal, SDL::Color *selected );
		~RenderableMenu();

		MenuItem *addItem( MenuItem *item );

		virtual bool handleEvent( SDL_Event *e );

	protected:
		virtual void render( Uint32 delta );

		void updateBuffer( void );

		SDL::Surface			*m_surface;
		float					m_alpha;
		std::vector<MenuItem *>	m_items;
		int						m_selection;
		SDL::Color				*m_colors[2];
		float					m_yoff;
	};

}

#endif /* bitfighter_renderable_menu_hpp */

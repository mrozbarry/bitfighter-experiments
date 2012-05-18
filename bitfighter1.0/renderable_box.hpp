
#include "renderable.hpp"
#include "sdlutil.hpp"
#include <SDL_opengl.h>

#ifndef bitfighter_renderable_menu_hpp
#define bitfighter_renderable_menu_hpp	1

namespace bitfighter {

	class RenderableBox : public RenderableObject {
	public:
		RenderableBox( Pointf topleft, Pointf bottomright, SDL::Color c = SDL::Color("white") );
		RenderableBox( Pointf topleft, Pointf bottomright, SDL::Surface *buffer );
		~RenderableBox();

		virtual bool handleEvent( SDL_Event *e );

	protected:
		virtual void render( Uint32 delta );

		Pointf			m_bottomright;
		SDL::Color		m_color;
		SDL::Surface	*m_surface;
	};

}

#endif /* bitfighter_renderable_menu_hpp */


#include "renderable.hpp"
#include <SDL_opengl.h>
#include "colours.hpp"

#ifndef bitfighter_renderable_menu_hpp
#define bitfighter_renderable_menu_hpp	1

namespace bitfighter {

	class RenderableBox : public RenderableObject {
	public:
		RenderableBox( Pointf topleft, Pointf bottomright, Uint8 r=255, Uint8 g=255, Uint8 b=255 );
		~RenderableBox();

		virtual bool handleEvent( SDL_Event *e );

	protected:
		virtual void render( Uint32 delta );

		Pointf		m_bottomright;
		SDL_Color	m_color;
	};

}

#endif /* bitfighter_renderable_menu_hpp */

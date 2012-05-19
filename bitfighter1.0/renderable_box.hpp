
#include "renderable.hpp"
#include "sdlutil.hpp"
#include <SDL_opengl.h>

#ifndef bitfighter_renderable_box_hpp
#define bitfighter_renderable_box_hpp	1

namespace bitfighter {

	class RenderableBox : public RenderableObject {
	public:
		RenderableBox( Window *window, SDL::Rect bounds, SDL::Color c = SDL::Color("white"), float alpha = 1.0 );
		RenderableBox( Window *window, SDL::Rect bounds, SDL::Surface *buffer, float alpha = 1.0, bool resize_to_buffer = false );
		~RenderableBox();

		virtual bool handleEvent( SDL_Event *e );

	protected:
		virtual void render( Uint32 delta );

		SDL::Color		m_color;
		SDL::Surface	*m_surface;
		float			m_alpha;
	};

}

#endif /* bitfighter_renderable_box_hpp */

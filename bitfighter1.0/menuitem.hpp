
#include <SDL.h>
#include <string>
#include "font.hpp"
#include "sdlutil.hpp"

#ifndef bitfighter_menuitem_hpp
#define bitfighter_menuitem_hpp	1

namespace bitfighter {

	class RenderableObject;

	class MenuItem {
	public:
		MenuItem( RenderableObject *renderable, bool enabled = false );
		~MenuItem( );

		virtual void process( SDL_Event *e );
		virtual void render( SDL::Color c );
		SDL::Surface *getBuffer( void );

		bool isEnabled( void );
		void isEnabled( bool e );


	protected:
		RenderableObject	*m_renderable;
		SDL::Surface		*m_buffer;
		bool				m_enabled;
	};

	class MenuText : public MenuItem {
	public:
		MenuText( RenderableObject *renderable, std::string text, bool enabled = true );
		~MenuText( );

		void process( SDL_Event *e );
		void render( SDL::Color c, SDL::Color *bg );

	private:
		std::string		m_text;
		FontText		*font_text;
	};

}

#endif

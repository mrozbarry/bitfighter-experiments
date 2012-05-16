
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "exceptions.hpp"
#include "sdlutil.hpp"

#ifndef bitfighter_font_hpp
#define bitfighter_font_hpp	1

namespace bitfighter {

	class Font;

	class FontText {
	public:
		FontText( Font *font );
		~FontText( );

		void setColor( SDL_Color fgc );
		void setColor( Uint8 r, Uint8 g, Uint8 b );
		SDL_Color getColor( void );

		SDL::Surface *solidText( std::string text );
		SDL::Surface *shadedText( std::string text );
		SDL::Surface *blendedText( std::string text );

		SDL::Surface *getLastSurface( void );

	private:
		Font			*m_font;
		SDL::Surface	*m_cache;
		SDL_Color		m_color;
		SDL_Color		m_background;
	};

	class Font {
	public:
		Font();
		Font( std::string path, int size );
		~Font();

		void load( std::string path, int size );
		int getSize( void );
		std::string getFontFamily( void );
		std::string getFontStyle( void );

		TTF_Font *getFont();

	private:
		TTF_Font	*m_font;
		int			m_size;
		std::string	m_familyname;
		std::string	m_fontstyle;
	};

}

#endif /* bitfighter_font_hpp */


#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <sstream>
#include "exceptions.hpp"
#include "point.hpp"

#ifndef bitfighter_sdlutil_hpp
#define bitfighter_sdlutil_hpp	1

namespace bitfighter {

	namespace SDL {

		class Color {
		public:
			Color( const Color& copy );
			Color( Uint8 r, Uint8 g, Uint8 b );
			Color( Uint8 gray );
			Color( std::string htmlcolor );

			SDL_Color toSDLColor( void );
			float *toGLColor4vf( float alpha = 1.0f );

			Uint8		r, g, b;
		private:
			bool setColorByName( std::string colorname );

			float		m_glcolor[4];
		};

		class Rect {
		public:
			Rect( const Rect& copy );
			Rect( Pointf p1, Pointf p2 );
			Rect( Pointf p1, float _w, float _h );
			Rect( float _x, float _y, float _w, float _h );
			Rect( float _w, float _h );
			Rect( SDL_Rect r );

			Pointf bottomleft( void );
			Pointf topleft( void );
			Pointf topright( void );
			Pointf bottomright( void );

			bool contains( Pointf p );

			SDL_Rect toSDLRect( void );

			float	x, y, w, h;
		};

		class Surface {
		public:
			Surface( SDL_Surface *surface );
			Surface( Surface *copySource );
			Surface( int w, int h, int depth, bool alpha = false );
			Surface( std::string bmp_path );
			~Surface( );

			SDL_Surface *surface( void );
			void blit( Surface *dest, SDL_Rect *region );

			void fillColor( SDL::Color c );

			int w( void );
			int h( void );

			int w_pow2( void );
			int h_pow2( void );

			void setClip( int x, int y, int w, int h );
			void setClip( SDL_Rect r );
			void resetClip( void );
			SDL_Rect getClip( void );

			void openglBindTexture( void );

			static int next_pow2( int num );

		private:
			SDL_Surface		*m_surface;
			SDL_Rect		m_clip;
			bool			m_hastexture;
			GLuint			m_texture;
		};

	}

}

#endif /* bitfighter_sdlutil_hpp */

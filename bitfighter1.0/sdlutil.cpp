
#include "sdlutil.hpp"
#include <cmath>

namespace bitfighter {

	namespace SDL {

		Surface::Surface( int w, int h, int depth, bool alpha )
			: m_surface( NULL )
			, m_hastexture( false )
		{
			Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
#endif
			if( !alpha ) amask = 0;
			this->m_surface = SDL_CreateRGBSurface(
				0, w, h, depth,
				rmask, gmask, bmask, amask
			);
			if( !this->m_surface ) { /* Throw an exception */ }
			this->resetClip( );
		}

		Surface::Surface( std::string bmp_path )
			: m_surface( NULL )
			, m_hastexture( false )
		{
			this->m_surface = SDL_LoadBMP( bmp_path.c_str() );
			if( !this->m_surface ) { /* Throw an exception */ }
			this->resetClip( );
		}

		Surface::~Surface( )
		{
			if( this->m_surface ) SDL_FreeSurface( this->m_surface );
			if( this->m_hastexture ) glDeleteTextures( 1, &this->m_texture );
		}

		SDL_Surface *Surface::surface( void )
		{
			return this->m_surface;
		}

		void Surface::blit( Surface *dest, SDL_Rect *region )
		{
			SDL_BlitSurface( this->m_surface, &this->m_clip, dest->surface(), region );
		}

		int Surface::w( void )
		{
			return this->m_surface->w;
		}

		int Surface::h( void )
		{
			return this->m_surface->h;
		}

		void Surface::setClip( int x, int y, int w, int h )
		{
			this->m_clip.x = x;
			this->m_clip.y = y;
			this->m_clip.w = w;
			this->m_clip.h = h;
		}

		void Surface::setClip( SDL_Rect r )
		{
			this->m_clip = r;
		}
		
		void Surface::resetClip( void )
		{
			if( !this->m_surface ) return; // Throw an exception, too?
			this->m_clip.x = 0;
			this->m_clip.y = 0;
			this->m_clip.w = this->m_surface->w;
			this->m_clip.h = this->m_surface->h;
		}

		SDL_Rect Surface::getClip( void )
		{
			return this->m_clip;
		}

		void Surface::openglBindTexture( void )
		{
			if( !this->m_hastexture ) {
				int w = (int)std::pow(2, std::ceil( std::log((float)this->m_surface->w) / std::log(2.0f) ) );

				SDL_Surface* newSurface = SDL_CreateRGBSurface(
					0, w, w, 24,
					0xff000000, 0x00ff0000, 0x0000ff00, 0
				);
				SDL_BlitSurface( this->m_surface, 0, newSurface, 0);

				glGenTextures( 1, &this->m_texture );
				glBindTexture( GL_TEXTURE_2D, this->m_texture );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, w, w, 0, GL_RGB, GL_UNSIGNED_BYTE, newSurface->pixels );
				SDL_FreeSurface( newSurface );
				this->m_hastexture = true;
			} else { glBindTexture( GL_TEXTURE_2D, this->m_texture ); }
		}

	}

}

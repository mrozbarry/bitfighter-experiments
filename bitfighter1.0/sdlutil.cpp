
#include "sdlutil.hpp"
#include <cmath>
#include <cassert>

namespace bitfighter {

	namespace SDL {

		/* SDL::Surface */
		Surface::Surface( SDL_Surface *surface )
			: m_surface( surface )
			, m_hastexture( false )
		{
			if( !this->m_surface ) { throw new SDLException( "SDL::Surface" ); }
			this->resetClip( );
		}

		Surface::Surface( Surface *copySource )
			: m_surface( NULL )
			, m_hastexture( false )
		{
			Uint32 rmask, gmask, bmask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
#endif
			this->m_surface = SDL_CreateRGBSurface(
				0, copySource->w(), copySource->h(), 24,
				rmask, gmask, bmask, 0
			);
			if( !this->m_surface ) { throw new SDLException( "SDL::Surface" ); }
			SDL_BlitSurface( copySource->surface(), NULL, this->m_surface, NULL );
			this->setClip( copySource->getClip() );
		}

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
			if( !this->m_surface ) { throw new SDLException( "SDL::Surface" ); }
			this->resetClip( );
		}

		Surface::Surface( std::string bmp_path )
			: m_surface( NULL )
			, m_hastexture( false )
		{
			this->m_surface = SDL_LoadBMP( bmp_path.c_str() );
			if( !this->m_surface ) { throw new SDLException( "SDL::Surface" ); }
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
			if( !this->m_surface ) { throw new BitfighterException( "Surface", "Null surface" ); }
			return this->m_surface->w;
		}

		int Surface::h( void )
		{
			if( !this->m_surface ) { throw new BitfighterException( "Surface", "Null surface" ); }
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
			assert( this->m_surface != NULL );
			int glerror = 0;
			if( !this->m_hastexture ) {
				int w = (int)std::pow(2, std::ceil( std::log((float)this->m_surface->w) / std::log(2.0f) ) );

				int bpp;
				Uint32 Rmask, Gmask, Bmask, Amask;
				SDL_PixelFormatEnumToMasks(
					SDL_PIXELFORMAT_ABGR8888, &bpp,
					&Rmask, &Gmask, &Bmask, &Amask
				);

				int glw = Surface::next_pow2( this->m_surface->w );
				int glh = Surface::next_pow2( this->m_surface->h );
        
				/* Create surface that will hold pixels passed into OpenGL. */
				SDL_Surface *img_rgba8888 = SDL_CreateRGBSurface(0,
					glw, glh, bpp,
					Rmask, Gmask, Bmask, Amask
				);

				SDL_SetSurfaceAlphaMod( this->m_surface, 0xFF );
				SDL_SetSurfaceBlendMode( this->m_surface, SDL_BLENDMODE_NONE );

				SDL_BlitSurface( this->m_surface, NULL, img_rgba8888, NULL );

				glGenTextures( 1, &this->m_texture );
				glBindTexture( GL_TEXTURE_2D, this->m_texture );
				//glTexImage2D( GL_TEXTURE_2D, 0, /*GL_DEPTH_COMPONENT24*/3, w, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->m_surface->pixels );
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, glw, glh, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_rgba8888->pixels );
				glerror = GLException::glError(); if( glerror != 0 ) throw new GLException( "Surface::openglBindTexture::glTexImage2D", glerror, __FILE__, __LINE__ );
        
				SDL_FreeSurface(img_rgba8888);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
				glerror = GLException::glError();
				if( glerror != 0 ) throw new GLException( "Surface::openglBindTexture::Importing raw texture", glerror, __FILE__, __LINE__ );
				//SDL_FreeSurface( newSurface );
				this->m_hastexture = true;
			}
			glBindTexture( GL_TEXTURE_2D, this->m_texture );
		}

		int Surface::next_pow2( int num ) {
			int p2 = 1;
			while( p2 < num ) p2 <<= 1;
			return p2;
		}

	}

}

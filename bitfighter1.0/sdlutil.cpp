
#include "sdlutil.hpp"
#include <cmath>
#include <cassert>
#include <utility>

namespace bitfighter {

	namespace SDL {

		/* Color name list */
#ifndef NUM_COLOR_NAMES
#		define NUM_COLOR_NAMES	34
#endif
		const std::pair< std::string, Color > colorNames[NUM_COLOR_NAMES] = {
			std::pair< std::string, Color >( "red", Color(255,0,0) ),
			std::pair< std::string, Color >( "green", Color(0,255,0) ),
			std::pair< std::string, Color >( "blue", Color(0,0,255) ),
			std::pair< std::string, Color >( "yellow", Color(255,255,0) ),
			std::pair< std::string, Color >( "cyan", Color(0,255,255) ),
			std::pair< std::string, Color >( "magenta", Color(255,0,255) ),
			std::pair< std::string, Color >( "black", Color(0) ),
			std::pair< std::string, Color >( "white", Color(255) ),

			std::pair< std::string, Color >( "gray20", Color(51) ),
			std::pair< std::string, Color >( "gray40", Color(102) ),
			std::pair< std::string, Color >( "gray50", Color(128) ),
			std::pair< std::string, Color >( "gray70", Color(179) ),
			std::pair< std::string, Color >( "gray80", Color(204) ),

			std::pair< std::string, Color >( "yellow40", Color(102,102,0) ),
			std::pair< std::string, Color >( "orange50", Color(255,128,0) ),
			std::pair< std::string, Color >( "orange67", Color(255,171,0) ),

			std::pair< std::string, Color >( "palered", Color(255,128,128) ),
			std::pair< std::string, Color >( "palegreen", Color(128,255,128) ),
			std::pair< std::string, Color >( "paleblue", Color(128,128,255) ),
			std::pair< std::string, Color >( "palepurple", Color(255,128,255) ),

			std::pair< std::string, Color >( "red30", Color(77,0,0) ),
			std::pair< std::string, Color >( "red35", Color(89,0,0) ),
			std::pair< std::string, Color >( "red40", Color(102,0,0) ),
			std::pair< std::string, Color >( "red50", Color(128,0,0) ),
			std::pair< std::string, Color >( "red60", Color(153,0,0) ),
			std::pair< std::string, Color >( "red80", Color(204,0,0) ),

			std::pair< std::string, Color >( "richgreen", Color(0,89,0) ),
			std::pair< std::string, Color >( "green65", Color(0,166,0) ),
			std::pair< std::string, Color >( "green80", Color(0,204,0) ),

			std::pair< std::string, Color >( "blue40", Color(0,0,102) ),
			std::pair< std::string, Color >( "blue80", Color(0,0,204) ),

			std::pair< std::string, Color >( "menuhelp", Color("green") ),
			std::pair< std::string, Color >( "idleplayerscoreboard", Color("gray50") ),
			std::pair< std::string, Color >( "standardplayerscoreboard", Color("white") )
		};

		/* SDL::Color */
		Color::Color( Color& copy )
			: r( copy.r )
			, g( copy.g )
			, b( copy.b )
		{	}

		Color::Color( Uint8 cr, Uint8 cg, Uint8 cb )
			: r( cr )
			, g( cg )
			, b( cb )
		{	}

		Color::Color( Uint8 gray )
			: r( gray )
			, g( gray )
			, b( gray )
		{	}

		Color::Color( std::string htmlcolor )
		{
			if( htmlcolor[0] == '#' ) {
				union {
					Uint32	mapped;
					Uint8	components[4];
				} colour;
				std::stringstream hex;
				std::string hexvalue;
				hexvalue = htmlcolor.substr(1);
				hex << std::hex << hexvalue;
				hex >> colour.mapped;
				this->r = colour.components[0];
				this->g = colour.components[1];
				this->b = colour.components[2];
			} else {
				if( !setColorByName( htmlcolor ) ) throw new BitfighterException( "SDL::Color", "Param htmlcolor is not hex or a recognized color name" );
			}
		}

		SDL_Color Color::toSDLColor( void )
		{
			SDL_Color ret;
			ret.r = this->r;
			ret.g = this->g;
			ret.b = this->b;
			return ret;
		}

		float *Color::toGLColor4vf( float alpha )
		{
			this->m_glcolor[0] = ((float)this->r) / 256.0f;
			this->m_glcolor[1] = ((float)this->g) / 256.0f;
			this->m_glcolor[2] = ((float)this->b) / 256.0f;
			this->m_glcolor[3] = alpha;
			return &this->m_glcolor[0];
		}

		bool Color::setColorByName( std::string colorname )
		{
			// Convert colorname to all lowercase
			std::string lowersearch;
			for (unsigned int i=0; i < colorname.length(); i++) {
				if (colorname[i] >= 65 && colorname[i] <=90) 
					lowersearch += colorname[i] + 32;
				else
					lowersearch += colorname[i];
			}

			for(int c = 0; c < NUM_COLOR_NAMES; c++) {
				if( colorNames[c].first.compare( lowersearch ) == 0 ) {
					this->r = colorNames[c].second.r;
					this->g = colorNames[c].second.g;
					this->b = colorNames[c].second.b;
					return true;
				}
			}

			return false;
		}


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

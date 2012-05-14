
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>

#ifndef bitfighter_sdlutil_hpp
#define bitfighter_sdlutil_hpp	1

namespace bitfighter {

	namespace SDL {

		class Surface {
		public:
			Surface( int w, int h, int depth, bool alpha = false );
			Surface( std::string bmp_path );
			~Surface( );

			SDL_Surface *surface( void );
			void blit( Surface *dest, SDL_Rect *region );

			int w( void );
			int h( void );

			void setClip( int x, int y, int w, int h );
			void setClip( SDL_Rect r );
			void resetClip( void );
			SDL_Rect getClip( void );

			void openglBindTexture( void );

		private:
			SDL_Surface		*m_surface;
			SDL_Rect		m_clip;
			bool			m_hastexture;
			GLuint			m_texture;
		};

	}

}

#endif /* bitfighter_sdlutil_hpp */

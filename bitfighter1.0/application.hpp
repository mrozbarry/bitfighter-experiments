
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

//#include "authentication.hpp"
//#include "client.hpp"
#include "server.hpp"
#include "thread.hpp"

#include "menu.hpp"

#include <utility>
#include <vector>

#ifndef bitfighter_application_hpp
#define bitfighter_application_hpp	1

/* Number of threads the application juggles */
#ifndef BITFIGHTER_ACTIVE_THREADS
#define BITFIGHTER_ACTIVE_THREADS	4
#endif

namespace bitfighter {

	class application {
	public:
		/* Public Class Enums and Structs */
		/*enum VolumeType {
			SfxVolumeType,
			MusicVolumeType,
			VoiceVolumeType,
			ServerAlertVolumeType
		};*/

		application( int width, int height );
		~application( );

		SDL_Window *getWindow( void );

		SDLThreadMessage *newTask( SDLThreadMessage *task, bool highPriority = false );

		void run( void );

	protected:
		int getShortestThreadingQueue( void );

		//authentication *auth;
		//client *local;

		SDL_Window					*window;
		SDL_GLContext				glctx;
		SDLThread					*threads[BITFIGHTER_ACTIVE_THREADS];


	};

}

#endif

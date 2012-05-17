
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

//#include "authentication.hpp"
//#include "client.hpp"
#include "server.hpp"
#include "thread.hpp"
#include "font.hpp"
#include "window.hpp"

#include <utility>
#include <vector>

#ifndef bitfighter_application_hpp
#define bitfighter_application_hpp	1

/* Number of threads the application juggles */
#ifndef BITFIGHTER_ACTIVE_THREADS
#define BITFIGHTER_ACTIVE_THREADS	4
#endif

namespace bitfighter {

	class Menu;

	class Application {
	public:
		/* Public Class Enums and Structs */
		/*enum VolumeType {
			SfxVolumeType,
			MusicVolumeType,
			VoiceVolumeType,
			ServerAlertVolumeType
		};*/

		struct AppFont {
			std::string	key;
			Font		*font;
		};

		Application( int argc, char *argv[] );
		~Application( );

		SDL::Window *newWindow( SDL::Window *w );

		SDLThreadMessage *newTask( SDLThreadMessage *task, bool highPriority = false );

		void run( void );
		bool dispatchEvents( void );

		void addFont( std::string key, Font *font );
		int getFonts( std::string key, std::vector<Font *> &fonts );

	protected:
		int getShortestThreadingQueue( void );

		int getWindow( Uint32 window_id );
		void closeWindow( Uint32 window_id );

		//authentication *auth;
		//client *local;

		std::vector<SDL::Window *>	windows;

		SDLThread					*threads[BITFIGHTER_ACTIVE_THREADS];
		std::vector<AppFont>		fonts;

	private:
		void parseCommandLine( int argc, char *argv[] );
	};

}

#endif

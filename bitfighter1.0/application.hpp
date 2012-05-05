
#include <SDL.h>
#include "authentication.hpp"
#include "client.hpp"
#include "server.hpp"
#include "thread.hpp"
#include "GameSettings.hpp"
#include "IniFile.hpp"

#include <utility>
#include <vector>

#ifndef bitfighter_application_hpp
#define bitfighter_application_hpp	1

namespace bitfighter {

	class application {
	public:
		/* Public Class Enums and Structs */
		enum VolumeType {
			SfxVolumeType,
			MusicVolumeType,
			VoiceVolumeType,
			ServerAlertVolumeType
		};

		application( );
		~application( );

		SDL_Window *createWindow( int width, int height, int bbp, Uint32 flags, bool makeCurrent = true, std::string name = "" );
		void destroyWindow( std::string name );
		void destroyWindow( SDL_Window *wnd );

	protected:
		authentication *auth;
		client *local;

		std::vector< SDL_Window * > windows;
		std::vector< SDLThread * > threads;

	};

}

#endif


#include <SDL.h>
#include "authentication.hpp"
#include "client.hpp"
#include "server.hpp"
#include "GameSettings.hpp"
#include "IniFile.hpp"

#ifndef bitfighter_application_hpp
#define bitfighter_application_hpp	1

namespace bitfighter {

	class application {
	public:
		application();
		application( int width, int height, int bpp, int flags );

	protected:
		virtual void startup( void );
		virtual void shutdown( void );

		authentication *auth;
		client *local;
	};

}

#endif

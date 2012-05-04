
#include <SDL.h>
#include <SDL_thread.h>
#include <deque>
#include <ctime>

#ifndef bitfighter_thread_hpp
#define bitfighter_thread_hpp	1

namespace bitfighter {

	class SDLThreadMessage {
	public:
		SDLThreadMessage();
		~SDLThreadMessage( );

		int timestamp;
		void *data;
		bool quitMessage;
	};

	class SDLThreadQuit : public SDLThreadMessage {
	public:
		SDLThreadQuit();
		~SDLThreadQuit();
	};

	class SDLThread {
	public:
		SDLThread();
		~SDLThread();

		void run( void (*func)(void *arg) );
		bool join( void );

		void postMessage( SDLThreadMessage *msg );
		int pollMessages( void );

		virtual bool processMessage( SDLThreadMessage *msg );

	protected:
		SDL_Thread	*thread;
		SDL_mutex	*mutex;
		std::deque<SDLThreadMessage *> messageQueue;

	private:
		static void background( void *arg );
	};

}

#endif

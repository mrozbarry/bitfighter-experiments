
#include <SDL.h>
#include <SDL_thread.h>
#include <deque>
#include <ctime>

#ifndef bitfighter_thread_hpp
#define bitfighter_thread_hpp	1

namespace bitfighter {

	// Forward declare the thread
	class SDLThread;

	// This class should be extended for different messages!!!
	class SDLThreadMessage {
	public:
		SDLThreadMessage();
		~SDLThreadMessage( );

		virtual void process( SDLThread *thread );

		Uint32 timestamp( void );
		bool isFinished( void );

		bool deleteAfterRead;

	private:
		Uint32		m_timestamp;
		bool		m_done;
		SDL_mutex	*m_lock;
	};

	class SDLThread {
	public:
		SDLThread();
		~SDLThread();

		bool run( void );
		void join( void );

		unsigned int backlog( void );

		void postMessage( SDLThreadMessage *msg );
		int pollMessages( void );

		bool processMessage( SDLThreadMessage *msg );

		int lock( void );
		int unlock( void );

		static int background( void *arg );

	protected:
		SDL_Thread						*thread;
		SDL_mutex						*mutex;
		std::deque<SDLThreadMessage *>	messageQueue;
	};

}

#endif

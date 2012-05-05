
#include "thread.hpp"

namespace bitfighter {

	// SDLThreadMessage
	SDLThreadMessage::SDLThreadMessage()
		: deleteAfterRead(true)
	{
		this->m_timestamp = (Uint32)std::time(NULL);
		this->m_lock = SDL_CreateMutex();
	}

	SDLThreadMessage::~SDLThreadMessage( )
	{
		SDL_DestroyMutex( this->m_lock );
	}

	void SDLThreadMessage::process( void )
	{
		SDL_mutexP( this->m_lock );
		// No nothing, just report being done
		this->m_done = true;
		SDL_mutexV( this->m_lock );
	}

	Uint32 SDLThreadMessage::timestamp( void )
	{
		return this->m_timestamp;
	}

	bool SDLThreadMessage::isFinished( void )
	{
		bool test = false;
		SDL_mutexP( this->m_lock );
		test = this->m_done;
		SDL_mutexV( this->m_lock );
		return test;
	}

	// SDLThread
	SDLThread::SDLThread()
		: thread(NULL)
		, mutex(NULL)
	{	}

	SDLThread::~SDLThread()
	{
		if( this->thread != NULL ) this->join();
	}

	bool SDLThread::run( void )
	{
		// Might be appropriate to throw an exception?
		if( this->thread != NULL ) this->join();

		this->messageQueue.clear();
		this->mutex = SDL_CreateMutex();
		if( !this->mutex ) return false;
		this->thread = SDL_CreateThread( SDLThread::background, NULL, (void *)this );
		if( !this->thread ) return false;
		return true;
	}

	void SDLThread::join( void )
	{
		if( this->thread ) {
			this->postMessage( NULL );
			int status;
			SDL_WaitThread( this->thread, &status );
		}
		SDL_DestroyMutex( this->mutex );
	}

	void SDLThread::postMessage( SDLThreadMessage *msg )
	{
		if( !this->thread ) return;
		this->lock();
			this->messageQueue.push_back( msg );
		this->unlock();
	}

	int SDLThread::lock( void )
	{
		return SDL_mutexP( this->mutex );
	}

	int SDLThread::unlock( void )
	{
		return SDL_mutexV( this->mutex );
	}

	int SDLThread::background( void *arg ) {
		SDLThread *me = (SDLThread *)arg;
		bool keepRunning = true;
		while( keepRunning ) {
			Uint32 wait_ms = 500;
			me->lock();
			if( me->messageQueue.size() > 0 ) {
				if( me->messageQueue[0] ) {		// If we have a valid message, let's process it
					SDLThreadMessage *msg = me->messageQueue[0];
					me->messageQueue.pop_front();
					msg->process();
					if( msg->deleteAfterRead ) delete msg;
					wait_ms = 50;
				} else {						// If we get a NULL message, it means it's time to get the frig out
					keepRunning = false;
					wait_ms = 0;
				}
			}
			me->unlock();
			if( wait_ms > 0 ) SDL_Delay( wait_ms );
		}
		return 0;
	}

}

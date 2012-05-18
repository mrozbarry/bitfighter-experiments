
#include "application.hpp"
#include "menu.hpp"
#include "menuitem.hpp"
#include "renderable_box.hpp"

namespace bitfighter {

	Application::Application( int argc, char *argv[] )
	{
		if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ) { throw new SDLException("Application"); }

		if( TTF_Init() < 0 ) { throw new TTFException("Application"); }

		for( int i = 0; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			this->threads[i] = new SDLThread();
		}
	}

	Application::~Application( )
	{
		unsigned int i = 0;
		for(i=0; i < this->fonts.size(); i++ ) {
			delete this->fonts[i].font;
		}

		for(i = 0; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			delete this->threads[i];
		}

		for(i = 0; i < this->windows.size(); i++) {
			delete this->windows[i];
		}

		TTF_Quit();
		SDL_Quit();
	}

	SDL::Window *Application::newWindow( SDL::Window *w )
	{
		if( !w ) throw new BitfighterException( "Application", "Cannot add NULL window" );
		this->windows.push_back( w );
		return w;
	}

	SDLThreadMessage *Application::newTask( SDLThreadMessage *task, bool highPriority )
	{
		int useQueue = this->getShortestThreadingQueue();
		this->threads[useQueue]->postMessage( task );
		return task;
	}

	void Application::run( void )
	{
		for(int i=0; i < 100; i++) {
			this->windows[0]->newRenderable(
				new RenderableBox( Pointf(float(rand() % 800),float(rand() % 600)), Pointf(float(rand() % 800), float(rand() % 600)), SDL::Color(rand()%255,rand()%255,rand()%255) )
			);
		}
		this->windows[0]->newRenderable( new RenderableBox( Pointf( 50.0f,50.0f), Pointf(250.0f, 250.0f), new SDL::Surface( "../contrib/testimg.bmp" ) ) );

		while( this->dispatchEvents() ) {
			for(unsigned int i=0; i < this->windows.size(); i++) {
				this->windows[i]->paint();
			}
		}
	}

	bool Application::dispatchEvents( void )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) ) {
			switch( e.type ) {
			case SDL_QUIT:
				return false;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				closeWindow( e.window.windowID );
				if( this->windows.size() == 0 ) return false;
				break;
			}
		}
		return true;
	}

	void Application::addFont( std::string key, Font *font )
	{
		if( !font ) { return; } // Also throw an exception?
		AppFont af;
		af.key = key;
		af.font = font;
		this->fonts.push_back( af );
	}

	int Application::getFonts( std::string key, std::vector<Font *> &fontlist )
	{
		fontlist.clear();
		for(unsigned int i=0; i < this->fonts.size(); i++ ) {
			if( key.compare( this->fonts[i].key ) == 0 ) fontlist.push_back( this->fonts[i].font );
		}
		return (int)fontlist.size();
	}

	int Application::getShortestThreadingQueue( void )
	{
		unsigned int num = this->threads[0]->backlog();
		int index = 0;
		for( int i = 1; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			unsigned int n = this->threads[0]->backlog();
			if( n < num ) { num = n; index = i; }
		}
		return index;
	}

	int Application::getWindow( Uint32 window_id )
	{
		for( unsigned int i=0; i < this->windows.size(); i++ ) {
			if( this->windows[i]->getId() == window_id ) return (int)i;
		}
		return -1;
	}

	void Application::closeWindow( Uint32 window_id )
	{
		int index = this->getWindow( window_id );
		delete this->windows[index];
		this->windows.erase( this->windows.begin() + index );
	}

	void Application::parseCommandLine( int argc, char *argv[] )
	{
		// Do something here?
	}
}

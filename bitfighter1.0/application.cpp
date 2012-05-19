
#include "application.hpp"
#include "menuitem.hpp"
#include "renderable_box.hpp"
#include "renderable_menu.hpp"

namespace bitfighter {

	Application::Application( int argc, char *argv[] )
		: m_window_active(NULL)
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

	Window *Application::newWindow( Window *w )
	{
		if( !w ) throw new BitfighterException( "Application", "Cannot add NULL window" );
		this->windows.push_back( w );
		this->m_window_active = w;
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
		Window *wnd = this->newWindow( new GLWindow( this, "bitfighter1.0", 800, 600 ) );
		this->addFont( "menu", new Font( "../contrib/zrnic rg.otf", 34 ) ); // Should be moved into the Application
		RenderableMenu *rmenu = new RenderableMenu( wnd, Pointf(30, 20), new SDL::Color("blue80"), new SDL::Color("yellow40") );
		rmenu->addItem( new MenuText( rmenu, "Join LAN/Internet Game" ) );
		rmenu->addItem( new MenuText( rmenu, "Host Game" ) );
		rmenu->addItem( new MenuText( rmenu, "Instructions" ) );
		rmenu->addItem( new MenuText( rmenu, "Options" ) );
		rmenu->addItem( new MenuText( rmenu, "Highscores" ) );
		rmenu->addItem( new MenuText( rmenu, "Level Editor" ) );
		rmenu->addItem( new MenuText( rmenu, "Credits" ) );
		rmenu->addItem( new MenuText( rmenu, "Exit" ) );
		rmenu->visible( false );
		wnd->newRenderable( rmenu );

		while( this->dispatchEvents() ) {
			for(unsigned int i=0; i < this->windows.size(); i++) {
				this->windows[i]->paint();
			}
		}
	}

	bool Application::dispatchEvents( void )
	{
		SDL_Event e;
		int windex=0;
		while( SDL_PollEvent( &e ) ) {
			switch( e.type ) {
			case SDL_QUIT:
				return false;
				break;
			case SDL_WINDOWEVENT_CLOSE:
				this->closeWindow( e.window.windowID, &e );
				if( this->windows.size() == 0 ) return false;
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				windex = this->getWindow( e.window.windowID );
				if( windex >= 0 ) this->m_window_active = this->windows[windex];
				break;
			default:
				if( this->m_window_active ) this->m_window_active->handleEvents(&e);
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

	void Application::closeWindow( Uint32 window_id, SDL_Event *e )
	{
		int index = this->getWindow( window_id );
		if( window_id == this->m_window_active->getWindowId() ) {
			int wid = (this->windows.size() > 1) ? ((index > 0) ? index-1 : index+1) : -1;
			this->m_window_active = this->windows[wid];
		}
		if( e ) this->windows[index]->handleEvents( e );
		delete this->windows[index];
		this->windows.erase( this->windows.begin() + index );
	}

	void Application::parseCommandLine( int argc, char *argv[] )
	{
		// Do something here?
	}
}

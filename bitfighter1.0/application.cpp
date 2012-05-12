
#include "application.hpp"


namespace bitfighter {

	application::application( int width, int height )
	{
		for( int i = 0; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			this->threads[i] = new SDLThread();
		}

		if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ) {
			// throw new SDLException("Init");
		}

		if( TTF_Init() < 0 ) {
			// throw new TTFException("Init");
		}

		//SDL_DisplayMode mode;
		//SDL_GetCurrentDisplayMode(0, &mode);

		this->window = SDL_CreateWindow(
			"Bitfighter",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN
		);

		glctx = SDL_GL_CreateContext( this->window );

		SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		SDL_Surface *icon = SDL_LoadBMP("bficon.bmp");
		if(icon != NULL) {
			SDL_SetColorKey(icon, 1, SDL_MapRGB(icon->format, 0, 0, 0));
			SDL_SetWindowIcon( this->window, icon);
		}
	}

	application::~application( )
	{
		for( int i = 0; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			delete this->threads[i];
		}

		TTF_Quit();
		SDL_Quit();
	}

	SDL_Window *application::getWindow( void )
	{
		return this->window;
	}

	SDLThreadMessage *application::newTask( SDLThreadMessage *task, bool highPriority )
	{
		int useQueue = this->getShortestThreadingQueue();
		this->threads[useQueue]->postMessage( task );
		return task;
	}

	void application::run( void )
	{
		Menu *main = new Menu();
		while( !main->dispatchEvents() ) {
			SDL_GL_SwapWindow( this->window );
		}
	}

	int application::getShortestThreadingQueue( void )
	{
		unsigned int num = this->threads[0]->backlog();
		int index = 0;
		for( int i = 1; i < BITFIGHTER_ACTIVE_THREADS; i++ ) {
			unsigned int n = this->threads[0]->backlog();
			if( n < num ) { num = n; index = i; }
		}
		return index;
	}

}


#include "window.hpp"

namespace bitfighter {
	
	namespace SDL {

		Window::Window( std::string title, int w, int h, Uint32 flags )
			: m_fps( 0 )
			, m_fps2( 0.0f )
			, m_deltaCount( 0 )
			, m_frameCount( 0 )
			, m_lastPaint( 0 )
		{
			this->m_window = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				w, h, flags
			);
		}

		Window::~Window( )
		{ SDL_DestroyWindow( this->m_window ); }

		SDL_Window *Window::getWindow( void )
		{ return this->m_window; }

		void Window::show( void )
		{ SDL_ShowWindow( this->m_window ); }

		void Window::hide( void )
		{ SDL_HideWindow( this->m_window ); }

		void Window::resizeWindow( int w, int h )
		{ SDL_SetWindowSize( this->m_window, w, h ); }

		void Window::paint( void )
		{
			Uint32 ticks = SDL_GetTicks();
			Uint32 delta = ticks - this->m_lastPaint;

			this->m_deltaCount += delta;
			if( this->m_deltaCount > 1000 ) {
				this->m_fps = this->m_frameCount;
				this->m_frameCount = 0;
				this->m_deltaCount -= 1000;

				std::stringstream fpsdata;
				fpsdata << "Bitfighter Renderer Test; realfps=" << this->m_fps << ", estimatedfps=" << this->m_fps2;
				SDL_SetWindowTitle( this->m_window, fpsdata.str().c_str() );
			}
			this->m_frameCount += 1;
			this->m_fps2 = 1000.0f / (float)delta * 1.0f;  // frames / second = fps | 1000/milliseconds*frames

			this->pre_paint( );
			this->do_paint( delta );
			this->post_paint( );

			this->m_lastPaint = ticks;
		}

		bool Window::handleEvents( SDL_Event *e )
		{ return true; }

		Uint32 Window::getId( void )
		{ return SDL_GetWindowID( this->m_window ); }

		int Window::getRealFPS( void )
		{ return this->m_fps; }

		float Window::getEstimatedFPS( void )
		{ return this->m_fps2; }

		RenderableObject *Window::newRenderable( RenderableObject *renderable )
		{
			if( !renderable ) return NULL;
			this->m_renderables.push_back( renderable );
			return renderable;
		}

		void Window::pre_paint( void )
		{ return; }
		
		void Window::do_paint( Uint32 delta_milliseconds )
		{ return; }
		
		void Window::post_paint( void )
		{ return; }
		
		// --- OpenGL Window
		GLWindow::GLWindow( std::string title, int w, int h )
			: Window( title, w, h, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL )
		{
			this->m_context = SDL_GL_CreateContext( this->m_window );
			this->makeCurrent();

			SDL_GL_SetSwapInterval(1);

			SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
			SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

			glClearColor( 0, 0, 0, 0 );

			glViewport( 0, 0, 800, 600 );

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity( );

			glOrtho(0, 800, 0, 600, 0, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glLineWidth( 2.0f );

			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_BLEND);

			glEnable(GL_TEXTURE_2D);
		}

		GLWindow::~GLWindow( )
		{
			for(unsigned int i=0; i < this->m_renderables.size(); i++) {
				delete this->m_renderables[i];
			}
			SDL_GL_DeleteContext( this->m_context );
		}

		void GLWindow::pre_paint( void )
		{ this->makeCurrent(); }
		
		void GLWindow::do_paint( Uint32 delta_milliseconds )
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glLoadIdentity();

			for(unsigned int i=0; i < this->m_renderables.size(); i++) {
				this->m_renderables[i]->draw( );
			}
		}
		
		void GLWindow::post_paint( void )
		{ SDL_GL_SwapWindow( this->m_window ); }
		
		void GLWindow::makeCurrent( void )
		{ SDL_GL_MakeCurrent( this->m_window, this->m_context ); }

		// --- SDL_Renderer Window
		RendererWindow::RendererWindow( std::string title, int w, int h, int driver, Uint32 flags )
			: Window( title, w, h )
		{ this->m_renderer = SDL_CreateRenderer( this->m_window, driver, flags ); }
			
		RendererWindow::~RendererWindow( )
		{ SDL_DestroyRenderer( this->m_renderer ); }

		SDL_Renderer *RendererWindow::getRenderer( void )
		{ return this->m_renderer; }

		void RendererWindow::do_paint( Uint32 delta_milliseconds )
		{ return; }

		void RendererWindow::post_paint( void )
		{ SDL_RenderPresent( this->m_renderer ); }


	}

}
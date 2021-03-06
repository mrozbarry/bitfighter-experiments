
#include <SDL.h>
#include <vector>
#include <string>
#include "sdlutil.hpp"

#ifndef bitfighter_window_hpp
#define bitfighter_window_hpp	1

namespace bitfighter {

	class Application;
	class RenderableObject;

	class Window {
	public:
		Window( Application *app, std::string title, int w, int h, Uint32 flags = SDL_WINDOW_SHOWN );
		~Window( );

		Application *getApplication( void );
		SDL_Window *getWindow( void );
		Uint32 getWindowId( void );

		void show( void );
		void hide( void );
		void paint( void );
		void resizeWindow( int w, int h );
		Uint32 getId( void );

		int getRealFPS( void );
		float getEstimatedFPS( void );

		RenderableObject *newRenderable( RenderableObject *renderable );

		virtual bool handleEvents( SDL_Event *e );

	protected:
		virtual void pre_paint( void );
		virtual void do_paint( Uint32 delta_milliseconds );
		virtual void post_paint( void );

		SDL_Window						*m_window;
		Uint32							m_lastPaint;
		Uint32							m_deltaCount;
		Uint32							m_frameCount;
		int								m_fps;
		float							m_fps2;
		std::vector<RenderableObject *>	m_renderables;
		Application						*m_application;
	};

	class GLWindow : public Window {
	public:
		GLWindow( Application *app, std::string title, int w, int h );
		~GLWindow( );

	protected:
		virtual void pre_paint( void );
		virtual void do_paint( Uint32 delta_milliseconds );
		virtual void post_paint( void );
		SDL_GLContext	m_context;

	private:
		void makeCurrent( void );
	};

	class RendererWindow : public Window {
	public:
		RendererWindow( Application *app, std::string title, int w, int h, int driver = -1, Uint32 flags = 0 );
		~RendererWindow( );

		SDL_Renderer *getRenderer( void );

	protected:
		virtual void do_paint( Uint32 delta_milliseconds );
		virtual void post_paint( void );

		SDL_Renderer	*m_renderer;
	};

}

#endif /* bitfighter_window_hpp */
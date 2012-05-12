
#include <SDL.h>
#include <string>
#include "menu.hpp"

#ifndef bitfighter_menuitem_hpp
#define bitfighter_menuitem_hpp	1

namespace bitfighter {

	class MenuItem {
	public:
		MenuItem( );
		~MenuItem( );

		virtual void process( SDL_Event *e );
		virtual void render( void );
		SDL_Surface *getBuffer( void );

		Menu			*subMenu;

	protected:
		SDL_Surface		*m_buffer;
	};

	class MenuText : public MenuItem {
	public:
		MenuText( std::string text );
		~MenuText( );

		void process( SDL_Event *e );
		void render( void );

	private:
		std::string		m_text;
	};

	class MenuToggle : public MenuItem {
	public:
		MenuToggle( std::string text, std::string text_true = "On", std::string text_false = "Off" );
		~MenuToggle( );

		void process( SDL_Event *e );
		void render( void );
		void set( bool value );
		bool get( void );

	private:
		std::string		m_text, m_on, m_off;
	};

	class MenuPlainInput : public MenuItem {
	public:
		MenuPlainInput( std::string prompt );
		MenuPlainInput( std::string prompt, std::string filter );
		~MenuPlainInput( );
		
		void process( SDL_Event *e );
		void render( void );
		void set( std::string value );
		std::string get( void );

	private:
		std::string		m_prompt, m_text, m_filter;
	};

	class MenuPasswordInput : public MenuItem {
	public:
		MenuPasswordInput( std::string prompt, char mask = '*' );
		~MenuPasswordInput( );
		
		void process( SDL_Event *e );
		void render( void );
		void set( std::string value );
		std::string get( void );
		// TODO add a get_md5 or whatever for keeping the password private

	private:
		std::string		m_prompt, m_password;
		char			m_mask;
	};

}

#endif

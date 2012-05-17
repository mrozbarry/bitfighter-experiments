
#include <SDL.h>
#include <string>
#include "menu.hpp"
#include "font.hpp"
#include "sdlutil.hpp"
#include "application.hpp"

#ifndef bitfighter_menuitem_hpp
#define bitfighter_menuitem_hpp	1

namespace bitfighter {

	class MenuItem {
	public:
		enum ItemType {
			// Note: All new widget types should be dealt with here
			IT_StaticText = 0,
			IT_Toggable,
			IT_TextInput,
			IT_PasswordInput,
			IT_SliderInput,

			IT_UpperBounds
		};

		MenuItem( Application *app, ItemType it );
		~MenuItem( );

		virtual void process( SDL_Event *e );
		virtual void render( void );
		SDL::Surface *getBuffer( void );

		ItemType getType( void );

	protected:
		Application		*m_app;
		SDL::Surface	*m_buffer;
		ItemType		m_itemtype;
	};

	class MenuText : public MenuItem {
	public:
		MenuText( Application *app, std::string text );
		~MenuText( );

		void process( SDL_Event *e );
		void render( void );

	private:
		std::string		m_text;
	};

	class MenuToggle : public MenuItem {
	public:
		MenuToggle( Application *app, std::string text, std::string text_true = "On", std::string text_false = "Off", bool value = false );
		~MenuToggle( );

		void process( SDL_Event *e );
		void render( void );
		
		void set( bool value );
		bool get( void );

	private:
		std::string		m_text, m_on, m_off;
		bool			m_value;
	};

	class MenuPlainInput : public MenuItem {
	public:
		MenuPlainInput( Application *app, std::string prompt );
		MenuPlainInput( Application *app, std::string prompt, std::string filter );
		~MenuPlainInput( );
		
		void process( SDL_Event *e );
		void render( void );
		
		void set( std::string value );
		std::string get( void );

	private:
		std::string		m_prompt, m_filter;
		std::string		m_value;
	};

	class MenuPasswordInput : public MenuItem {
	public:
		MenuPasswordInput( Application *app, std::string prompt, char mask = '*' );
		~MenuPasswordInput( );
		
		void process( SDL_Event *e );
		void render( void );
		
		void set( std::string value );
		std::string get( void );
		// TODO add a get_md5 or whatever for keeping the password private

	private:
		std::string		m_prompt;
		std::string		m_password;
		char			m_mask;
	};

	class MenuSlider : public MenuItem {
	public:
		MenuSlider( Application *app, std::string text, float min, float max, float step = 1.0f );
		~MenuSlider( );

		void process( SDL_Event *e );
		void render( void );

		void set( float value );
		float get( void );

	private:
		std::string		m_text;
		float			m_min, m_max, m_step;
		float			m_value;
	};
}

#endif

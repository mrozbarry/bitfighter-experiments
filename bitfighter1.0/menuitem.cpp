
#include "menuitem.hpp"

namespace bitfighter {

	/* MenuItem Base Class */
	MenuItem::MenuItem( )
		: m_buffer( NULL )
	{	}

	MenuItem::~MenuItem( )
	{
		if( this->m_buffer ) SDL_FreeSurface( this->m_buffer );
	}

	void MenuItem::process( SDL_Event *e )
	{
		return;
	}

	void MenuItem::render( void )
	{
		return;
	}

	SDL_Surface *MenuItem::getBuffer( void )
	{
		return this->m_buffer;
	}

	/* Plain text in the menu */
	MenuText::MenuText( std::string text )
		: m_text( text )
	{
		this->m_buffer = NULL; // SDL_ttf?
	}

	MenuText::~MenuText( )
	{	}

	void MenuText::process( SDL_Event *e )
	{
		return;
	}

	void MenuText::render( void )
	{
		return;
	}

	/* Menu On/Off Switch */
	MenuToggle::MenuToggle( std::string text, std::string text_true, std::string text_false )
		: m_text( text )
		, m_on( text_true )
		, m_off( text_false )
	{
		this->m_buffer = NULL;
	}

	MenuToggle::~MenuToggle( )
	{	}

	void MenuToggle::process( SDL_Event *e )
	{
		return;
	}

	void MenuToggle::render( void )
	{
		return;
	}
	
	void MenuToggle::set( bool value )
	{
		// do a toggle
	}

	bool MenuToggle::get( void )
	{
		return false;
	}

	/* Menu Plain-text Input */
	MenuPlainInput::MenuPlainInput( std::string prompt )
		: m_prompt( prompt )
		, m_text( "" )
		, m_filter( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=!@#$%^&*()_+[];',./\\{}|:\"<>?" )
	{
		this->m_buffer = NULL;
	}

	MenuPlainInput::MenuPlainInput( std::string prompt, std::string filter )
		: m_prompt( prompt )
		, m_text( "" )
		, m_filter( filter )
	{
		this->m_buffer = NULL;
	}

	MenuPlainInput::~MenuPlainInput( )
	{	}
		
	void MenuPlainInput::process( SDL_Event *e )
	{
		return;
	}

	void MenuPlainInput::render( void )
	{
		return;
	}

	void MenuPlainInput::set( std::string value )
	{
		this->m_text = value;
	}

	std::string MenuPlainInput::get( void )
	{
		return this->m_text;
	}

	/* Same as above, but with a character mask for passwords */
	MenuPasswordInput::MenuPasswordInput( std::string prompt, char mask )
		: m_prompt( prompt )
		, m_password( "" )
		, m_mask( mask )
	{
		this->m_buffer = NULL;
	}

	MenuPasswordInput::~MenuPasswordInput( )
	{	}
		
	void MenuPasswordInput::process( SDL_Event *e )
	{
		return;
	}

	void MenuPasswordInput::render( void )
	{
		return;
	}

	void MenuPasswordInput::set( std::string value )
	{
		this->m_password = value;
	}

	std::string MenuPasswordInput::get( void )
	{
		return this->m_password;
	}

}

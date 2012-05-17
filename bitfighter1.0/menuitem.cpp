
#include "menuitem.hpp"
#include "application.hpp"

namespace bitfighter {

	/* MenuItem Base Class */
	MenuItem::MenuItem( Application *app, ItemType it )
		: m_app( app )
		, m_buffer( NULL )
		, m_itemtype( it )
	{
		if( !app ) { throw new BitfighterException( "MenuItem", "Null application" ); }
	}

	MenuItem::~MenuItem( )
	{
		if( this->m_buffer ) delete this->m_buffer;
	}

	void MenuItem::process( SDL_Event *e )
	{
		return;
	}

	void MenuItem::render( void )
	{
		return;
	}

	SDL::Surface *MenuItem::getBuffer( void )
	{
		return this->m_buffer;
	}

	MenuItem::ItemType MenuItem::getType( void )
	{
		return this->m_itemtype;
	}

	/* Plain text in the menu */
	MenuText::MenuText( Application *app, std::string text )
		: MenuItem( app, IT_StaticText )
		, m_text( text + " >" )
	{
		this->m_buffer = NULL; // SDL_ttf?
		this->render( );
	}

	MenuText::~MenuText( )
	{	}

	void MenuText::process( SDL_Event *e )
	{
		return;
	}

	void MenuText::render( void )
	{
		std::vector<Font *> fonts;

		this->m_app->getFonts( "menu", fonts );
		FontText *text = new FontText( fonts[0] );

		text->setColor( SDL::Color("blue20").toSDLColor() );

		text->blendedText( this->m_text );

		this->m_buffer = new SDL::Surface( text->getLastSurface() );

		delete text;
		return;
	}

	/* Menu On/Off Switch */
	MenuToggle::MenuToggle( Application *app, std::string text, std::string text_true, std::string text_false, bool value )
		: MenuItem( app, IT_Toggable )
		, m_text( text )
		, m_on( text_true )
		, m_off( text_false )
		, m_value( value )
	{
		this->render();
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
		this->m_value = value;
	}

	bool MenuToggle::get( void )
	{
		return this->m_value;
	}

	/* Menu Plain-text Input */
	MenuPlainInput::MenuPlainInput( Application *app, std::string prompt )
		: MenuItem( app, IT_TextInput )
		, m_prompt( prompt )
		, m_filter( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=!@#$%^&*()_+[];',./\\{}|:\"<>?" )
	{
		this->m_buffer = NULL;
	}

	MenuPlainInput::MenuPlainInput( Application *app, std::string prompt, std::string filter )
		: MenuItem( app, IT_TextInput )
		, m_prompt( prompt )
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

	/* Same as above, but with a character mask for passwords */
	MenuPasswordInput::MenuPasswordInput( Application *app, std::string prompt, char mask )
		: MenuItem( app, IT_PasswordInput )
		, m_prompt( prompt )
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

}

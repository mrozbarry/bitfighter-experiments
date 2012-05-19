
#include "menuitem.hpp"
#include "renderable.hpp"
#include "application.hpp"

namespace bitfighter {

	/* MenuItem Base Class */
	MenuItem::MenuItem( RenderableObject *renderable, bool enabled )
		: m_renderable( renderable )
		, m_buffer( NULL )
		, m_enabled( enabled )
	{
		if( !m_renderable ) { throw new BitfighterException( "MenuItem", "Null renderable" ); }
	}

	MenuItem::~MenuItem( )
	{
		if( this->m_buffer ) delete this->m_buffer;
	}

	void MenuItem::process( SDL_Event *e )
	{ return; }

	void MenuItem::render( SDL::Color c )
	{ return; }

	SDL::Surface *MenuItem::getBuffer( void )
	{ return this->m_buffer; }

	bool MenuItem::isEnabled( void )
	{ return this->m_enabled; }

	void MenuItem::isEnabled( bool e )
	{ this->m_enabled = e; }

	/* Plain text in the menu */
	MenuText::MenuText( RenderableObject *renderable, std::string text, bool enabled )
		: MenuItem( renderable, enabled )
		, m_text( text + " >" )
	{
		this->m_buffer = NULL;
	}

	MenuText::~MenuText( )
	{	}

	void MenuText::process( SDL_Event *e )
	{ return; }

	void MenuText::render( SDL::Color c, SDL::Color bg )
	{
		std::vector<Font *> fonts;

		this->m_renderable->getWindow()->getApplication()->getFonts( "menu", fonts );
		FontText *text = new FontText( fonts[0] );

		text->setColor( c.toSDLColor() );

		text->blendedText( this->m_text );

		this->m_buffer = new SDL::Surface( text->getLastSurface() );

		delete text;
		return;
	}

}

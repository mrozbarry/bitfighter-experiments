
#include "font.hpp"

namespace bitfighter {

	/* FontText Class */
	FontText::FontText( Font *font )
		: m_font( font )
		, m_cache( NULL )
	{
		this->m_color.r = 255;
		this->m_color.g = 255;
		this->m_color.b = 255;
		this->m_background.r = 255;
		this->m_background.g = 255;
		this->m_background.b = 255;
	}

	FontText::~FontText( )
	{
		if( this->m_cache ) delete this->m_cache;
	}

	void FontText::setColor( SDL_Color fgc )
	{
		this->m_color.r = fgc.r;
		this->m_color.g = fgc.g;
		this->m_color.b = fgc.b;
	}

	void FontText::setColor( Uint8 r, Uint8 g, Uint8 b )
	{
		this->m_color.r = r;
		this->m_color.g = g;
		this->m_color.b = b;
	}

	SDL_Color FontText::getColor( void )
	{
		return this->m_color;
	}

	SDL::Surface *FontText::solidText( std::string text )
	{
		if( this->m_cache ) delete this->m_cache;
		this->m_cache = new SDL::Surface( TTF_RenderText_Solid( m_font->getFont(), text.c_str(), this->m_color ) );
		if( !this->m_cache ) { throw new TTFException( "FontText::solidText" ); }
		return this->m_cache;
	}

	SDL::Surface *FontText::shadedText( std::string text )
	{
		if( this->m_cache ) delete this->m_cache;
		this->m_cache = new SDL::Surface( TTF_RenderText_Shaded( m_font->getFont(), text.c_str(), this->m_color, this->m_background ) );
		if( !this->m_cache ) { throw new TTFException( "FontText::shadedText" ); }
		return this->m_cache;
	}

	SDL::Surface *FontText::blendedText( std::string text )
	{
		if( this->m_cache ) delete this->m_cache;
		this->m_cache = new SDL::Surface( TTF_RenderText_Blended( m_font->getFont(), text.c_str(), this->m_color ) );
		if( !this->m_cache ) { throw new TTFException( "FontText::blendedText" ); }
		return this->m_cache;
	}

	SDL::Surface *FontText::getLastSurface( void )
	{
		return this->m_cache;
	}

	/* Font class */
	Font::Font()
		: m_font( NULL )
		, m_familyname( "" )
		, m_fontstyle( "" )
		, m_size( 0 )
	{	}
	
	Font::Font( std::string path, int size )
		: m_font( NULL )
		, m_familyname( "" )
		, m_fontstyle( "" )
		, m_size( 0 )
	{
		this->load( path, size );
	}

	Font::~Font()
	{
		if( this->m_font ) {
			TTF_CloseFont( this->m_font );
		}
	}

	void Font::load( std::string path, int size )
	{
		if( this->m_font ) {
			TTF_CloseFont( this->m_font );
		}
		this->m_font = TTF_OpenFont( path.c_str(), size );
		if( !this->m_font ) { throw new TTFException( "FontText::shadedText" ); }
		this->m_size = size;
		this->m_familyname = std::string( TTF_FontFaceFamilyName( this->m_font ) );
		this->m_fontstyle = std::string( TTF_FontFaceStyleName( this->m_font ) );
	}

	int Font::getSize( void )
	{
		return this->m_size;
	}

	std::string Font::getFontFamily( void )
	{
		return this->m_familyname;
	}

	std::string Font::getFontStyle( void )
	{
		return this->m_fontstyle;
	}

	TTF_Font *Font::getFont()
	{
		return this->m_font;
	}

};

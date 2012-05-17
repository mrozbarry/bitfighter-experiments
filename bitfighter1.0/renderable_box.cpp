
#include "renderable_box.hpp"

namespace bitfighter {

	RenderableBox::RenderableBox( Pointf topleft, Pointf bottomright, Uint8 r, Uint8 g, Uint8 b )
		: RenderableObject( topleft, -1.0f, true, RenderableObject::RecievesEvents_Never )
		, m_bottomright( bottomright )
	{
		this->m_color.r = r;
		this->m_color.g = g;
		this->m_color.b = b;
	}

	RenderableBox::~RenderableBox()
	{	}

	bool RenderableBox::handleEvent( SDL_Event *e )
	{ return true; }

	void RenderableBox::render( Uint32 delta )
	{
		glBegin( GL_QUADS );

			glColor3i( this->m_color.r, this->m_color.g, this->m_color.b );
			glVertex3f( this->m_position.x, this->m_position.y, this->m_z );
			glVertex3f( this->m_bottomright.x, this->m_position.y, this->m_z );
			glVertex3f( this->m_bottomright.x, this->m_bottomright.y, this->m_z );
			glVertex3f( this->m_position.x, this->m_bottomright.y, this->m_z );

		glEnd( );
	}

}
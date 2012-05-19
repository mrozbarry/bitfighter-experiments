
#include "renderable.hpp"
#include "window.hpp"
#include "exceptions.hpp"

namespace bitfighter {

	RenderableObject::RenderableObject( Window *window, SDL::Rect bounds, float z, bool vis, Uint32 recieves_events )
		: m_bound( bounds )
		, m_z( z )
		, m_visible( vis )
		, m_recieve_events( recieves_events )
		, m_last_render( SDL_GetTicks() )
		, m_window( window )
	{
		if( !this->m_window ) throw new BitfighterException("RenderableObject", "Null window object");
	}

	Window *RenderableObject::getWindow( void )
	{ return this->m_window; }

	bool RenderableObject::visible( void )
	{ return this->m_visible; }

	void RenderableObject::visible( bool toggle )
	{ this->m_visible = toggle; }

	SDL::Rect RenderableObject::boundary( void )
	{ return this->m_bound; }

	void RenderableObject::boundary( SDL::Rect bounds )
	{ this->m_bound = bounds; }

	float RenderableObject::zIndex( void )
	{ return this->m_z; }

	void RenderableObject::zIndex( float z )
	{ this->m_z = z; }

	Uint32 RenderableObject::recieveEvents( void )
	{ return this->m_recieve_events; }

	void RenderableObject::recieveEvents( Uint32 recieveOn )
	{ this->m_recieve_events = recieveOn; }

	bool RenderableObject::recieveEventsOn( Uint32 recieveOn )
	{ return this->m_recieve_events && recieveOn; }

	void RenderableObject::draw( void )
	{
		Uint32 ticks = SDL_GetTicks();
		Uint32 delta = ticks - this->m_last_render;

		this->render( delta );

		this->m_last_render = ticks;
	}

	bool RenderableObject::handleEvent( SDL_Event *e )
	{ return true; }

	void RenderableObject::render( Uint32 delta )
	{ return; }

}

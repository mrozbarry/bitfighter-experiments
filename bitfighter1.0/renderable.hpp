
#include <SDL.h>
#include "point.hpp"

#ifndef bitfighter_renderable_hpp
#define bitfighter_renderable_hpp	1

namespace bitfighter {

	class RenderableObject {
	public:

		static const Uint32 RecievesEvents_Never = 0;
		static const Uint32 RecievesEvents_Visible = 1;
		static const Uint32 RecievesEvents_Active = 2;
		static const Uint32 RecievesEvents_MouseOver = 4;
		static const Uint32 RecievesEvents_Always = RecievesEvents_Visible | RecievesEvents_Active;

		RenderableObject( Pointf pos, float z = 0.0f, bool vis = true, Uint32 recieves_events = RecievesEvents_Visible|RecievesEvents_MouseOver );

		bool visible( void );
		void visible( bool toggle );				

		Pointf position( void );					// Get the position
		void position( Pointf pos );				// Change the position

		float zIndex( void );						// Get the z index
		void zIndex( float z );						// Change the z index (-1.0f to 1.0f)

		Uint32 recieveEvents( void );				// Get the states that the RenderableObject will recieve events
		void recieveEvents( Uint32 recieveOn );		// Change the states that the RenderableObject will recieve events
		bool recieveEventsOn( Uint32 recieveOn );	// Check to see if recieveOn is enough to push an event to this RenderableObject

		void draw( void );							// Do any drawing logic here (in subclasses)
		virtual bool handleEvent( SDL_Event *e );	// Return false if you want this RenderableObject removed

	protected:
		virtual void render( Uint32 delta );

		Pointf		m_position;
		float		m_z;
		bool		m_visible;
		Uint32		m_recieve_events;
		Uint32		m_last_render;
	};

}

#endif /* bitfighter_renderable_hpp */

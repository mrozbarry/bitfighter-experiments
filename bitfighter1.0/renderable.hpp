
#include <SDL.h>
#include "point.hpp"

#ifndef bitfighter_renderable_hpp
#define bitfighter_renderable_hpp	1

namespace bitfighter {

	class Renderable {
	public:
		Renderable( Pointf position, float z = 0.0f );
		~Renderable( );

		virtual void draw( void );

	protected:
		Pointf		m_position;
		float		m_z;
	};

}

#endif /* bitfighter_renderable_hpp */


#include <cmath>

#ifndef bitfighter_point_hpp
#define bitfighter_point_hpp	1

namespace bitfighter {

	class Pointf {
	public:
		Pointf()
		{ /* Nothing here... */ }
			
		Pointf( float px, float py )
		{
			this->x = px;
			this->y = py;
		}

		float distance( Pointf p2 )
		{
			float xdiff = p2.x - this->x;
			float ydiff = p2.y - this->y;
			return (float)std::sqrt( (xdiff*xdiff) + (ydiff*ydiff) );
		}

		float	x, y;
	};
}

#endif /* bitfighter_point_hpp */

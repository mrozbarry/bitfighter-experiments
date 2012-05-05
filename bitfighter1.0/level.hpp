
#include <chipmunk/chipmunk.h>

#ifndef bitfighter_level_hpp
#define bitfighter_level_hpp	1

namespace bitfighter {

	class Level {
	public:
		Level();
		Level( std::string path );
		~Level();

		cpVect	position;
	};

}

#endif

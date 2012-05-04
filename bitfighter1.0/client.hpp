
#include <iostream>
#include "authentication.hpp"

namespace bitfighter {

	class client {
	public:
		client( authentication *auth );
		~client();

		static void idle( client *me );

	private:
		authentication *user;
	};

}

#include <iostream>
#include <fstream>
#include "application.hpp"

using namespace bitfighter;

int main(int argc, char* argv[])
{
	try {
		application app( 800, 600 );
		app.run();
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}



#include <iostream>
#include <fstream>
#include "application.hpp"
#include "window.hpp"
#include "exceptions.hpp"

using namespace bitfighter;

int main(int argc, char* argv[])
{
	try {
		Application app( argc, argv );
		app.run();
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}


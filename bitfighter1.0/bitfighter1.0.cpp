
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
		app.newWindow( new SDL::GLWindow( "bitfighter1.0", 800, 600 ) );
		app.addFont( "menu", new Font( "../contrib/zrnic rg.otf", 16 ) ); // Should be moved into the Application
		app.run();
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}



#include <iostream>
#include <fstream>
#include "application.hpp"
#include "window.hpp"
#include "exceptions.hpp"

using namespace bitfighter;

int main(int argc, char* argv[])
{
	try {
		Application app;
		app.newWindow( new SDL::GLWindow( "bitfighter1.0", 800, 600 ) );
		app.addFont( "menu", new Font( "../contrib/zrnic rg.otf", 16 ) );
		app.run();
	} catch (SDLException sdlex) {
		std::cout << sdlex.what() << std::endl;
	} catch (TTFException ttfex ) {
		std::cout << ttfex.what() << std::endl;
	} catch (GLException glex ) {
		std::cout << glex.what() << std::endl;
	} catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}


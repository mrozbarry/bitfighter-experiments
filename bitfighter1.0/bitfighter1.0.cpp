
#include <iostream>
#include <fstream>
#include "application.hpp"

using namespace bitfighter;

int main(int argc, char* argv[])
{
	application *app = new application();
	try {
		std::string username = "";
		std::string password = "";
		client *me = new client(
			new authentication( "http://some.host/place", 80, username, password )
		);
	} catch (std::exception ex) {
	}
	return 0;
}


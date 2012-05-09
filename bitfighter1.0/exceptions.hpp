
#include <iostream>
#include <fstream>
#include <exception>

#ifndef bitfighter_exceptions_hpp
#define bitfighter_exceptions_hpp	1

namespace bitfighter {

	namespace exception {

		class InvalidFileName : public std::exception {
		public:
			InvalidFileName( std::string message );
			~InvalidFileName( );

			const char* what() const throw();

		private:
			std::string m_what;
		}

	}

}

#endif /* bitfighter_exceptions_hpp */

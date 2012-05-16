
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

#ifndef bitfighter_exceptions_hpp
#define bitfighter_exceptions_hpp	1

namespace bitfighter {

	class BitfighterException : public std::exception {
	public:
		BitfighterException( std::string reference, std::string message, const char *filename = NULL, int linenumber = -1 );
		const char *what() const throw();
	private:
		std::string m_what;
	};

	class SDLException : public std::exception {
	public:
		SDLException( std::string reference, const char *filename = NULL, int linenumber = -1 );
		const char *what() const throw();
	private:
		std::string m_what;
	};

	class TTFException : public std::exception {
	public:
		TTFException( std::string reference, const char *filename = NULL, int linenumber = -1 );
		const char *what() const throw();
	private:
		std::string m_what;
	};

	class GLException : public std::exception {
	public:
		GLException( std::string reference, int code, const char *filename = NULL, int linenumber = -1 );
		const char *what() const throw();

		static int glError( void );
	private:
		std::string	m_what;
	};

}

#endif /* bitfighter_exceptions_hpp */

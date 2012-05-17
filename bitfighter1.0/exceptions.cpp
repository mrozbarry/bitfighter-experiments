
#include "exceptions.hpp"

namespace bitfighter {

	BitfighterException::BitfighterException( std::string reference, std::string message, const char *filename, int linenumber )
	{
		std::stringstream exc;
		exc << "Bitfighter Exception (" << reference << "): " << message;
		if( (filename != NULL) || (linenumber >= 0) ) {
			exc << " [ ";
			if( filename ) exc << " File `" << filename << "` ";
			if( linenumber >= 0 ) exc << " LineNumber:" << linenumber << " ";
			exc << "]";
		}
		this->m_what = exc.str();
	}

	const char* BitfighterException::what() const throw()
	{
		return this->m_what.c_str();
	}


	SDLException::SDLException( std::string reference, const char *filename, int linenumber )
	{
		std::stringstream exc;
		exc << "SDL Exception (" << reference << "): " << SDL_GetError();
		if( (filename != NULL) || (linenumber >= 0) ) {
			exc << " [ ";
			if( filename ) exc << " File `" << filename << "` ";
			if( linenumber >= 0 ) exc << " LineNumber:" << linenumber << " ";
			exc << "]";
		}
		this->m_what = exc.str();
	}

	const char* SDLException::what() const throw()
	{
		return this->m_what.c_str();
	}

	TTFException::TTFException( std::string reference, const char *filename, int linenumber )
	{
		std::stringstream exc;
		exc << "TTF Exception (" << reference << "): " << TTF_GetError();
		if( (filename != NULL) || (linenumber >= 0) ) {
			exc << " [ ";
			if( filename ) exc << " File `" << filename << "` ";
			if( linenumber >= 0 ) exc << " LineNumber:" << linenumber << " ";
			exc << "]";
		}
		this->m_what = exc.str();
	}

	const char* TTFException::what() const throw()
	{
		return this->m_what.c_str();
	}

	GLException::GLException( std::string reference, int code, const char *filename, int linenumber )
	{
		std::stringstream exc;
		exc << "OpenGL Exception (" << reference << "): ";
		switch( code ) {
		case GL_NO_ERROR:
			exc << "No errors"; break;
		case GL_INVALID_ENUM:
			exc << "A function had an illegal glEnum value"; break;
		case GL_INVALID_VALUE:
			exc << "A parameter had an invalid glEnum value"; break;
		case GL_INVALID_OPERATION:
			exc << "A command was invalid because of the current OpenGL state"; break;
		case GL_OUT_OF_MEMORY:
			exc << "OpenGL has ran out of available memory"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			exc << "The framebuffer was incomplete while attempting to read or write"; break;
		}
		this->m_what = exc.str();
		std::cout << this->m_what << std::endl;
	}

	const char *GLException::what() const throw()
	{
		return this->m_what.c_str();
	}

	int GLException::glError( void )
	{
		return glGetError();
	}
}

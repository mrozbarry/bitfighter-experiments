//-----------------------------------------------------------------------------------
//
// Bitfighter - A multiplayer vector graphics space game
// Based on Zap demo released for Torque Network Library by GarageGames.com
//
// Derivative work copyright (C) 2008-2009 Chris Eykamp
// Original work copyright (C) 2004 GarageGames.com, Inc.
// Other code copyright as noted
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful (and fun!),
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//------------------------------------------------------------------------------------

#ifndef bitfighter_stringutils_hpp
#define bitfighter_stringutils_hpp	1

#ifdef _MSC_VER
#pragma warning (disable: 4996)     // Disable POSIX deprecation, certain security warnings that seem to be specific to VC++
#endif

#include <SDL_types.h>

#include <chipmunk/chipmunk.h>

#include <tnlVector.h>

#include <string>
#include <map>
#include <exception>

namespace bitfighter {

	// From http://stackoverflow.com/questions/134569/c-exception-throwing-stdstring
	struct SaveException : public std::exception
	{
	   std::string msg;

	   SaveException(std::string str);         // Constructor
	   virtual ~SaveException() throw();  // Destructor, needed to avoid "looser throw specifier" errors with gcc
	   const char* what() const throw();
	};

	// Collection of useful string things

	std::string ExtractDirectory(const std::string& path);

	std::string ExtractFilename(const std::string& path);

	std::string itos(Sint32 i);
	std::string itos(Uint32 i);
	std::string itos(Uint64 i);
	std::string itos(Sint64 i);
	std::string ftos(float f, int digits);
	std::string ftos(float f);

	Sint32 stoi(const std::string &s);
	float stof(const std::string &s);

	std::string replaceString(const std::string &strString, const std::string &strOld, const std::string &strNew);
	std::string stripExtension(std::string filename);

	std::string listToString(const TNL::Vector<std::string> &words, char seperator);

	// TODO: Merge these methods
	TNL::Vector<std::string> parseString(const std::string &line);
	void parseString(const char *inputString, TNL::Vector<std::string> &words, char seperator);
	void parseString(const std::string &inputString, TNL::Vector<std::string> &words, char seperator);
	void parseComplexStringToMap(const std::string &inputString, std::map<std::string, std::string> &fillMap,
								 const std::string &entryDelimiter = ";", const std::string &keyValueDelimiter = ":");

	std::string concatenate(const TNL::Vector<std::string> &words, Sint32 startingWith = 0);

	std::string lcase(std::string strToConvert);
	std::string ucase(std::string strToConvert);

	bool isInteger(const char *str);


	void s_fprintf(FILE *stream, const char *format, ...);      // throws SaveException

	bool caseInsensitiveStringCompare(const std::string &str1, const std::string &str2);

	// File utils
	bool fileExists(const std::string &path);               // Does file exist?
	bool makeSureFolderExists(const std::string &dir);      // Like the man said: Make sure folder exists
	bool getFilesFromFolder(const std::string& dir, TNL::Vector<std::string>& files, const std::string& extension = "");
	bool safeFilename(const char *str);


	// Different variations on joining file and folder names
	std::string joindir(const std::string &path, const std::string &filename);
	std::string strictjoindir(const std::string &part1, const std::string &part2);
	std::string strictjoindir(const std::string &part1, const std::string &part2, const std::string &part3);

	std::string trim_right(const std::string &source, const std::string &t = " ");
	std::string trim_left(const std::string &source, const std::string &t = " ");
	std::string trim(const std::string &source, const std::string &t = " ");

	Sint32 countCharInString(const std::string &source, char search);

	const Uint32 MAX_FILE_NAME_LEN = 128;     // Completely arbitrary
	std::string makeFilenameFromString(const char *levelname);

	std::string ctos(char c);

	std::string writeLevelString(const char *in);

}

#endif

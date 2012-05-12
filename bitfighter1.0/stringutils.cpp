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

#include "stringutils.hpp"
#include <tnlPlatform.h>
#include <tnlVector.h>

#include <cstdio>
#include <stdarg.h>        // For va_args
#include <string>          // For... everything.  This is std::stringUtils, after all!
#include <sstream>         // For parsestd::string
#include <sys/stat.h>      // For testing existence of folders

#ifdef TNL_OS_WIN32
#include <direct.h>        // For mkdir
#endif

#  ifdef TNL_OS_WIN32
#     include "dirent.h"        // Need local copy for Windows builds
#  else
#     include <dirent.h>        // Need standard copy for *NIXes
#  endif


namespace bitfighter {

	// Constructor
	SaveException::SaveException(std::string str) : msg(str)
	{
	   // do nothing
	}


	// Destructor
	SaveException::~SaveException() throw ()
	{
	   // do nothing
	}


	const char *SaveException::what() const throw ()
	{
	   return msg.c_str();
	}


	////////////////////////////////////////
	////////////////////////////////////////


	// Collection of useful std::string things

	std::string ExtractDirectory( const std::string& path )
	{
	  return path.substr( 0, path.find_last_of( '\\' ) + 1 );
	}

	std::string ExtractFilename( const std::string& path )
	{
	  return path.substr( path.find_last_of( '\\' ) + 1 );
	}


	std::string itos(Sint32 i)
	{
	   char outstring[12];  // 11 chars plus a null char, -2147483648
	   TNL::dSprintf(outstring, sizeof(outstring), "%d", i);
	   return outstring;
	}


	std::string itos(Uint32 i)
	{
	   char outstring[11];  // 10 chars plus a null char, 4294967295
	   TNL::dSprintf(outstring, sizeof(outstring), "%u", i);
	   return outstring;
	}


	std::string itos(Uint64 i)
	{
	   char outstring[21];  // 20 chars plus a null char, 18446744073709551615
	   TNL::dSprintf(outstring, sizeof(outstring), "%u", i);
	   return outstring;
	}


	std::string itos(Sint64 i)
	{
	   char outstring[21];  // 20 chars plus a null char, -9223372036854775808
	   TNL::dSprintf(outstring, sizeof(outstring), "%d", i);
	   return outstring;
	}


	std::string stripZeros(std::string str)
	{
	   while(str[str.length() - 1]  == '0')
		  str.erase(str.length() - 1);

	   if(str[str.length() - 1] == '.')
		  str.erase(str.length() - 1);

	   return str;
	}


	std::string ftos(float f, Sint32 digits)
	{
	   char outstring[100];
	   TNL::dSprintf(outstring, sizeof(outstring), (std::string("%2.") + itos(digits) + "f").c_str(), f);

	   return stripZeros(outstring);
	}


	std::string ftos(float f)
	{
	   char outstring[100];
	   TNL::dSprintf(outstring, sizeof(outstring), "%f", f);

	   return stripZeros(outstring);
	}

	// These next two functions are defined in c++0x/c++11 and can be removed if we migrate to
	// the new standard
	Sint32 stoi(const std::string &s)
	{
	   return atoi(s.c_str());
	}


	float stof(const std::string &s)
	{
	   return (float)atof(s.c_str());
	}


	// From http://stackoverflow.com/questions/3418231/c-replace-part-of-a-std::string-with-another-std::string, replaceAll variant
	std::string replacestring(const std::string &strstring, const std::string &from, const std::string &to) 
	{
	   std::string str = strstring;    // Make working copy

		size_t start_pos = 0;
		while((start_pos = str.find(from, start_pos)) != std::string::npos) 
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();      // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}

	   return str;
	}


	// Remove any extension from filename
	std::string stripExtension(std::string filename)
	{
	   return filename.substr(0, filename.find_last_of('.'));
	}


	// From http://stackoverflow.com/questions/11635/case-insensitive-std::string-comparison-in-c
	bool caseInsensitiveStringCompare(const std::string &str1, const std::string &str2) {
		if(str1.size() != str2.size()) {
			return false;
		}
		for(std::string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
			if(tolower(*c1) != tolower(*c2)) {
				return false;
			}
		}
		return true;
	}


	// Convert std::string to lower case
	std::string lcase(std::string strToConvert)      // Note that strToConvert is a copy of whatever was passed
	{
	   for(Uint32 i = 0; i < strToConvert.length(); i++)
		  strToConvert[i] = tolower(strToConvert[i]);
	   return strToConvert;
	}


	// Convert std::string to upper case
	std::string ucase(std::string strToConvert)
	{
	   for(Uint32 i = 0; i < strToConvert.length(); i++)
		  strToConvert[i] = toupper(strToConvert[i]);
	   return strToConvert;
	}


	// Return true if str looks like an int
	bool isInteger(const char *str)
	{
	   Sint32 i = 0;
	   while(str[i])
	   {
		  if(str[i] < '0' || str[i] > '9')
			 return false;
		  i++;
	   }

	   return true;
	}


	// TODO: Merge this with the one following
	// Based on http://www.gamedev.net/community/forums/topic.asp?topic_id=320087
	// Parses a std::string on whitespace, except when inside "s
	//
	// FIXME: This is using std::string streams which are an order of magnitude (or 2) too slow
	// rewrite without using streams if possible
	TNL::Vector<std::string> parseString(const std::string &line)
	{
	   TNL::Vector<std::string> result;

	   std::string          item;
	   std::stringstream    ss(line);

	   while(ss >> item)
	   {
		  if(item[0] == '"')
		  {
			 Sint32 lastItemPosition = (Sint32)item.length() - 1;
			 if(item[lastItemPosition] != '"') 
			 {
				// read the rest of the double-quoted item
				std::string restOfItem;
				getline(ss, restOfItem, '"');
				item += restOfItem;
			 }
			 // otherwise, we had a single word that was quoted. In any case, we now
			 // have the item in quotes; remove them
			 item = trim(item, "\"");
		  }

		  // item is "fully cooked" now
		  result.push_back(item);
	   }

	   return result;
	}


	void parseString(const std::string &inputString, TNL::Vector<std::string> &words, char seperator)
	{
	   parseString(inputString.c_str(), words, seperator);
	}


	// Splits inputstd::string into a series of words using the specified separator; does not consider quotes
	void parseString(const char *inputString, TNL::Vector<std::string> &words, char seperator)
	{
	   char word[128];
	   Sint32 wn = 0;       // Where we are in the word we're creating
	   Sint32 isn = 0;      // Where we are in the inputstd::string we're parsing

	   words.clear();

	   while(inputString[isn] != 0)
	   {
		  if(inputString[isn] == seperator) 
		  {
			 word[wn] = 0;    // Add terminating NULL
			 if(wn > 0) 
				words.push_back(word);
			 wn = 0;
		  }
		  else
		  {
			 if(wn < 126)   // Avoid overflows
			 {
				word[wn] = inputString[isn]; 
				wn++; 
			 }
		  }
		  isn++;
	   }
		word[wn] = 0;

		if(wn > 0) 
		   words.push_back(word);
	}


	void parseComplexStringToMap(const std::string &inputString, std::map<std::string, std::string> &fillMap,
								 const std::string &entryDelimiter, const std::string &keyValueDelimiter)
	{
		size_t lp = 0;
		while( true ) {
			size_t p = inputString.find( entryDelimiter, lp );
			bool isLast = ( p == std::string::npos );
			std::string part = inputString.substr( p, (isLast ? lp : ( lp - p ) ) );
			size_t divider = part.find( keyValueDelimiter );
			if( divider != std::string::npos ) {
				std::string key = inputString.substr(0, divider);
				std::string value = inputString.substr( divider + keyValueDelimiter.length() );
				std::pair<std::string, std::string> keyValuePair( key, value );
				fillMap.insert( keyValuePair );
			}
			lp = p + entryDelimiter.length();
			if( isLast ) break;
		}
	}


	// Concatenate all std::strings in words into one, startingWith default to zero
	// TODO: Merge with listToString below
	std::string concatenate(const TNL::Vector<std::string> &words, Sint32 startingWith)
	{
	   std::string concatenated = "";
	   for(Sint32 i = startingWith; i < words.size(); i++)
		  concatenated += (i == startingWith ? "" : " ") + words[i];

	   return concatenated;
	}


	// TODO: Merge with concatenate above
	std::string listToString(const TNL::Vector<std::string> &words, char seperator)
	{
	   std::string str = "";

	   // Convert separator char to a c_std::string so it can be added below
	   char sep[2];
	   sep[0] = seperator;
	   sep[1] = 0;    // Null terminate
      
	   for(Sint32 i = 0; i < words.size(); i++)
			str += words[i] + ((i < words.size() - 1) ? sep : "");

	   return str;
	}


	// Safe fprintf ==> throws exception if writing fails
	void s_fprintf(FILE *stream, const char *format, ...)
	{
		va_list args;
		va_start(args, format);

		char buffer[2048];
		vsnprintf(buffer, sizeof(buffer), format, args);

		va_end(args);

		if(fprintf(stream, "%s", buffer) < 0)     // Uh-oh...
		{
		   throw(SaveException("Error writing to file"));
		}
	}


	// Returns true if file or folder exists
	// Ok, not strictly a std::string util, but do we really want a fileutils just for this??
	bool fileExists(const std::string &path)
	{
	   struct stat st;
	   return (stat(path.c_str(), &st) == 0);               // Does path exist?
	}


	// Checks if specified folder exists; creates it if not
	bool makeSureFolderExists(const std::string &folder)
	{
	   if(!fileExists(folder)) {
#ifdef TNL_OS_WIN32
		  mkdir(folder.c_str());
#else
		  mkdir(folder.c_str(), 0755);
#endif
		  if(!fileExists(folder)) {
			 TNL::logprintf( TNL::LogConsumer::LogError, "Could not create folder %s", folder.c_str() );
			 return false;
		  }
	   }

	   return true;
	}


	// Read files from folder
	bool getFilesFromFolder(const std::string &dir, TNL::Vector<std::string> &files, const std::string &extension)
	{
	   DIR *dp;
	   struct dirent *dirp;

	   if((dp = opendir(dir.c_str())) == NULL)
		  return false;

	   while ((dirp = readdir(dp)) != NULL) {
		  std::string name = std::string(dirp->d_name);
		  if( ( name.compare( "." ) == 0 ) && ( name.compare( ".." ) ) ) continue;
		  if (extension.length() > 0) {
			 if(name.length() > extension.length() + 1 &&  // +1 -> include the dot '.'
				   name.substr(name.length() - extension.length(), extension.length()) == extension)
				files.push_back(name);
		  } else if (name.length() > 2)  // quick hack to not include . and ..
				files.push_back(name);
	   }

	   closedir(dp);
	   return true;
	}


	// Make sure a file name is 'safe', i.e. not having a path component
	bool safeFilename(const char *str)
	{
	   char chr = str[0];
	   Sint32 i = 0;
	   while(chr != 0)
	   {
		  if(chr == '\\' || chr == '/')
			 return false;
		  i++;
		  chr = str[i];
	   }
	   return true;
	}


	// Join a directory and filename std::strings in a platform-specific way
	std::string joindir(const std::string &path, const std::string &filename)
	{
	   // If there is no path, there's nothing to join -- just return filename
	   if(path == "")
		  return filename;

	   // Does path already have a trailing delimiter?  If so, we'll use that.
	   if(path[path.length() - 1] == '\\' || path[path.length() - 1] == '/')
		  return path + filename;

	   // Otherwise, join with a delimeter.  This works on Win, OS X, and Linux.
	   return path + "/" + filename;
	}
   

	// Join without checking for blank parts
	std::string strictjoindir(const std::string &part1, const std::string &part2)
	{
	   if(part1.length() == 0) return part2;      //avoid crash on zero length std::string.

	   // Does path already have a trailing delimeter?  If so, we'll use that.
	   if(part1[part1.length() - 1] == '\\' || part1[part1.length() - 1] == '/')
		  return part1 + part2;

	   // Otherwise, join with a delimeter.  This works on Win, OS X, and Linux.
	   return part1 + "/" + part2;
	}


	// Three arg version
	std::string strictjoindir(const std::string &part1, const std::string &part2, const std::string &part3)
	{
	   return strictjoindir(part1, strictjoindir(part2, part3));
	}


	std::string trim_right(const std::string &source, const std::string &t)
	{
	   std::string str = source;
	   return str.erase(str.find_last_not_of(t) + 1);
	}


	std::string trim_left(const std::string &source, const std::string &t)
	{
	   std::string str = source;
	   return str.erase(0, source.find_first_not_of(t));
	}

	std::string trim(const std::string &source, const std::string &t)
	{
	   return trim_left(trim_right(source, t), t);
	}

	// count the occurrence of a specific character in a std::string
	Sint32 countCharInString(const std::string &source, char search)
	{
		Sint32 count = 0, c = 0;
		while (source[c] != '\0')
		{
			  if (source[c] == search)
				  count++;
			  c++;
		}
		return count;
	}

	std::string makeFilenameFromString(const char *levelname)
	{
	   static char filename[MAX_FILE_NAME_LEN + 1];    // Leave room for terminating null

	   Uint32 i = 0;

	   while(i < MAX_FILE_NAME_LEN && levelname[i] != 0)
	   {
		  // Prevent invalid characters in file names
		  char c = levelname[i];
		  if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
			 filename[i]=c;
		  else
			 filename[i]='_';
		  i++;
	   }

	   filename[i] = 0;    // Null terminate
	   return filename;
	}


	std::string ctos(char c)
	{
	   // Return empty std::string if char is null
	   if (!c)
		  return "";

	   return std::string(1, c);
	}

	std::string replacestring(const char *in, const char *find, const char *replace)
	{
	   std::string out;
	   int n = 0;
	   int findlen = strlen(find);
	   while(in[n])
	   {
		  if(!strncmp(&in[n], find, findlen))
		  {
			 out += replace;
			 n += findlen;
		  }
		  else
		  {
			 out += in[n];
			 n++;
		  }
	   }
	   return out;
	}

	std::string writeLevelString(const char *in)
	{
	   int c=0;
	   while(in[c] != 0 && in[c] != '\"' && in[c] != '#' && in[c] != ' ')
		  c++;
	   if(in[c] == 0 && c != 0)
		  return std::string(in);  // std::string does not need to be changed if not zero length and there is no space or any of: # "

	   std::string out = replacestring(in, "\"", "\"\"");
	   return std::string("\"") + out + "\"";
	}

};

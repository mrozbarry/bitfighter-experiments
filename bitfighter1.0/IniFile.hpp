// IniFile.cpp:  Implementation of the CIniFile class.
// Written by:   Adam Clauss
// Email: cabadam@tamu.edu
// You may use this class/code as you wish in your programs.  Feel free to distribute it, and
// email suggested changes to me.
//
// Rewritten by: Shane Hill
// Date:         21/08/2001
// Email:        Shane.Hill@dsto.defence.gov.au
// Reason:       Remove dependancy on MFC. Code should compile on any
//               platform. Tested on Windows/Linux/Irix
//////////////////////////////////////////////////////////////////////

#ifndef CIniFile_H
#define CIniFile_H

//#define _UNICODE

// C++ Includes
#include <string>
#include <tnlVector.h>     // For Vector type
#include <cstdlib>

#define MAX_KEYNAME    128
#define MAX_VALUENAME  128
#define MAX_VALUEDATA 2048

using namespace std;
using namespace TNL;

namespace bitfighter {

class CIniFile
{
private:
   bool   caseInsensitive;
   std::string path;

   struct section
   {
      Vector<string> keys;
      Vector<string> values;
      Vector<string> comments;
   };

   Vector<section> sections;         // This is our main Vector that holds all of our INI data
   Vector<string>  sectionNames;     // Holds just the section names
   Vector<string>  headerComments;   // Holds the header comments that aren't part of any section
   std::string CheckCase( std::string s) const;

   std::string section;

public:
   enum errors
   {
      noID = -1
   };

   S32 lineCount;

   CIniFile( const std::string iniPath = "");     // Constructor
   ~CIniFile();                              // Destructor

   void processLine(string line);     // Process a line of an input file (CE)


   // Sets whether or not keynames and valuenames should be case sensitive.
   // The default is case insensitive.
   void CaseSensitive();
   void CaseInsensitive();

   // Sets path of ini file to read and write from.
   void Path(const std::string newPath);
   std::string Path() const;
   void SetPath(const std::string newPath);

   // Reads ini file specified using path.
   // Returns true if successful, false otherwise.
   void ReadFile();

   // Writes data stored in class to ini file.
   bool WriteFile();

   // Deletes all stored ini data.
   void Erase();
   void Clear();
   void Reset();

   // Returns index of specified key, or noID if not found.
   S32 findSection(const std::string &sectionName) const;

   // Returns index of specified value, in the specified key, or noID if not found.
   S32 FindValue(S32 const sectionID, const std::string &keyName) const;

   // Returns number of sections currently in the ini.
   S32 NumSections() const;
   S32 GetNumSections() const;

   // Add a key name.
   S32 addSection( const std::string section);

   // Returns key names by index.
   std::string sectionName( S32 const sectionId) const;
   std::string getSectionName( S32 const sectionId) const;

   // Returns number of values stored for specified section.
   S32 GetNumEntries(S32 const sectionId);
   S32 GetNumEntries(const std::string &keyName);

   // Returns value name by index for a given keyname or sectionId.
   std::string ValueName( S32 const sectionID, S32 const keyID) const;
   std::string GetValueName( S32 const sectionID, S32 const keyID) const;
   std::string ValueName( const std::string section, S32 const keyID) const;
   std::string GetValueName( const std::string section, S32 const keyID) const;

   // Gets value of [keyname] valuename =.
   // Overloaded to return std::string, int, and double.
   // Returns defValue if key/value not found.
   std::string GetValue(S32 const sectionId, S32 const keyID, const std::string &defValue = "") const;
   std::string GetValue(S32 const sectionId, const std::string &keyName, const std::string &defValue = "") const;
   std::string GetValue(const std::string &section, const std::string &keyName, const std::string &defValue = "") const;

   // Load up valueList with all values from the section
   void GetAllValues(const std::string &section, Vector<string> &valueList);
   void GetAllValues(S32 const sectionId, Vector<string> &valueList);

   // Load up keyList with all keys from the section
   void GetAllKeys(S32 const sectionId, Vector<string> &keyList);
   void GetAllKeys(const std::string &section, Vector<string> &keyList);

   S32    GetValueI(const std::string &section, const std::string &key, S32 const defValue = 0) const;
   bool   GetValueB(const std::string &section, const std::string &key, bool const defValue = false) const;
   F64   GetValueF(const std::string &section, const std::string& key, F64 const defValue = 0.0) const;
   bool     GetValueYN(const std::string &section, const std::string &key, bool defValue) const;

   // This is a variable length formatted GetValue routine. All these voids
   // are required because there is no vsscanf() like there is a vsprintf().
   // Only a maximum of 8 variable can be read.
   /*  S32 GetValueV( const std::string keyname, const std::string valuename, char *format,
            void *v1 = 0, void *v2 = 0, void *v3 = 0, void *v4 = 0,
            void *v5 = 0, void *v6 = 0, void *v7 = 0, void *v8 = 0,
            void *v9 = 0, void *v10 = 0, void *v11 = 0, void *v12 = 0,
            void *v13 = 0, void *v14 = 0, void *v15 = 0, void *v16 = 0);
    */
   // Sets value of [keyname] valuename =.
   // Specify the optional paramter as false (0) if you do not want it to create
   // the key if it doesn't exist. Returns true if data entered, false otherwise.
   // Overloaded to accept std::string, int, and double.
   bool SetValue(const std::string &section, const std::string &key, const std::string &value, bool const create = true);
   bool SetAllValues(const std::string &section, const std::string &prefix, const Vector<string> &values);
   bool SetValueI(const std::string &section, const std::string &key, int const value, bool const create = true);
   bool SetValueB(const std::string &section, const std::string &key, bool const value, bool const create = true);
   bool setValueYN(const std::string section, const std::string key, bool const value, bool const create = true);
   bool SetValueF(const std::string &section, const std::string &key, F64 const value, bool const create = true);
   bool SetValueV(const std::string &section, const std::string &key, char *format, ...);
   bool SetValue(S32 const sectionId, S32 const valueID, const std::string value);

   // Deletes specified value.
   // Returns true if value existed and deleted, false otherwise.
   bool deleteKey(const std::string &section, const std::string &key);

   // Deletes specified key and all values contained within.
   // Returns true if key existed and deleted, false otherwise.
   bool deleteSection(const std::string &section);

   // Header comment functions.
   // Header comments are those comments before the first key.
   //
   // Get number of header comments.
   size_t NumHeaderComments();
   // Add a header comment.
   void     headerComment( const std::string comment);
   // Return a header comment.
   std::string   headerComment( S32 const commentID) const;
   // Delete a header comment.
   bool     deleteHeaderComment( S32 commentID);
   // Delete all header comments.
   void     deleteHeaderComments();

   // Key comment functions.
   // Key comments are those comments within a key. Any comments
   // defined within value names will be added to this list. Therefore,
   // these comments will be moved to the top of the key definition when
   // the CIniFile::WriteFile() is called.
   //
   // Number of key comments.
   S32 numSectionComments(S32 const sectionId) const;
   S32 numSectionComments(const std::string keyname) const;
   // Add a key comment.
   bool     sectionComment(S32 sectionId, const std::string &comment);
   bool     sectionComment(const std::string keyname, const std::string comment, bool const create = true);
   // Return a key comment.
   std::string   sectionComment( S32 const sectionId, S32 const commentID) const;
   std::string   sectionComment( const std::string keyname, S32 const commentID) const;
   // Delete a key comment.
   bool     deleteSectionComment( S32 const sectionId, S32 const commentID);
   bool     deleteSectionComment( const std::string keyname, S32 const commentID);
   // Delete all comments for a key.
   bool     deleteSectionComments( S32 const sectionId);
   bool     deleteSectionComments( const std::string keyname);

   bool     deleteAllSectionComments();
};

extern CIniFile gINI;

};
#endif


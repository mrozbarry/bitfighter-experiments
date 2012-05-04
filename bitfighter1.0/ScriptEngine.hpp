
#include <iostream>
#include <string>

#ifndef bitfighter_scriptengine_hpp
#define bitfighter_scriptengine_hpp	1

namespace bitfighter {

	class ScriptVM {
	public:
		ScriptVM();
		~ScriptVM();

		virtual bool load( std::string path );
		virtual bool load_from_string( std::string script );
		virtual void unload( void );
		virtual bool has_script( void );

	protected:

	private:
		std::string scriptSource;
	};

}

#endif

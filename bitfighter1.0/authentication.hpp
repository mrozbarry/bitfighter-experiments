
#include <string>

namespace bitfighter {

	// Forward declare the application
	class application;

	class authentication {
	public:
		authentication( application *app, std::string host, int port );
		authentication( application *app, std::string host, int port, std::string username, std::string password );
		~authentication( );

		bool login( std::string username, std::string password );
		void logout( void );

		bool isLoggedIn( void );
		bool isRegisteredUser( void );

		const char *getUserName( void );

	private:
		bool		m_isLoggedIn;
		bool		m_isRegisteredUser;
		std::string m_UserName;
		application	*m_app;
	};

}

#include <string>

namespace bitfighter {

	class authentication {
	public:
		authentication( std::string host, int port );
		authentication( std::string host, int port, std::string username, std::string password );
		~authentication( );

		bool login( std::string username, std::string password );
		void logout( void );

		bool isLoggedIn( void );
		bool isRegisteredUser( void );

		const char *getUserName( void );

	private:
		bool m_isLoggedIn;
		bool m_isRegisteredUser;
		std::string m_UserName
	};

}
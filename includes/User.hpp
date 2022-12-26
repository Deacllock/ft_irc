#ifndef USER
# define USER

#include <ostream>
#include <string>

class User
{
	private:
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
		bool					_isConnected;
		std::string 			_username;
		std::string				_nickname;
	
	public:
		/*--------------- Constructors ---------------*/
		User( int fd = -1 );
		User( const User &rhs );
		User &operator=( const User &rhs );
		~User();

		/*--------------- Getters ---------------*/
		int				getFd() const;
		unsigned long	getUserId() const;
		bool			getIsConnected() const;
		std::string     getUsername() const;
		std::string     getNickname() const;

		/*--------------- Setters ---------------*/
		//setNickname;
		//setUsername;
};

std::ostream &operator<<(std::ostream &o, User const &rhs);


#endif
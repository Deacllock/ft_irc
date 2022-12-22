#ifndef USER
# define USER

#include <ostream>
#include <string>

class User
{
	private:
		static	unsigned long	_ids;

		int						_fd;
		unsigned long			_userId;
		bool					_isConnected;
		std::string 			_username;
		std::string				_nickname;
	
	public:
		User(int fd = -1);
		~User();

		int				getFd() const;
		unsigned long	getUserId() const;
		bool			getIsConnected() const;
		std::string     getUsername() const;
		std::string     getNickname() const;

		//setNickname;
		//setUsername;
};

std::ostream &operator<<(std::ostream &o, User const &rhs);


#endif
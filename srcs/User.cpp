#include <unistd.h>
#include "User.hpp"

/*--------------- Constructors ---------------*/
unsigned long	User::_ids = 0;

User::User( int fd ): _fd(fd), _userId(User::_ids), _isConnected(false), _username("") , _nickname("") { User::_ids++; }
User::User( const User &rhs ): _fd(rhs._fd), _userId(rhs._userId), _username(rhs._username) { *this = rhs; }
User::~User()
{
    close(this->_fd);
}

User & User::operator=( const User &rhs )
{
    this->_isConnected = rhs._isConnected;
    this->_nickname = rhs._nickname;
    return *this;
}

/*--------------- Getters ---------------*/
int				User::getFd() const             { return this->_fd; }
unsigned long	User::getUserId() const         { return this->_userId; }
bool			User::getIsConnected() const    { return this->_isConnected; }
std::string     User::getUsername() const       { return this->_username; }
std::string     User::getNickname() const       { return this->_nickname; }
time_t      	User::getLastNickChange() const { return this->_lastNickChange; }

/*--------------- Setters ---------------*/
void	User::setIsConnected( bool val )            { this->_isConnected = val; }
void    User::setNickname( std::string nick )       { this->_nickname = nick; }
void    User::setUsername( std::string user )       { this->_username = user; }
void	User::setLastNickChange( time_t new_time ) { this->_lastNickChange = new_time; }

/*---------------- Non-member functions ----------------*/
std::ostream &operator<<(std::ostream &o, User const &rhs)
{
    o << "\tunique identifier : " << rhs.getUserId() << std::endl;
    o << "\tunique username : " << rhs.getUsername() << std::endl;
    o << "\tunique identifier : " << rhs.getNickname() << std::endl;
    o << "\tuser fd : " << rhs.getFd() << std::endl;
    return o;
}

bool	operator==(const User &u1, const User u2)
{
	if (u1.getFd() == u2.getFd() && u1.getUserId() == u2.getUserId() && u1.getUsername() == u2.getUsername() && u1.getNickname() == u2.getNickname())
		return true;
	return false;
}

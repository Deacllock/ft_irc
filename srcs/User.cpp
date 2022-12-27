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

/*--------------- Setters ---------------*/
void	User::setIsConnected() { this->_isConnected = true; }

std::ostream &operator<<(std::ostream &o, User const &rhs)
{
    o << "\tunique identifier : " << rhs.getUserId() << std::endl;
    o << "\tunique username : " << rhs.getUsername() << std::endl;
    o << "\tunique identifier : " << rhs.getNickname() << std::endl;
    o << "\tuser fd : " << rhs.getFd() << std::endl;
    return o;
}
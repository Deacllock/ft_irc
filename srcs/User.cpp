#include <unistd.h>
#include "User.hpp"

unsigned long	User::_ids = 0;

#include <iostream>
User::User( int fd ): _fd(fd), _userId(User::_ids), _isConnected(false), _username("") , _nickname("") { User::_ids++; }

User::~User() {}

int				User::getFd() const             { return this->_fd; }
unsigned long	User::getUserId() const         { return this->_userId; }
bool			User::getIsConnected() const    { return this->_isConnected; }
std::string     User::getUsername() const       { return this->_username; }
std::string     User::getNickname() const       { return this->_nickname; }


std::ostream &operator<<(std::ostream &o, User const &rhs)
{
    o << "\tunique identifier : " << rhs.getUserId() << std::endl;
    o << "\tunique username : " << rhs.getUsername() << std::endl;
    o << "\tunique identifier : " << rhs.getNickname() << std::endl;
    o << "\tuser fd : " << rhs.getFd() << std::endl;
    return o;
}
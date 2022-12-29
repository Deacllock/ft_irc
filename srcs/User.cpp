#include <unistd.h>
#include "User.hpp"

/*--------------- Constructors ---------------*/
unsigned long	User::_ids = 0;

User::User( int fd, bool isCo): _fd(fd), _userId(User::_ids++)
{
    this->_isConnected = isCo;
    this->_isRegistered = false;
    this->_username = "";
    this->_nickname = "";
    this->_lastNickChange = 0;
    this->_mode = 0;
    this->_realName = "";
}

User::User( const User &rhs): _fd(rhs._fd), _userId(rhs._userId) { *this = rhs; }

User::~User() { close(this->_fd); }

User & User::operator=( const User &rhs )
{
    this->_isConnected = rhs._isConnected;
    this->_isRegistered = rhs._isRegistered;
    this->_username = rhs._username;
    this->_nickname = rhs._nickname;
    this->_lastNickChange = rhs._lastNickChange;
    this->_mode = rhs._mode;
    this->_realName = rhs._realName;
    return *this;
}

/*--------------- Getters ---------------*/
int				User::getFd() const             { return this->_fd; }
unsigned long	User::getUserId() const         { return this->_userId; }
bool			User::getIsConnected() const    { return this->_isConnected; }
bool            User::getIsRegistered() const   { return this->_isRegistered; }
std::string     User::getUsername() const       { return this->_username; }
std::string     User::getNickname() const       { return this->_nickname; }
time_t      	User::getLastNickChange() const { return this->_lastNickChange; }
char			User::getMode() const           { return this->_mode; }

/*--------------- Setters ---------------*/
void	User::setIsConnected( bool val )        { this->_isConnected = val; }
void    User::setIsRegistered( bool val )       { this->_isRegistered = val; }
void    User::setUsername( std::string user )   { this->_username = user; }
void	User::setMode( char mode )              { this->_mode = mode; }
void    User::setRealName( std::string name )   { this->_realName = name; }

void    User::setNickname( std::string nick )
{
    this->_nickname = nick;
    if (this->_isRegistered)
        this->_lastNickChange = time(0);
}

/*--------------- Printing ---------------*/
std::ostream &operator<<(std::ostream &o, User const &rhs)
{
    o << "\tunique identifier : " << rhs.getUserId() << std::endl;
    o << "\tunique username : " << rhs.getUsername() << std::endl;
    o << "\tunique identifier : " << rhs.getNickname() << std::endl;
    o << "\tuser fd : " << rhs.getFd() << std::endl;
    return o;
}
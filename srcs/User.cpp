#include <unistd.h>
#include "User.hpp"

/*--------------- Constructors ---------------*/
unsigned long	User::_ids = 0;

User::User( int fd, bool isCo, unsigned long limit ): _fd(fd), _userId(User::_ids++)
{
    this->_isConnected = isCo;
    this->_isRegistered = false;
    this->_username = "";
    this->_nickname = "";
    this->_lastNickChange = 0;
    this->_mode = 0;
    this->_realName = "";
    this->_limit = limit;
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
    this->_limit = rhs._limit;
    return *this;
}

/*--------------- Getters ---------------*/
int				User::getFd() const             { return this->_fd; }
unsigned long	User::getUserId() const         { return this->_userId; }
bool			User::getIsConnected() const    { return this->_isConnected; }
bool			User::getIsRegistered() const   { return this->_isRegistered; }
std::string     User::getUsername() const       { return this->_username; }
std::string     User::getNickname() const       { return this->_nickname; }
time_t      	User::getLastNickChange() const { return this->_lastNickChange; }

/*--------------- Setters ---------------*/
void	User::setIsConnected( bool val )            { this->_isConnected = val; }
void	User::setIsRegistered( bool val )           { this->_isRegistered = val; }

void    User::setNickname( std::string nick )
{
    this->_nickname = nick;
    if (this->_isRegistered)
        this->_lastNickChange = time(0);
}

void    User::setUsername( std::string user )       { this->_username = user; }
void	User::setLastNickChange( time_t new_time )  { this->_lastNickChange = new_time; }
void	User::setMode( char mode )                  { this->_mode = mode; }
void    User::setRealName( std::string name )       { this->_realName = name; }
void	User::setLimit( unsigned long limit )		{ this->_limit = limit; }


void	User::addJoinedChan( Channel c )
{
	std::vector<Channel>::iterator it = this->_joinedChan.begin();
	std::vector<Channel>::iterator it_end = this->_joinedChan.end();

	for (; it < it_end; it++)
		if (c == *it)
			return;
	
	this->_joinedChan.push_back(c);
}
void	User::removeJoinedChan( Channel c )
{
	std::vector<Channel>::iterator it = this->_joinedChan.begin();
	std::vector<Channel>::iterator it_end = this->_joinedChan.end();

	for (; it < it_end; it++)
	{
		if (c == *it)
		{
			this->_joinedChan.erase(it);
			break;
		}
	}
}
void	User::quitAllChan() { this->_joinedChan.clear(); }

/*--------------- Others ---------------*/
bool	User::tooManyChanJoined() const { return this->_limit == this->_joinedChan.size(); }

/*---------------- Non-member functions ----------------*/

std::ostream &operator<<(std::ostream &o, User const &rhs)
{
    o << "\tunique identifier : " << rhs.getUserId() << std::endl;
    o << "\tunique username : " << rhs.getUsername() << std::endl;
    o << "\tunique identifier : " << rhs.getNickname() << std::endl;
    o << "\tuser fd : " << rhs.getFd() << std::endl;
    return o;
}

bool	operator==(const User &u1, const User &u2)
{
	return u1.getFd() == u2.getFd() && u1.getUserId() == u2.getUserId() && u1.getUsername() == u2.getUsername() && u1.getNickname() == u2.getNickname();
}

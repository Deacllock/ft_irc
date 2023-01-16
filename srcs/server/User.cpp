#include <unistd.h>
#include "User.hpp"

/*--------------- Constructors ---------------*/
unsigned long	User::_ids = 0;

User::User(): _fd(-1), _userId(User::_ids++)
{
    this->_status = STARTING;
    this->_username = "";
    this->_nickname = "*";
    this->_lastNickChange = 0;
    this->_operator = false;
    this->_realName = "";
    this->_limit = -1;
    this->_replies = std::queue<std::string>();
    this->_nbPing = 0;
    this->_incompleteCmd = "";
}

User::User( int fd, enum status val, unsigned long limit ): _fd(fd), _userId(User::_ids++)
{
    this->_status = val;
    this->_username = "";
    this->_nickname = "*";
    this->_lastNickChange = 0;
    this->_operator = false;
    this->_realName = "";
    this->_limit = limit;
    this->_replies = std::queue<std::string>();
    this->_nbPing = 0;
    this->_incompleteCmd = "";
}

User::User( const User &rhs): _fd(rhs._fd), _userId(rhs._userId) { *this = rhs; }

User::~User() { close(this->_fd); }

User & User::operator=( const User &rhs )
{
    this->_status = rhs._status;
    this->_username = rhs._username;
    this->_nickname = rhs._nickname;
    this->_lastNickChange = rhs._lastNickChange;
    this->_realName = rhs._realName;
    this->_limit = rhs._limit;
	this->_joinedChan = rhs._joinedChan;
    return *this;
}

/*--------------- Getters ---------------*/
int				User::getFd() const             	{ return this->_fd; }
unsigned long	User::getUserId() const         	{ return this->_userId; }

bool			User::isConnected() const           { return this->_status == CONNECTED; }
bool			User::isRegistered() const  	 	{ return this->_status == REGISTERED; }
bool			User::isDisconnected() const        { return this->_status == DISCONNECTED; }

bool            User::isOperator() const            { return this->_operator; }

std::string     User::getUsername() const       	{ return this->_username; }
std::string     User::getNickname() const       	{ return this->_nickname; }
time_t      	User::getLastNickChange() const 	{ return this->_lastNickChange; }

std::vector<Channel *>	User::getJoinedChan() const { return this->_joinedChan; }

std::queue<std::string>	User::getReplies() const	{ return this->_replies; }

int             User::getNbPing() const             { return this->_nbPing; }

/*--------------- Setters ---------------*/
void	User::setStatus( enum status val )            { this->_status = val; }

void    User::setUsername( std::string user )       { this->_username = user; }
void    User::setNickname( std::string nick )
{
    this->_nickname = nick;
    if (this->_status == REGISTERED)
        this->_lastNickChange = time(0);
}
void    User::setRealName( std::string name )       { this->_realName = name; }

void	User::setOperator( bool val )               { this->_operator = val; }
void	User::setLimit( unsigned long limit )		{ this->_limit = limit; }

void	User::addJoinedChan( Channel *c )
{
	std::vector<Channel *>::iterator it = this->_joinedChan.begin();
	std::vector<Channel *>::iterator it_end = this->_joinedChan.end();

	for (; it < it_end; it++)
		if (c == *it)
			return;
	
	this->_joinedChan.push_back(c);
}
void	User::removeJoinedChan( Channel *c )
{
	std::vector<Channel *>::iterator it = this->_joinedChan.begin();
	std::vector<Channel *>::iterator it_end = this->_joinedChan.end();

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
bool	User::isOnChan( std::string name )
{
	std::vector<Channel *>::iterator it = this->_joinedChan.begin();
	std::vector<Channel *>::iterator it_end = this->_joinedChan.end();

	for (; it < it_end; it++)
		if ((*it)->getName() == name)
			return true;

	return false;
}

void	User::pushReply( std::string reply ) { this->_replies.push(":" + this->server->getName() + " " + reply + "\r\n"); }
void	User::popReply() { this->_replies.pop(); }

void    User::addPing() { this->_nbPing++; }
void    User::subPing() { this->_nbPing--; }

void    User::pushIncompleteCmd( std::string cmd ) { this->_incompleteCmd = cmd; }
std::string User::popIncompleteCmd()
{
    std::string tmp = this->_incompleteCmd;
    this->_incompleteCmd = "";
    return tmp;
}


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
	return u1.getUserId() == u2.getUserId();
}
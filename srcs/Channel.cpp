#include <unistd.h>
#include "Channel.hpp"

/*--------------- Constructors ---------------*/
unsigned long	Channel::_ids = 0;

Channel::Channel( std::string name, std::string topic, unsigned long limit ): _id(Channel::_ids), _name(name), _topic(topic), _limit(limit) { Channel::_ids++; }
Channel::Channel( const Channel &rhs ): _id(rhs._id), _name(rhs._name), _topic(rhs._topic), _limit(rhs._limit), _banned(rhs._banned), _users(rhs._users) { *this = rhs; }
Channel::~Channel() {}

Channel & Channel::operator=( const Channel &rhs )
{
    this->_name = rhs._name;
    this->_topic = rhs._topic;
    this->_limit = rhs._limit;
    this->_banned = rhs._banned;
    this->_users = rhs._users;
    return *this;
}

/*--------------- Getters ---------------*/
unsigned long		Channel::getId() const         { return this->_id; }
std::string     	Channel::getName() const       { return this->_name; }
std::string     	Channel::getTopic() const       { return this->_topic; }
unsigned long		Channel::getLimit() const		{ return this->_limit; }
std::vector<User *>	Channel::getBanned() const		{ return this->_banned; }
std::vector<User *>	Channel::getUsers() const		{ return this->_users; }

/*--------------- Setters ---------------*/
void    Channel::setName( std::string name )       { this->_name = name; }
void    Channel::setTopic( std::string topic )       { this->_topic = topic; }
void	Channel::setLimit( unsigned long limit )	{ this->_limit = limit; }
void	Channel::addBannedUser( User *u ) {
	std::vector<User *>::iterator	it = this->_banned.begin();
	std::vector<User *>::iterator	it_end = this->_banned.end();
	
	for (; it < it_end; it++)
		if (u == *it)
			return;
	
	this->_banned.push_back(u);
}
void	Channel::removeBannedUser( User *u ) {
	std::vector<User *>::iterator	it = this->_banned.begin();
	std::vector<User *>::iterator	it_end = this->_banned.end();
	
	for (; it < it_end; it++)
	{
		if (u == *it)
		{
			this->_banned.erase(it);
			break;
		}
	}
}
void	Channel::addUser( User *u ) {
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	it_end = this->_users.end();
	
	for (; it < it_end; it++)
		if (u == *it)
			return;
	
	this->_users.push_back(u);
}
void	Channel::removeUser( User *u ) {
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	it_end = this->_users.end();
	
	for (; it < it_end; it++)
	{
		if (u == *it)
		{
			this->_users.erase(it);
			break;
		}
	}
}

/*------------- Others --------------*/
bool	Channel::isBannedUser(User u)
{
	std::vector<User *>::iterator it = this->_banned.begin();
	std::vector<User *>::iterator it_end = this->_banned.end();

	for (; it < it_end; it++)
		if (u == *(*it))
			return true;
	return false;
}

bool	Channel::isJoinedUser(User u)
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator it_end = this->_users.end();

	for (; it < it_end; it++)
		if (u == *(*it))
			return true;
	return false;
}

bool	Channel::isBannedUser(User *u)
{
	std::vector<User *>::iterator it = this->_banned.begin();
	std::vector<User *>::iterator it_end = this->_banned.end();

	for (; it < it_end; it++)
		if (u == *it)
			return true;
	return false;
}

bool	Channel::isJoinedUser(User *u)
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator it_end = this->_users.end();

	for (; it < it_end; it++)
		if (u == *it)
			return true;
	return false;
}

bool	Channel::isChannelFull() { return this->_limit == this->_users.size(); }

static bool	isChanstring(char c)
{
	if (c == 0 || c == '\a' || c == '\r' || c == '\n' || c == ' ' || c == ',' || c == ':')
		return false;
	return true;
}

bool	Channel::checkChannelName(std::string name)
{
	int	i = 1;
	if (name.at(0) != '#' && name.at(0) != '+' && name.at(0) != '&' && name.at(0) != '!')
		return false;
	if (name.at(0) == '!')
	{
		if (name.at(i) != '5')
			return false;
		i++;
		if (!isupper(name.at(i)) && !isdigit(name.at(i)))
			return false;
		i++;
	}
	if (!isChanstring(name.at(i)))
		return false;
	i++;
	if (name.at(i) == ':')
		if (!isChanstring(name.at(i + 1)))
			return false;
	return true;
}

/*--------------- Non-member fuctions ---------------*/
std::ostream &operator<<(std::ostream &o, Channel const &rhs)
{
    o << "\tunique identifier : " << rhs.getId() << std::endl;
    o << "\tname : " << rhs.getName() << std::endl;
    o << "\ttopic : " << rhs.getTopic() << std::endl;
    return o;
}

bool	operator==(const Channel &c1, const Channel &c2)
{
	return c1.getId() == c2.getId() && c1.getName() == c2.getName() && c1.getTopic() == c2.getTopic() && c1.getLimit() == c2.getLimit();
}

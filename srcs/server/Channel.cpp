#include <algorithm>
#include <unistd.h>
#include "Channel.hpp"

/*--------------- Constructors ---------------*/
unsigned long	Channel::_ids = 0;

Channel::Channel( std::string name, std::string topic, unsigned long limit ): _id(Channel::_ids++), _topic(topic), _limit(limit), _inviteOnly(false) 
{	
	this->_name = name;
	this->_banned = std::vector<User *>();
    this->_users = std::vector<User *>();
	this->_operators = std::vector<User *>();
}

Channel::Channel( const Channel &rhs ): _id(rhs._id) { *this = rhs; }
Channel::~Channel() {}

Channel & Channel::operator=( const Channel &rhs )
{
    this->_name = rhs._name;
    this->_topic = rhs._topic;
    this->_limit = rhs._limit;
    this->_banned = rhs._banned;
    this->_users = rhs._users;
	this->_operators = rhs._operators;
    return *this;
}

/*--------------- Getters ---------------*/
unsigned long		Channel::getId() const			{ return this->_id; }
std::string     	Channel::getName() const		{ return this->_name; }
std::string     	Channel::getTopic() const       { return this->_topic; }
std::string			Channel::getKey() const			{ return this->_key; }
unsigned long		Channel::getLimit() const		{ return this->_limit; }
std::vector<User *>	Channel::getBanned() const		{ return this->_banned; }
std::vector<User *>	Channel::getUsers() const		{ return this->_users; }
std::vector<User *>	Channel::getOperators() const	{ return this->_operators; }
std::vector<User *>	Channel::getInvited() const		{ return this->_invited; }

/*--------------- Setters ---------------*/
void    Channel::setName( std::string name )       { this->_name = name; }
void    Channel::setTopic( std::string topic )       { this->_topic = topic; }
void	Channel::setKey( std::string key )			{ this->_key = key; }
void	Channel::setLimit( unsigned long limit )	{ this->_limit = limit; }
void	Channel::setInviteOnly( bool inviteOnly )	{ this->_inviteOnly = inviteOnly; }

static void addUserToVector( std::vector<User *> &vect, User *u )
{
	if (std::find(vect.begin(), vect.end(), u) == vect.end())
		vect.push_back(u);
}

static void removeUserFromVector( std::vector<User *> &vect, User *u )
{
	std::vector<User *>::iterator it = std::find(vect.begin(), vect.end(), u);

	if (it != vect.end())
		vect.erase(it);
}

void	Channel::addBannedUser( User *u )		{ addUserToVector(this->_banned, u); }
void	Channel::removeBannedUser( User *u )	{ removeUserFromVector(this->_banned, u); }

void	Channel::addUser( User *u )				{ addUserToVector(this->_users, u); }
void	Channel::removeUser( User *u )
{ 
	removeUserFromVector(this->_users, u);
	if (this->_users.size() == 0)
		User::server->removeChannel(this);

}

void	Channel::addOperator( User *u )			{ addUserToVector(this->_operators, u); }
void	Channel::removeOperator( User *u )		{ removeUserFromVector(this->_operators, u); }

void	Channel::addInvited( User *u )			{ addUserToVector(this->_invited, u); }
void	Channel::removeInvited( User *u )		{ removeUserFromVector(this->_invited, u); }

/*------------- Others --------------*/
bool	Channel::isBannedUser(const User *u) const
{
	return std::find(this->_banned.begin(), this->_banned.end(), u) != this->_banned.end();
}

bool	Channel::isJoinedUser(const User *u) const
{
	return std::find(this->_users.begin(), this->_users.end(), u) != this->_users.end();
}

bool	Channel::isOperatorUser(const User *u) const
{
	return std::find(this->_operators.begin(), this->_operators.end(), u) != this->_operators.end();
}

bool	Channel::isInvitedUser(const User *u) const
{
	return std::find(this->_invited.begin(), this->_invited.end(), u) != this->_invited.end();
}

bool	Channel::isChannelFull() const { return this->_limit <= this->_users.size(); }

bool	Channel::isInviteOnly() const { return this->_inviteOnly; }

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

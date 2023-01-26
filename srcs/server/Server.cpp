#include <algorithm>

#include "Server.hpp"
#include "utils.hpp"
#include "numericReplies.hpp"

unsigned long	Server::_pingID = 0;

/*--------------- Constructors ---------------*/
Server *Command::server;
Server *User::server;

Server::Server(): _name("ft_irc"), _port("6667"), _password("")
{
	this->_isUp = true;
	this->_opeCredential[0] = "admin";
	this->_opeCredential[1] = "admin";
	Command::server = this;
	User::server = this;
	instanciateCommand();
	if (this->server_start())
		throw CannotStartServer();
	this->client_interactions();
}

Server::Server(std::string port, std::string password): _name("ft_irc"), _port(port), _password(password)
{
	this->_isUp = true;
	this->_opeCredential[0] = "admin";
	this->_opeCredential[1] = "admin";
	Command::server = this;
	User::server = this;
	instanciateCommand();
	if (this->server_start())
		throw CannotStartServer();
	this->client_interactions();
}

Server::Server( const Server &rhs ) { *this = rhs; }

Server & Server::operator=( const Server &rhs )
{
	this->_port = rhs._port;
	this->_password = rhs._password;
	this->_sockfd = rhs._sockfd;
	this->_users = rhs._users; //check vector cpy
	return (*this);
}
 
Server::~Server()
{
	while (this->_users.size())
		removeUser(this->_users[0]);
	while (this->_channels.size())
		removeChannel(this->_channels[0]);
	close (this->_sockfd);
}

const char *Server::CannotStartServer::what() const throw()
{
	return "Error: Impossible to start the server";
}

/*--------------- Getters ---------------*/
std::vector<User *>		Server::getUsers() const	{ return this->_users; };
std::vector<Channel *>	Server::getChannels() const	{ return this->_channels; };
std::string				Server::getName() const		{ return this->_name; };
bool					Server::isUp() const		{ return this->_isUp;}

/*--------------- Setters ---------------*/
void	Server::setIsUp( bool val ) { this->_isUp = val; }

/*--------------- Users ---------------*/
User    *Server::searchUserByFd( int fd )
{
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
		if ((*it)->getFd() == fd)
			return *it;
	return NULL;
}

void Server::addUser( int fd )
{
	enum status status = STARTING;
	if (this->_password == "")
		status = CONNECTED;
	this->_users.push_back(new User(fd, status, -1));
}

void     Server::removeUser( User *user )
{
	removeElmFromVector(this->_users, user);

	std::vector<Channel *> joinedChan = user->getJoinedChan();
	for (std::vector<Channel *>::iterator it = joinedChan.begin();
		it != joinedChan.end(); it++)
	{
		(*it)->removeBannedUser(user);
		(*it)->removeOperator(user);
		(*it)->removeUser(user);
	}
	delete user;
}

bool	Server::isExistingUserByName( std::string name )
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator it_end = this->_users.end();

	for (; it < it_end; it++)
		if (name == (*it)->getNickname())
			return true;

	return false;
}

bool	Server::isExistingUserByNickname( std::string name )
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator it_end = this->_users.end();

	for (; it < it_end; it++)
		if (name == (*it)->getNickname())
			return true;

	return false;
}

User	*Server::getUserByName( std::string name )
{
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	it_end = this->_users.end();

	for (; it < it_end; it++)
		if ((*it)->getNickname() == name)
			return *it;

	return NULL;
}

User	*Server::getUserByNickname( std::string name )
{
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	it_end = this->_users.end();

	for (; it < it_end; it++)
		if ((*it)->getNickname() == name)
			return *it;

	return NULL;
}

/*--------------- Channels ---------------*/
void	Server::createChan( std::string name )
{
	this->addChannel(new Channel(name, "", -1));
}

void	Server::addChannel( Channel *chan )
{
	addElmToVector(this->_channels, chan);
}

void	Server::removeChannel( Channel *chan )
{
	removeElmFromVector(this->_channels, chan);

	std::vector<User *> users = chan->getUsers();
	for (std::vector<User *>::iterator it = users.begin();
		it != users.end(); it++)
	{
		(*it)->removeJoinedChan(chan);
	}
	delete chan;
}

bool	Server::isExistingChannelByName( std::string name )
{
	std::vector<Channel *>::iterator	it = this->_channels.begin();
	std::vector<Channel *>::iterator	it_end = this->_channels.end();

	for (; it < it_end; it++)
		if ((*it)->getName() == name)
			return true;

	return false;
}

Channel	*Server::getChannelByName( std::string name )
{
	std::vector<Channel *>::iterator	it = this->_channels.begin();
	std::vector<Channel *>::iterator	it_end = this->_channels.end();

	for (; it < it_end; it++)
		if ((*it)->getName() == name)
			return *it;

	return NULL;
}

/*--------------- Password ---------------*/
bool    Server::checkPassword( std::string pwd )
{
	return (this->_password == "" || pwd == this->_password);
}

bool    Server::checkOpeCredentials( std::string username, std::string pwd )
{
	return (this->_opeCredential[0] == username && this->_opeCredential[0] == pwd);
}

std::ostream & operator<<(std::ostream &o, Server const &rhs)
{
	std::vector<User *> users = rhs.getUsers();
	o << "-----------------------" << std::endl;
	o << "Nb users : " << users.size() << std::endl;
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		o << **it << std::endl;
	o << "-----------------------" << std::endl;
	return (o);
}

/*--------------- Timeout ---------------*/

std::string	Server::getPingValue()
{
	return (static_cast< std::ostringstream & >(( std::ostringstream() << std::dec << this->_pingID ) ).str());
}

void	Server::checkPong()
{
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ((*it)->getNbPing())
		{
			(*it)->pushReply(":" + this->_name + " " + error("Connection timeout"));
			(*it)->setStatus(DISCONNECTED);
		}
	}
}

void Server::sendPing()
{
	this->_pingID++;
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ((*it)->isDisconnected())
			continue;
		(*it)->pushReply("PING " + this->getPingValue());
		(*it)->addPing();
	}
	
}

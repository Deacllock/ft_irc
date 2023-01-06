#include "Server.hpp"

/*--------------- Constructors ---------------*/
Server::Server(): _name("ft_irc"), _port("6667"), _password("")
{
	instanciateCommand(this);
	if (this->server_start())
		throw CannotStartServer();
	this->client_interactions();
}

Server::Server(std::string port, std::string password): _name("ft_irc"), _port(port), _password(password)
{
	instanciateCommand(this);
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
	{
		delete this->_users[0];
		this->_users.erase(this->_users.begin());
	}
	close (this->_sockfd);
}

const char *Server::CannotStartServer::what() const throw()
{
	return "Error: Impossible to start the server";
}

/*--------------- Getters ---------------*/
std::vector<User *> Server::getUsers() const	{ return this->_users; };
std::vector<Channel *> Server::getChannels() const	{ return this->_channels; };
std::string	Server::getName() const				{ return this->_name; };

/*--------------- Users ---------------*/
User    *Server::searchUserByFd( int fd )
{
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
		if ((*it)->getFd() == fd)
			return *it;
	return NULL;

}

void Server::addUser( int fd ) { this->_users.push_back(new User(fd, this->_password == "")); }

int     Server::removeUser( User *user )
{
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ((*it) == user)
		{
			delete *it;
			this->_users.erase(it);
			return 0;
		}
	}
	return (-1);
}

bool	Server::isExistingUserByName( std::string name )
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator it_end = this->_users.end();

	for (; it < it_end; it++)
		if (name == (*it)->getUsername())
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
		if ((*it)->getUsername() == name)
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
void	Server::addChannel( Channel *chan )
{
	std::vector<Channel *>::iterator it = this->_channels.begin();
	std::vector<Channel *>::iterator it_end = this->_channels.end();

	for (; it < it_end; it++)
		if (chan == *it)
			return;
	
	this->_channels.push_back(chan);
}

int		Server::removeChannel( Channel *chan )
{
	for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		if ((*it) == chan)
		{
			delete *it;
			this->_channels.erase(it);
			return 0;
		}
	}
	return (-1);
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
	return (this->_password == "" || pwd.compare(this->_password) == 0);
}

std::ostream & operator<<(std::ostream &o, Server const &rhs)
{
	std::vector<User *> users = rhs.getUsers();
	o << "-----------------------" << std::endl;
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		o << **it << std::endl;
	o << "-----------------------" << std::endl;
	return (o);
}

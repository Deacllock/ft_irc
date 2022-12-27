#include "Server.hpp"

Server::Server(): _port("6667"), _password("")
{
	if (this->server_start())
		throw CannotStartServer();
	this->client_interactions();
}

Server::Server(std::string port, std::string password): _port(port), _password(password)
{
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
	return (*this);s
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

void Server::addUser( int fd )
{
	this->_users.push_back(new User(fd));
}

int Server::removeUserByFd( int fd )
{
	for (std::vector<User *>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if ((*it)->getFd() == fd)
		{
			delete *it;
			this->_users.erase(it);
			return 0;
		}
	}
	return (-1);
}

std::vector<User *> Server::getUsers() const	{ return this->_users; };

std::ostream & operator<<(std::ostream &o, Server const &rhs)
{
	std::vector<User *> users = rhs.getUsers();
	o << "-----------------------" << std::endl;
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		o << **it << std::endl;
	o << "-----------------------" << std::endl;
	return (o);
}

bool    Server::checkPassword( std::string pwd )
{
	return (pwd.compare(this->_password) == 0);
}

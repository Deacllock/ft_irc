#include "Server.hpp"

Server::Server(): _port("6667"), _password("")
{
	if (server_start())
		throw CannotStartServer();
}

Server::Server(std::string port, std::string password): _port(port), _password(password)
{
	if (server_start())
		throw CannotStartServer();
}

Server::~Server() {}

const char *Server::CannotStartServer::what() const throw()
{
	return "Error: Impossible to start the server";
}

void Server::addUser( int fd )
{
	this->_users.push_back(User(fd));
}

int Server::removeUserByFd( int fd )
{
	for (std::vector<User>::iterator it = this->_users.begin(); it != this->_users.end(); it++)
		if ((*it).getFd() == fd)
		{
			this->_users.erase(it);
			close(fd);
			return 0;
		}
	return (-1);
}

std::vector<User> Server::getUsers() const	{ return this->_users; };

std::ostream & operator<<(std::ostream &o, Server const &rhs)
{
	std::vector<User> users = rhs.getUsers();
	o << "-----------------------" << std::endl;
	for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++)
		o << *it << std::endl;
	o << "-----------------------" << std::endl;
	return (o);
}
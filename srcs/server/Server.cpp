#include "Command.hpp"
#include "Server.hpp"

/*--------------- Constructors ---------------*/
Server::Server(): _name("ft_irc"), _port("6667"), _password("")
{
	this->_opeCredential[0] = "admin";
	this->_opeCredential[1] = "admin";
	instanciateCommand(this);
	if (this->server_start())
		throw CannotStartServer();
	this->client_interactions();
}

Server::Server(std::string port, std::string password): _name("ft_irc"), _port(port), _password(password)
{
	this->_opeCredential[0] = "admin";
	this->_opeCredential[1] = "admin";
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
std::string	Server::getName() const				{ return this->_name; };

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
	this->_users.push_back(new User(this->_name, fd, status, -1));
}

int     Server::removeUser( User *user )
{
	//delete user in every channel it belongs to
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

/*--------------- Password ---------------*/
bool    Server::checkPassword( std::string pwd )
{
	return (this->_password == "" || pwd.compare(this->_password) == 0);
}

bool    Server::checkOpeCredentials( std::string username, std::string pwd )
{
	return (this->_opeCredential[0].compare(username) == 0 && this->_opeCredential[0].compare(pwd) == 0);
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
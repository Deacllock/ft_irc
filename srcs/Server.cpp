#include <Server.hpp>

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
	return "Error: Impossible to Start Server";
}
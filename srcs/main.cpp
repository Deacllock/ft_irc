#include <iostream>

#include "Server.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ft_irc port password" << std::endl;
		return (2);
	}
	
	Server	server(argv[1], argv[2]);
	return server.client_interactions();
}
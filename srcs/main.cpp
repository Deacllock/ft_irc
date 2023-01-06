#include <iostream>
#include <csignal>

#include "Server.hpp"

void	ctrl_c(int signum)
{
	(void)signum;
	std::cout << "In ctrl C" << std::endl;
	// delete server; 
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ft_irc port password" << std::endl;
		return (2);
	}
	signal(SIGINT, ctrl_c);
	Server(argv[1], argv[2]);
}

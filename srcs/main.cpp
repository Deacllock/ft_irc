#include <iostream>
#include <csignal>

#include "Server.hpp"

void	ctrl_c(int signum) { (void)signum; }

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ft_irc port password" << std::endl;
		return (2);
	}
	signal(SIGINT, ctrl_c);
	try {
		Server(argv[1], argv[2]);
	} catch (std::exception &e) { std::cout << e.what() << std::endl; }
}

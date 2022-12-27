#include <iostream>

#include "Command.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ft_irc port password" << std::endl;
		return (2);
	}
	Server	srv(argv[1], argv[2]);
}

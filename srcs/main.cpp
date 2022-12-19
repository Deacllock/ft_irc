#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>

#include <stdio.h>

/**
 * @brief Binds a socket file descriptor to a specific port.
 * 
 * This function generates an addrinfo struct for TCP connection using IPV(4 or 6), calls getaddrinfo to generate a list of usable socket address and try to bind any of them with the socket.
 * The program stops at first match.
 * 
 * @param sockfd Socket file descriptor.
 * @param port Port to bind to.
 * @return int On success, returns 0, otherwise, -1.
 */
int	ft_bind(int sockfd, const char *port)
{
	struct addrinfo *results, *tmp, hints;

	hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = getprotobyname("TCP")->p_proto; //IPPROTO_TCP?
	hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;	
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

    if (getaddrinfo(NULL, port, &hints, &results))
	{
		std::cerr << "Error while using getaddrinfo" << std::endl;
		return -1;
	}
	for (tmp = results; tmp; tmp = tmp->ai_next)
	{
		if (!bind(sockfd, tmp->ai_addr, tmp->ai_addrlen))
		{
			freeaddrinfo(results);
			return (0);
		}
	}
	freeaddrinfo(results);
	std::cerr << "Error while binding" << std::endl;
	return -1;
}

/**
 * @brief Generate a socket.
 * 
 * This function generate a non bloquant, TCP/IP(v4/v6) socket.
 * Then specify some options to make this socket address and port reusable between two calls.
 * 
 * @return int Socket file descriptor value.
 */
int ft_socket()
{
	int sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0); //IPPROTO_TCP?
	if (sockfd == -1)
	{
		std::cerr << "Error while using socket" << std::endl;
		return (-1);
	}
	
	int opt = 1; //what opt shall I choose?
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cerr << "Error while using setsockopt" << std::endl;
		return (-1);
	}
	return (sockfd);
}

/**
 * @brief Initiate a listening server.
 *
 * This function initiate a listening server using the socket, bind, listen functions.
 *  
 * @param port The port to listen to.
 * @return int The socket to use to handle connexions to server.
 */
int	init_server(const char *port)
{
	int sockfd = ft_socket();
	if (sockfd == -1 || ft_bind(sockfd, port) == -1)
		return -1;
	if (listen(sockfd, 32) == -1) //how shall we choose backlog?
	{
		std::cerr << "Error while using listen" << std::endl;
		return -1;
	}
	return sockfd;
}

int main(void)
{
	int sockfd = init_server("6667");
	if (sockfd == -1)
		return (1);
	return 0;
}
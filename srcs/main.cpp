#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <iostream>

#include <stdio.h>

#define TIMEOUT 180000 //3 * 60 *1000 = 3mins

//allocation statique ou dynamique (pollfd)

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

int client_interactions(int sockfd)
{
	struct pollfd	fds[200];
	int	nfds = 1;
	int ret = 0;

	fds[0].fd = sockfd;
	fds[0].events = POLLIN;
	//POLLIN -> there is data to read (amazing)
	//POLLOUT -> writing is now possible!
	//POLLERR -> error condition
	//POLLHUB -> peer closed its end of the channel but may have some data to read
	//POLLNVAL -> fd not open

	while(1)
	{
		if (poll(fds, nfds, TIMEOUT) <= 0) //fail or timeout
			return (-1);
		//never getting here
		std::cout << "never" << std::endl;
		//why adding server on fds?
		while (1)
		{
			int new_fd = accept(sockfd, NULL, NULL);
			if (new_fd == -1)
				break;
			fds[nfds].fd = new_fd;
			fds[nfds].events = POLLIN; //shall I use other events?
		}

		//check new connection on server -> what about max size?
		//for each matching fd, receive data -> moment to handle commands?
		//if connection closed make a smart reduction of table (end of loop) + update db?
		
	}
	return ret;
}

int main(void)
{
	int sockfd = init_server("6667");
	if (sockfd == -1)
		return (1);
	return client_interactions(sockfd);
}
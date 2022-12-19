#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <iostream>

#include <stdio.h>

#include <vector>

#define TIMEOUT  10000 //10 * 1000 = 10sec

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
	int sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (sockfd == -1)
	{
		std::cerr << "Error while using socket" << std::endl;
		return (-1);
	}
	
	int opt = 1;
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
	hints.ai_protocol = getprotobyname("TCP")->p_proto;
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

void accept_new_connections(std::vector<pollfd> fds, int *nfds, int sockfd)
{
	while (1)
	{
		int new_fd = accept(sockfd, NULL, NULL);
		if (new_fd == -1)
			break;
		std::cout << "Amazing" << std::endl;
		pollfd tmp;
		tmp.fd = new_fd;
		tmp.events = POLLIN | POLLOUT ;
		fds.push_back(tmp);
	}
}


int client_interactions(int sockfd)
{
	std::vector<pollfd>	fds;
	int	nfds = 1;
	int ret = 0;
	struct pollfd	tmp;
	tmp.fd = sockfd;
	tmp.events = POLLIN;
	fds.push_back(tmp);
	fds[0].events = POLLIN;
	//POLLIN -> there is data to read (amazing)
	//POLLOUT -> writing is now possible!
	//POLLERR -> error condition
	//POLLHUB -> peer closed its end of the channel but may have some data to read
	//POLLNVAL -> fd not open
	bool end_server = false;
	while(!end_server)
	{
		if (poll(fds.data(), nfds, TIMEOUT) <= 0) //fail or timeout ->timeout is not an error, just continue?
			return -1;

		for (int i = 0; i < nfds; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)//or else?
				return -1;
			if (fds[i].fd == sockfd)
			{
				accept_new_connections(fds, &nfds, sockfd);
				continue;
			}
			//read_parse_and_reply(); //can use boolean to check if I shall update fd
		}
		//compress_array();
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
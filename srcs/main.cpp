#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <iostream>

#include <sstream>
#include <stdio.h>


#include <vector>

#define TIMEOUT 180000 // 3 * 60 * 1000 = 3min
#define BUFFER_SIZE 42

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

void	add_poll_connection(std::vector<struct pollfd> *fds, int fd, int events)
{
	struct pollfd tmp;
	tmp.fd = fd;
	tmp.events = events;
	tmp.revents = 0;
	fds->push_back(tmp);
}

/**
 * @brief Accepts every connexion incoming on socket.
 * 
 * Generate a new file descriptor for any incoming connexion and keep it in memory.
 * 
 * @param fds Vector of struct pollfd as defined in man poll. 
 * @param sockfd Server socket file descriptor.
 */
void accept_new_connections(std::vector<struct pollfd> *fds, const int sockfd)
{
	while (1)
	{
		int new_fd = accept(sockfd, NULL, NULL); //accept fill other params with user info
												 //proper time to fill a new user class
		if (new_fd == -1)
			break;
		add_poll_connection(fds, new_fd, POLLIN);
	}
}

int	read_parse_and_reply(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	std::string 	msg = "";

	int ret = recv(fd, buf, BUFFER_SIZE, MSG_DONTWAIT);
	while (ret > 0)
	{
		buf[ret] = '\0';
		msg += buf;
		ret = recv(fd, buf, BUFFER_SIZE, MSG_DONTWAIT);
	}
	std::cout << msg; //HERE IS PARSING TIME
	return (0);
}

int client_interactions(int sockfd)
{	
	std::vector<pollfd>	fds;

	add_poll_connection(&fds, sockfd, POLLIN);
	bool end_server = false;

	while(!end_server)
	{
		int ret = poll(fds.data(), fds.size(), TIMEOUT);
		if ( ret < 0 )
		{
			end_server = true;
			continue;
		}

		if (ret == 0)
			continue;
		
		size_t size = fds.size();
		for (size_t i = 0; i < size; i++, size = fds.size())
		{
			if (fds[i].revents == 0)
				continue;
			//on error close link with user or insult it?
			if (!(fds[i].revents & POLLIN) && !(fds[i].revents & POLLOUT) && !(fds[i].revents & POLLHUP))
			{
				fds.erase(fds.begin() + i);
				//update user db
				i--;
				continue;
			}
			if (fds[i].fd == sockfd)
			{
				accept_new_connections(&fds, sockfd);
				continue;
			}
			read_parse_and_reply(fds[i].fd); //can use boolean to check if I shall update fd
		}		
	}
	//free and return?
	return 0;
}

int main(void)
{
	int sockfd = init_server("6667");
	if (sockfd == -1)
		return (1);
	return client_interactions(sockfd);
}
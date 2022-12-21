
#include <iostream> //TO REMOVE
#include <netdb.h>
#include <poll.h>

#include "Server.hpp"

/**
 * @brief Generate a socket.
 * 
 * This function generate a non bloquant, TCP/IP(v4/v6) socket.
 * Then specify some options to make this socket address and port reusable between two calls.
 * 
 * @return int Socket file descriptor value.
 */
static int ft_socket()
{
	int sockfd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (sockfd == -1)
		return (-1);
	
	int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		return (-1);

	return (sockfd);
}

/**
 * @brief Binds a socket to a specific port.
 * 
 * This function generates an addrinfo struct for TCP connection using IPV(4 or 6),
 * calls getaddrinfo to generate a list of usable socket addresses and try to bind
 * any of them with the socket.
 * 
 * The program stops at first match.
 * 
 * @param sockfd Socket file descriptor.
 * @param port Port to bind to.
 * @return int On success, returns 0, otherwise, -1.
 */
static int	ft_bind(int sockfd, std::string port)
{
	struct addrinfo *results, *tmp, hints;

	hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = getprotobyname("TCP")->p_proto;
	hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;	
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

    if (getaddrinfo(NULL, port.c_str(), &hints, &results))
		return -1;

	for (tmp = results; tmp; tmp = tmp->ai_next)
	{
		if (!bind(sockfd, tmp->ai_addr, tmp->ai_addrlen))
		{
			freeaddrinfo(results);
			return (0);
		}
	}

	freeaddrinfo(results);
	return -1;
}

/**
 * @brief Add new file descriptor with specific events to pollfd vector.
 * 
 * @param fds Pollfd vector to modify.
 * @param fd Fd to add.
 * @param events Event mask to look for in poll function.
 */
static void	add_poll_connection(std::vector<struct pollfd> *fds, int fd, int events)
{
	struct pollfd tmp;
	tmp.fd = fd;
	tmp.events = events;
	tmp.revents = 0;
	fds->push_back(tmp);
}

/**
 * @brief Accepts every connection incoming on socket.
 * 
 * Generate a new file descriptor for any incoming connection and add it in pollfd vector.
 * 
 * @param fds pollfd vector as defined in man poll. 
 * @param sockfd Server socket.
 */
static void accept_new_connections(std::vector<struct pollfd> *fds, const int sockfd)
{
	while (true)
	{
		int new_fd = accept(sockfd, NULL, NULL); //accept fill other params with user info
												 //proper time to fill a new user class
		if (new_fd == -1)
			break;
		add_poll_connection(fds, new_fd, POLLIN);
	}
}

/**
 * @brief Read user input, parse it and reply.
 * 
 * Receive user message, call parsing and send a reply depending on user input.
 * 
 * @param fd User fd.
 * @return int 
 */
static int	read_parse_and_reply(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	std::string 	msg = "";

	int ret = recv(fd, buf, BUFFER_SIZE, MSG_DONTWAIT);
	while (ret > 0)
	{
		buf[ret] = '\0';
		msg += buf;
		ret = recv(fd, buf, BUFFER_SIZE, MSG_DONTWAIT);
	}
	std::cout << msg; //HERE IS PARSING TIME
	return (0); // What shall I return ? (depends on user leaving server)
}

/**
 * @brief Start the server and make it listen.
 *
 * This function create a socket for the server, binds it to a port speicified by a user.
 * When the server is ready, use the listen function to wait for user connections.
 *  
 * @return int -1 if something wrong happened, 0 otherwise.
 */
int	Server::server_start()
{
	int sockfd = ft_socket();
	if (sockfd == -1 || ft_bind(sockfd, this->_port) == -1)
		return -1;
	if (listen(sockfd, 128) == -1)
	{
		std::cerr << "Error while using listen" << std::endl;
		return -1;
	}
	this->_sockfd = sockfd;
	return 0;
}

/**
 * @brief While server is up, handle user connections.
 * 
 * This function:
 *  - Accepts new incoming requests.
 *  - Read user messages and reply.
 *  - Handle errors.
 * 
 * @return int -1 if something went wrong, 0 otherwise.
 */
int Server::client_interactions()
{	
	std::vector<pollfd>	fds;
	add_poll_connection(&fds, this->_sockfd, POLLIN);

	while (true)
	{
		int ret = poll(fds.data(), fds.size(), TIMEOUT);
		if ( ret < 0 )
			return -1;

		if (ret == 0)
			continue;
		
		for (size_t size = fds.size(), i = 0; i < size; i++, size = fds.size())
		{
			std::cout << "fd: " << fds[i].fd << std::endl;
			std::cout << "revent: " << fds[i].revents << std::endl;
			if (fds[i].revents == 0)
				continue;

			if (!(fds[i].revents & POLLIN) && !(fds[i].revents & POLLOUT) && !(fds[i].revents & POLLHUP))
			{
				fds.erase(fds.begin() + (i--));	//update user db
			}
			else if (fds[i].fd == this->_sockfd)
				accept_new_connections(&fds, this->_sockfd);

			else
				read_parse_and_reply(fds[i].fd); //can use boolean to check if I shall update fd
		}		
	}
	return 0;
}

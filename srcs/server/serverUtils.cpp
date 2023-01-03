#include <netdb.h>
#include <poll.h>

#include <iostream>

#include "Command.hpp"
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
static void	add_poll_connection(std::vector<struct pollfd> &fds, int fd, int events)
{
	struct pollfd tmp;
	tmp.fd = fd;
	tmp.events = events;
	tmp.revents = 0;
	fds.push_back(tmp);
}

/**
 * @brief Accepts every connection incoming on socket.
 * 
 * Generate a new file descriptor for any incoming connection and add it in pollfd vector.
 * 
 * @param fds pollfd vector as defined in man poll. 
 * @param sockfd Server socket.
 */
static void accept_new_connections(Server &server, std::vector<struct pollfd> &fds, const int sockfd)
{
	while ( true )
	{
		int new_fd = accept(sockfd, NULL, NULL);
		if (new_fd == -1)
			break;
		#ifdef DEBUG
			std::cout << "New user landed in " + server.getName() << std::endl; //debug
		#endif
		server.addUser(new_fd);
		add_poll_connection(fds, new_fd, POLLIN | POLLRDHUP);
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
static int	read_parse_and_reply(Server *server, int fd)
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
	
	if (msg.substr(0, msg.length() - 2) == "") //shall be handled later in parsing
		return ret;
	#ifdef DEBUG
		std::cout << fd << " < " << msg; //debug
	#endif
	
	std::vector<std::string> srv_reps = handle_input(server->searchUserByFd(fd), msg).getOutputs();
	while (srv_reps.size())
	{
		send(fd, srv_reps[0].c_str(), srv_reps[0].length(), MSG_DONTWAIT);
		#ifdef DEBUG
			std::cout << fd << " > " << srv_reps[0]; //debug
		#endif
		srv_reps.erase(srv_reps.begin());
	}
	return (ret);
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
		return -1;
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
	add_poll_connection(fds, this->_sockfd, POLLIN);

	while (true)
	{
		int ret = poll(fds.data(), fds.size(), TIMEOUT);
		if ( ret < 0 )
			return -1;

		if (ret == 0)
			continue;
		
		for (size_t size = fds.size(), i = 0; i < size; i++, size = fds.size())
		{
			if (fds[i].revents == 0)
				continue;

			if (fds[i].revents != POLLIN)
			{
				#ifdef DEBUG
					std::cout << "User has left " + this->_name << std::endl;
				#endif
				this->removeUser(this->searchUserByFd(fds[i].fd));
				fds.erase(fds.begin() + (i--));
			}

			else if (fds[i].fd == this->_sockfd)
				accept_new_connections(*this, fds, this->_sockfd);

			else if (read_parse_and_reply(this, fds[i].fd) == 0)
			{
				#ifdef DEBUG
					std::cout << "User has left " + this->_name << std::endl;
				#endif
				this->removeUser(this->searchUserByFd(fds[i].fd));
				fds.erase(fds.begin() + (i--));
			}
		}
	}
	return 0;
}

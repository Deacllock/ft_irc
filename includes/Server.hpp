#ifndef SERVER
#define SERVER

#include <exception>
#include <string>
#include <vector>

//#include "User.hpp"

class Server
{
    private:
        std::string             _port;
        std::string             _password; // shall be encoded
        int                     _sockfd;

        // std::vector<User>       _users;
        // std::vector<User>       _connected_users;
        // std::vector<Channel>    _channels;

    public:
        Server();
        Server(std::string port, std::string password);
        ~Server();

        int	server_start();
        int client_interactions();

        class CannotStartServer : public std::exception
        {
            public:
				virtual const char *what() const throw();
        };
};


#endif
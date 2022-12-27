#ifndef SERVER
# define SERVER

# define TIMEOUT 180000 // 3 * 60 * 1000 = 3min
# define BUFFER_SIZE 42

# include <exception>
# include <ostream>
# include <string>
# include <unistd.h>
# include <vector>

#include "Command.hpp"
#include "User.hpp"

class Command;

class Server
{
    private:
        std::string             _port;
        std::string             _password; // shall be encoded
        int                     _sockfd;

        std::vector<User *>       _users;
        // std::vector<Channel>    _channels;

    public:
   		/*--------------- Constructors ---------------*/
        Server();
        Server( std::string port, std::string password );
        Server( const Server &rhs );
        Server &operator=( const Server &rhs );
        ~Server();

        int	server_start();
        int client_interactions();

        class CannotStartServer : public std::exception
        {
            public:
				virtual const char *what() const throw();
        };

        std::vector<User*> getUsers() const;

        void    addUser( int fd );
        User    *searchUserByFd( int fd );
        int     removeUser( User *user );
        bool    checkPassword( std::string pwd );
};

std::ostream &operator<<(std::ostream &o, Server const &rhs);

#endif
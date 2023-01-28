#ifndef SERVER
# define SERVER

# define TIMEOUT 60000 // 60 * 1000 = 1 minute
# define BUFFER_SIZE 42
# define NICK_DELAY 60 // 1 minute

# include <ostream>
# include <unistd.h>
# include <string>
# include <vector>

# include "Channel.hpp"
# include "Command.hpp"
# include "User.hpp"

class Channel;
class Command;
class User;

class Server
{
    private:
        static unsigned long    _pingID;
        bool                    _isUp;

        std::string             _name;
        std::string             _port;
        std::string             _password;
        int                     _sockfd;
        std::string             _opeCredential[2];

        std::vector<User *>       _users;
        std::vector<Channel *>    _channels;

    public:
   		/*--------------- Constructors ---------------*/
        Server();
        Server( std::string port, std::string password );
        Server( const Server &rhs );
        Server &operator=( const Server &rhs );
        ~Server();

        class CannotStartServer : public std::exception
        {
            public:
				virtual const char *what() const throw();
        };

        /*--------------- Server instantiation ---------------*/
        int	server_start();
        int client_interactions();

        /*--------------- Getters ---------------*/
        std::vector<User*>      getUsers() const;
        std::string             getName() const;
		std::vector<Channel *>	getChannels() const;
        bool                    isUp() const;
 
        /*--------------- Setters ---------------*/
        void    setIsUp(bool val);

        /*--------------- Users ---------------*/
        User    *searchUserByFd( int fd );
        void    addUser( int fd );
        void    removeUser( User *user );
		bool	isExistingUserByName( std::string name );
		bool	isExistingUserByNickname( std::string name );
		User	*getUserByName( std::string name );
		User	*getUserByNickname( std::string name );

		/*--------------- Channels --------------*/
		void	createChan( std::string name );
        void    addChannel( Channel *chan );
        void    removeChannel( Channel *chan );
		bool	isExistingChannelByName( std::string name );
		Channel	*getChannelByName( std::string name );

        /*--------------- Password ---------------*/
        bool    checkPassword( std::string pwd );
        bool    checkOpeCredentials( std::string username, std::string pwd );

        /*--------------- Timeout ---------------*/
        std::string getPingValue();
        void    checkPong();
        void    sendPing();
};

std::ostream &operator<<(std::ostream &o, Server const &rhs);

#endif

#ifndef USER
# define USER

# include <queue>

# include "Server.hpp"
# include "utils.hpp"

class Channel;
class Server;

enum status
{
	DISCONNECTED,
	STARTING,
	CONNECTED,
	REGISTERED
};

class User
{
	public:
		static Server			*server;

	private:
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
	
		bool					_operator;
		enum status				_status;
		std::string 			_username;
		std::string				_nickname;
		time_t					_lastNickChange;
		std::string				_realName;
		unsigned long			_limit;

		std::queue<std::string>	_replies;
		std::vector<Channel * >	_joinedChan;

		int						_nbPing;
		std::string				_incompleteCmd;

	public:
		/*--------------- Constructors ---------------*/
		User();
		User( int fd, enum status val, unsigned long limit );
		User( const User &rhs);
		~User();
		User &operator=( const User &rhs );

		/*--------------- Getters ---------------*/
		int						getFd() const;
		unsigned long			getUserId() const;

		// STATUS //
		bool					isConnected() const;
		bool            		isRegistered() const;
		bool					isDisconnected() const;

		// INFOS //
		std::string   		 	getUsername() const;
		std::string     		getNickname() const;
		time_t					getLastNickChange() const;
		std::string     		getRealName() const;
		std::string				getFullName() const;

		bool					isOperator() const;
		unsigned long			getLimit() const;

		std::vector<Channel *>	getJoinedChan() const;
		std::queue<std::string>	getReplies() const;
		int						getNbPing() const;

		/*--------------- Setters ---------------*/
		void	setStatus( enum status val );

		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void    setRealName( std::string name );

		void	setOperator( bool val );
		void	setLimit( unsigned long limit );

		void		addJoinedChan( Channel *c );
		void		removeJoinedChan( Channel *c );
		void		quitAllChan();
		bool		tooManyChanJoined() const;
		bool    	isOnChan( std::string name );
		std::string listAllChans();

		void	pushReply( std::string reply );
		void	popReply();

		void	addPing();
		void	subPing();

		void		pushIncompleteCmd( std::string cmd );
		std::string popIncompleteCmd();

		void	sendAllChannels( std::string msg );
};

/*---------------- operators ----------------*/

std::ostream &operator<<(std::ostream &o, User const &rhs);
bool	operator==(const User &u1, const User &u2);


#endif

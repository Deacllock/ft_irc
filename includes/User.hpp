#ifndef USER
# define USER

# include <ctime>
# include <ostream>
# include <queue>
# include <string>

# include "Channel.hpp"

class Channel;

enum mode_flags
{
	AWAY, //1
	INVISIBLE, //2
	WALLOPS, //4
	RESTRICTED, //8
	OPERATOR = 16, //16
	LOCAL_OPERATOR, //32
	NOTICE //64
};

enum status
{
	DISCONNECTED,
	STARTING,
	CONNECTED,
	REGISTERED
};

class User
{
	private:
		std::string				_hostname;
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
	
		enum status				_status;
		std::string 			_username;
		std::string				_nickname;
		time_t					_lastNickChange;
		char					_mode;
		std::string				_realName;
		unsigned long			_limit;

		std::queue<std::string>	_replies;
		std::vector<Channel * >	_joinedChan;

	public:
		/*--------------- Constructors ---------------*/
		User();
		User( std::string hostname, int fd, enum status val, unsigned long limit );
		User( const User &rhs);
		~User();
		User &operator=( const User &rhs );

		/*--------------- Getters ---------------*/
		int						getFd() const;
		unsigned long			getUserId() const;

		// STATUS //
		bool					getIsConnected() const;
		bool            		getIsRegistered() const;
		bool					getIsDisconnected() const;

		std::string   		 	getUsername() const;
		std::string     		getNickname() const;
		time_t					getLastNickChange() const;
		std::string     		getRealName() const;

		// MODE //
		bool					getIsOperator() const;
		char					getMode() const;
		unsigned long			getLimit() const;

		// CHANNEL //
		std::vector<Channel *>	getJoinedChan() const;
		std::queue<std::string>	getReplies() const;

		/*--------------- Setters ---------------*/
		void	setStatus( enum status val );

		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void    setRealName( std::string name );

		// MODE //
		void	setOperator();
		void	setMode( char mode );
		void	setLimit( unsigned long limit );

		void	addJoinedChan( Channel *c );
		void	removeJoinedChan( Channel *c );
		void	quitAllChan();
		bool	tooManyChanJoined() const;
		bool    isOnChan( std::string name );

		void	pushReply( std::string reply );
		void	popReply();

};

/*---------------- operators ----------------*/

std::ostream &operator<<(std::ostream &o, User const &rhs);
bool	operator==(const User &u1, const User &u2);


#endif

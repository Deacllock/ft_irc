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
	away, //1
	invisible, //2
	wallops, //4
	restricted, //8
	op, //16
	local_op, //32
	notice_serv //64
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
		std::vector<Channel>	_joinedChan;

	public:
		/*--------------- Constructors ---------------*/
		User( int fd = -1, enum status val = STARTING, unsigned long limit = -1 );
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

		char					getMode() const;
		unsigned long			getLimit() const;

		// CHANNEL //
		std::vector<Channel>	getJoinedChan();
		std::queue<std::string>	getReplies() const;

		/*--------------- Setters ---------------*/
		void	setStatus( enum status val );

		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void    setRealName( std::string name );

		void	setMode( char mode );
		void	setLimit( unsigned long limit );

		void	addJoinedChan( Channel c );
		void	removeJoinedChan( Channel c );

		void	pushReply( std::string reply );
		void	popReply();

};

/*---------------- operators ----------------*/

std::ostream &operator<<(std::ostream &o, User const &rhs);
bool	operator==(const User &u1, const User &u2);


#endif

#ifndef USER
# define USER

# include <ctime>
# include <ostream>
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
	CONNECTED,
	REGISTERED,
	DISCONNECTED
};

class User
{
	private:
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
	
		enum status				_status
		std::string 			_username;
		std::string				_nickname;
		time_t					_lastNickChange;
		char					_mode;
		std::string				_realName;
		unsigned long			_limit;
		std::vector<Channel>	_joinedChan;

	public:
		/*--------------- Constructors ---------------*/
		User( int fd = -1, bool isCo = false, unsigned long limit = -1 );
		User( const User &rhs);
		~User();
		User &operator=( const User &rhs );

		/*--------------- Getters ---------------*/
		int						getFd() const;
		unsigned long			getUserId() const;
		bool					getIsConnected() const;
		std::string   		 	getUsername() const;
		std::string     		getNickname() const;
		time_t					getLastNickChange() const;
		char					getMode() const;
		bool            		getIsRegistered() const;
		std::string     		getRealName() const;
		unsigned long			getLimit() const;
		std::vector<Channel>	getJoinedChan() const;

		/*--------------- Setters ---------------*/
		void	setIsConnected( bool val );
		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void	setLastNickChange( time_t new_time );
		void	setMode( char mode );
		void    setIsRegistered(bool val);
		void    setRealName( std::string name );
		void	setLimit( unsigned long limit );
		void	addJoinedChan( Channel c );
		void	removeJoinedChan( Channel c );
};

/*---------------- Non-member functions ----------------*/
std::ostream &operator<<(std::ostream &o, User const &rhs);

bool	operator==(const User &u1, const User &u2);


#endif

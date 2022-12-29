#ifndef USER
# define USER

#include <ctime>
#include <ostream>
#include <string>

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

class User
{
	private:
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
	
		bool					_isConnected;
		bool					_isRegistered;
		std::string 			_username;
		std::string				_nickname;
		time_t					_lastNickChange;
		char					_mode;
		std::string				_realName;

		//channel list
		User &operator=( const User &rhs );
	
	public:
		/*--------------- Constructors ---------------*/
		User( int fd = -1, bool isCo = false );
		User( const User &rhs);
		~User();

		/*--------------- Getters ---------------*/
		int				getFd() const;
		unsigned long	getUserId() const;
		bool			getIsConnected() const;
		std::string     getUsername() const;
		std::string     getNickname() const;
		time_t			getLastNickChange() const;
		char			getMode() const;
		bool            getIsRegistered() const;
		std::string     getRealName() const;


		/*--------------- Setters ---------------*/
		void	setIsConnected( bool val );
		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void	setLastNickChange( time_t new_time );
		void	setMode( char mode );
		void    setIsRegistered(bool val);
		void    setRealName( std::string name );
};

/*--------------- Printing ---------------*/
std::ostream &operator<<(std::ostream &o, User const &rhs);


#endif
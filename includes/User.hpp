#ifndef USER
# define USER

# include <ctime>
# include <ostream>
# include <string>

# include "Channel.hpp"
class Channel;

class User
{
	private:
		static	unsigned long	_ids;

		const int				_fd;
		const unsigned long		_userId;
		bool					_isConnected;
		std::string 			_username;
		std::string				_nickname;
		time_t					_lastNickChange;
		unsigned long			_limit;
		std::vector<Channel>	_joinedChan;
	
	public:
		/*--------------- Constructors ---------------*/
		User( int fd = -1, unsigned long limit = -1 );
		User( const User &rhs );
		User &operator=( const User &rhs );
		~User();

		/*--------------- Getters ---------------*/
		int						getFd() const;
		unsigned long			getUserId() const;
		bool					getIsConnected() const;
		std::string     		getUsername() const;
		std::string     		getNickname() const;
		time_t					getLastNickChange() const;
		unsigned long			getLimit() const;
		std::vector<Channel>	getJoinedChan() const;

		/*--------------- Setters ---------------*/
		void	setIsConnected( bool val );
		void    setUsername( std::string user );
		void    setNickname( std::string nick );
		void	setLastNickChange( time_t new_time );
		void	setLimit( unsigned long limit );
		void	addJoinedChan( Channel c );
		void	removeJoinedChan( Channel c );
};

std::ostream &operator<<(std::ostream &o, User const &rhs);
bool	operator==(const User &u1, const User &u2);


#endif

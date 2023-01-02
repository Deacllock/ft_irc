#ifndef CHANNEL
# define CHANNEL

# include <ctime>
# include <ostream>
# include <string>
# include <vector>

# include "User.hpp"
class User;

class Channel
{
	private:
		static	unsigned long	_ids;

		const unsigned long		_id;
		std::string 			_name;
		std::string				_topic;
		unsigned long			_limit;
		std::vector<User>		_banned;

		bool	checkChannelName( std::string name );
	
	public:
		/*--------------- Constructors ---------------*/
		Channel( std::string name = "", std::string topic = "" , unsigned long limit = -1);
		Channel( const Channel &rhs );
		Channel &operator=( const Channel &rhs );
		~Channel();

		/*--------------- Getters ---------------*/
		unsigned long		getId() const;
		std::string			getName() const;
		std::string			getTopic() const;
		unsigned long		getLimit() const;
		std::vector<User>	getBanned() const;

		/*--------------- Setters ---------------*/
		void    setName( std::string user );
		void	setTopic( std::string topic );
		void	setLimit( unsigned long limit);
		void	addBannedUser( User u );
		void	removeBannedUser( User u );

		/*-------------- Others ----------------*/
		bool	isUserBanned( User u );
};

std::ostream	&operator<<( std::ostream &o, Channel const &rhs );
bool			operator==( const Channel &c1, const Channel &c2 );

#endif

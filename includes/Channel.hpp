#ifndef CHANNEL
# define CHANNEL

# include "Server.hpp"

class User;

class Channel
{
	private:
		static	unsigned long	_ids;

		const unsigned long		_id;
		std::string 			_name;
		std::string				_topic;
		std::string				_key;
		unsigned long			_limit;
		bool					_inviteOnly;

		std::vector<User *>		_users;
		std::vector<User *>		_banned;
		std::vector<User *>		_operators;
		std::vector<User *>		_invited;
	
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
		std::string			getKey() const;
		unsigned long		getLimit() const;

		std::vector<User *>	getBanned() const;
		std::vector<User *>	getUsers() const;
		std::vector<User *>	getOperators() const;
		std::vector<User *>	getInvited() const;

		/*--------------- Setters ---------------*/
		void    setName( std::string user );
		void	setTopic( std::string topic );
		void	setKey( std::string key );
		void	setLimit( unsigned long limit);

		void	addBannedUser( User *u );
		void	removeBannedUser( User *u );

		void	addUser( User *u );
		void	removeUser( User *u );

		void	addOperator( User *u );
		void	removeOperator( User *u );

		void	addInvited( User *u );
		void	removeInvited( User *u );

		/*-------------- Others ----------------*/
		bool	isBannedUser( const User *u ) const;
		bool	isJoinedUser( const User *u ) const;
		bool	isOperatorUser( const User *u ) const;
		bool	isChannelFull() const;
		bool	isInviteOnly() const;
};

std::ostream	&operator<<( std::ostream &o, Channel const &rhs );
bool			operator==( const Channel &c1, const Channel &c2 );

#endif

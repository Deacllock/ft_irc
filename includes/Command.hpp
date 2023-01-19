#ifndef COMMANDS
# define COMMANDS

# define INCOMPLETE -1


# include <map>
# include <sstream>

# include "Server.hpp"

class Server;
class User;

class Command
{
	public:
		typedef void (*handler_type)(Command);
		static Server 								*server;
		static std::map<std::string, handler_type>	cmd_map;

	private:		
		std::string 				_cmd;
		std::vector<std::string>	_params;

		User *						_user;
		handler_type				_handler;

		void	split_str(std::string str);

	public:
		/*---------------- Constructors ----------------*/
		Command();
		Command( User *user, std::string zzsusr_input );
		Command( const Command &rhs );
		Command &operator=( const Command &rhs );
		~Command();

		/*---------------- Getters ----------------*/
		std::string 				getCmd() const;
		std::vector<std::string>	getParams() const;
		User *						getUser() const;
		handler_type				getHandler() const;
};

/*---------------- Non-member functions ----------------*/
void 			instanciateCommand();
void			handle_input( User *user, std::string user_input );

int isMessageValid( std::string msg, size_t &i );

#endif

#ifndef COMMANDS
# define COMMANDS

# include <map>
# include <sstream>

# include "Server.hpp"

class Server;
class User;

class Command
{
	public:
		typedef void (*handler_type)(Command &);
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
		Command( User *user, std::string &usr_input );
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
std::string		getColonMsg( std::vector<std::string> params, size_t pos );

#endif

#ifndef COMMANDS
# define COMMANDS

# include <map>
# include <sstream>

# include "Server.hpp"
# include "User.hpp"

class Server;

class Command
{
	public:
		typedef void (*handler_type)(Command &);
		static Server *								_server;
		static std::map<std::string, handler_type>	_cmd_map;

	private:		
		std::string 				_cmd;
		std::vector<std::string>	_params;

		User *						_user;
		handler_type				_handler;
		std::string					_output;

		void	split_str(std::string str);

	public:
		/* CONSTRUCTORS */
		Command();
		Command( User *user, std::string &usr_input );
		Command( const Command &rhs );
		Command &operator=( const Command &rhs );
		~Command();

		/* GETTER */
		std::string 				getCmd() const;
		std::vector<std::string>	getParams() const;
		User *						getUser() const;
		handler_type				getHandler() const;
		std::string					getOutput() const;

		/* SETTER */
		void	setOutput( std::string output );

};

void 	instanciateCommand( Server *server );
Command	handle_input( User *user, std::string user_input );

#endif

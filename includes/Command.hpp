#ifndef COMMANDS
# define COMMANDS

# include <map>
# include <sstream>
# include <vector>

# include "Server.hpp"
# include "User.hpp"

class Server;

class Command
{
	public:
		typedef void (*handler_type)(Command &);
		static Server *								server;
		static std::map<std::string, handler_type>	cmd_map;

	private:		
		std::string 				_cmd;
		std::vector<std::string>	_params;

		User *						_user;
		handler_type				_handler;
		std::vector<std::string>	_outputs;

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
		std::vector<std::string>	getOutputs() const;

		/* SETTER */
		void	addOutput( std::string output );

};

void 	instanciateCommand( Server *server );
Command	handle_input( User *user, std::string user_input );

#endif

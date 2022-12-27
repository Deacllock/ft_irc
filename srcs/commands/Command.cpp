#include "Command.hpp"
#include "commandHandlers.hpp"

/* STATIC INSTANCIATION */
Server *Command::_server;
std::map<std::string, typename Command::handler_type> Command::_cmd_map;

void instanciateCommand(Server	*server)
{
	Command::_server = server;

	std::map<std::string, typename Command::handler_type>	cmd_map;
	cmd_map["PASS"] = pass;
	/* ... */

	Command::_cmd_map = cmd_map;

}

/* CONSTRUCTORS */
Command::Command(): _cmd(0), _params(0), _user(0), _handler(0), _output(0) {}
Command::Command( User *user, std::string &str ): _user(user), _output(0)
{ 
	split_str(str);
	this->_handler = this->_cmd_map[this->_cmd]; //what if not here?
}

Command::Command( const Command &rhs ) { *this = rhs; }

Command & Command::operator=(const Command &rhs)
{
	if (this == &rhs) {return *this;}
	this->_cmd = rhs._cmd;
	this->_params = rhs._params;
	this->_user = rhs._user;
	this->_handler = rhs._handler;
	this->_output = rhs._output;
	return *this;
}

Command::~Command() {}

/* GETTER */
std::string Command::getCmd() const 						{ return this->_cmd; }
std::vector<std::string> Command::getParams() const			{ return this->_params; }
User * Command::getUser() const 							{ return this->_user; }
typename Command::handler_type Command::getHandler() const	{ return this->_handler; }
std::string	Command::getOutput() const 						{ return this->_output; };

/* SETTER */
void	Command::setOutput( std::string output )	{ this->_output = output; }

/**
 * @brief Split string in command and parameters.
 *
 * @param str The full command taken
 * @return VOID
 */
void	Command::split_str(std::string str)
{
	std::istringstream ss(str);
	std::string elem;

	bool first = true;
	while (getline(ss, elem, ' '))
	{
		if (first && elem != "")
		{
			this->_cmd = elem;
			first = false;
		}
		else if (elem != "")
			this->_params.push_back(elem);
	}
}
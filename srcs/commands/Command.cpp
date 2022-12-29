#include "commandHandlers.hpp"

/* STATIC INSTANCIATION */
Server *Command::server;
std::map<std::string, Command::handler_type> Command::cmd_map;

void instanciateCommand(Server	*server)
{
	Command::server = server;
	Command::cmd_map["PASS"] = pass;
	Command::cmd_map["NICK"] = nick;
}

/* CONSTRUCTORS */
Command::Command() {}
Command::Command( User *user, std::string &str ): _user(user), _output("")
{ 
	split_str(str);
	this->_handler = this->cmd_map[this->_cmd]; //what if not here?
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
std::string Command::getCmd() const 				{ return this->_cmd; }
std::vector<std::string> Command::getParams() const	{ return this->_params; }
User * Command::getUser() const 					{ return this->_user; }
Command::handler_type Command::getHandler() const	{ return this->_handler; }
std::string	Command::getOutput() const 				{ return this->_output; };

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
	std::istringstream ss(str.substr(0, str.length() - 2));
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

Command	handle_input(User *user, std::string user_input)
{
	Command c(user, user_input);
	//make check;
	if (c.getHandler())
		c.getHandler()(c);
	return (c);
}
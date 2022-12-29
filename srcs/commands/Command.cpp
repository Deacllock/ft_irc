#include "commandHandlers.hpp"

/* STATIC INSTANCIATION */
Server *Command::server;
std::map<std::string, Command::handler_type> Command::cmd_map;

void instanciateCommand(Server	*server)
{
	Command::server = server;
	Command::cmd_map["PASS"] = pass;
	Command::cmd_map["NICK"] = nick;
	Command::cmd_map["USER"] = user;
	Command::cmd_map["CAP"] = cap;
	Command::cmd_map["JOIN"] = join;
}

/* CONSTRUCTORS */
Command::Command() {}
Command::Command( User *user, std::string &str ): _user(user)
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
	this->_outputs = rhs._outputs;
	return *this;
}

Command::~Command() {}

/* GETTER */
std::string Command::getCmd() const 						{ return this->_cmd; }
std::vector<std::string> Command::getParams() const			{ return this->_params; }
User * Command::getUser() const 							{ return this->_user; }
Command::handler_type Command::getHandler() const			{ return this->_handler; }
std::vector<std::string>	Command::getOutputs() const 	{ return this->_outputs; };

/* SETTER */
void	Command::addOutput( std::string output )
{
	std::vector<std::string>::iterator it = this->_outputs.begin();
	std::vector<std::string>::iterator it_end = this->_outputs.end();

	for (; it < it_end; it++)
		if (output == *it)
			return;

	this->_outputs.push_back(":" + this->server->getName() + " " + output + "\n");
}

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
	else
		c.addOutput(error(c.getCmd() + " :Cannot find command"));
	return (c);
}

#include "commandHandlers.hpp"

/*---------------- Static Instanciation ----------------*/

std::map<std::string, Command::handler_type> Command::cmd_map;

void instanciateCommand()
{
	Command::cmd_map["PASS"] = pass;
	Command::cmd_map["NICK"] = nick;
	Command::cmd_map["USER"] = user;
	Command::cmd_map["CAP"] = cap;
	Command::cmd_map["QUIT"] = quit;
	Command::cmd_map["PING"] = ping;
	Command::cmd_map["PONG"] = pong;

	Command::cmd_map["JOIN"] = join;
	Command::cmd_map["PART"] = part;
	Command::cmd_map["INVITE"] = invite;
	Command::cmd_map["TOPIC"] = topic;
	Command::cmd_map["LIST"] = list;
	Command::cmd_map["NAMES"] = names;
	Command::cmd_map["MODE"] = mode;

	Command::cmd_map["DIE"] = die;
	Command::cmd_map["KICK"] = kick;
	Command::cmd_map["KILL"] = kill;
	Command::cmd_map["OPER"] = oper;
}

/*---------------- Constructors ----------------*/
Command::Command() {}
Command::Command( User *user, std::string &str ): _user(user)
{ 
	split_str(str);
	this->_handler = this->cmd_map[this->_cmd];
}

Command::Command( const Command &rhs ) { *this = rhs; }

Command & Command::operator=(const Command &rhs)
{
	if (this == &rhs) {return *this;}
	this->_cmd = rhs._cmd;
	this->_params = rhs._params;
	this->_user = rhs._user;
	this->_handler = rhs._handler;
	return *this;
}

Command::~Command() {}

/*---------------- Getters ----------------*/
std::string Command::getCmd() const 				{ return this->_cmd; }
std::vector<std::string> Command::getParams() const	{ return this->_params; }
User * Command::getUser() const						{ return this->_user; }
Command::handler_type Command::getHandler() const	{ return this->_handler; }

/*---------------- Non-member functions ----------------*/

/**
 * @brief Split string in command and parameters.
 *
 * @param str The full command taken
 * @return VOID
 */
void	Command::split_str(std::string str)
{
	if (str[str.length() - 1] == '\n' && str[str.length() - 2] == '\r')
		str = str.substr(0, str.length() - 2); //shall be prevented by using proper parsing

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

void	handle_input(User *user, std::string user_input)
{
	Command c(user, user_input);
	if (c.getHandler())
	{
		std::string cmd = c.getCmd();
		if (cmd.compare("PASS") && cmd.compare("NICK")
			&& cmd.compare("CAP") && cmd.compare("USER")
			&& cmd.compare("QUIT") && !user->isRegistered())
				user->pushReply(err_notregistered(user->getNickname()));
		else
			c.getHandler()(c);
	}
	else
		user->pushReply(error(user->getNickname(), c.getCmd() + " :Cannot find command"));
}

std::string		getColonMsg( std::vector<std::string> params, size_t pos )
{
	if (pos >= params.size())
		return "";

	std::string ret = params[pos];
	if (pos < params.size() && params[pos][0] == ':')
	{
		ret = params[pos].substr(1, params[pos].length());
		for (size_t i = pos + 1; i < params.size(); i++)
			ret = ret + " " + params[i];
	}
	return ret;	
}
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

	Command::cmd_map["PRIVMSG"] = privmsg;
	Command::cmd_map["NOTICE"] = notice;
}

/*---------------- Constructors ----------------*/
Command::Command() {}
Command::Command( User *user, std::string str ): _user(user)
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

#include <iostream>
/**
 * @brief Split string in command and parameters.
 *
 * @param str The full command taken
 * @return VOID
 */
void	Command::split_str(std::string str)
{
	size_t i = 0;

	for ( ; str[i] && str[i] != ' '; i++)
		this->_cmd += toupper(str[i]);

	std::string param = "";
	while (++i < str.length())
	{
		if (str[i] == ':' )
		{
			for (i++; str[i] && !(str[i] == ' ' && str[i + 1] && str[i + 1] == ':'); i++)
				param += str[i];
			this->_params.push_back(param);
		}

		else
		{
			for (; str[i] && str[i] != ' '; i++)
				param += str[i];
			this->_params.push_back(param);
		}
		param = "";
	}
}

void	handle_input(User *user, std::string user_input)
{
	std::string remainData = user->popIncompleteCmd() + user_input;
	std::string curMsg;

	while (remainData != "")
	{
		size_t i = 0;
		int validity = isMessageValid(remainData, i);
	
		if (validity == INCOMPLETE)
			return user->pushIncompleteCmd(remainData);

		else if (validity == false)
		{
			size_t nextI = remainData.find("\r\n");

			if (nextI != 0)
				user->pushReply(":" + Command::server->getName() + " " + error("Cannot parse command"));
			if (nextI == std::string::npos || nextI + 2 == remainData.length())
				return;
			remainData = remainData.substr(nextI + 2, remainData.length());
			continue;
		}

		curMsg = remainData.substr(0, i - 2);
		remainData = remainData.substr(i, remainData.length());

		Command c(user, curMsg);
		if (c.getHandler())
		{
			std::string cmd = c.getCmd();
			if (cmd != "PASS" && cmd != "NICK" && cmd != "CAP" && cmd != "USER"
				&& cmd != "QUIT" && cmd != "PONG" && cmd != "PING" && !user->isRegistered())
					user->pushReply(":" + c.server->getName() + " " + err_notregistered(user->getNickname()));
			else
				c.getHandler()(c);
		}
		else
			user->pushReply(":" + Command::server->getName() + " " + error(c.getCmd() + " :Unknown command"));

	}
}

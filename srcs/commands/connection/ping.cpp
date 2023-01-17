#include "commandHandlers.hpp"

void	ping(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noorigin(usr->getNickname()));
	if (params[0][0] == ':')
		return usr->pushReply("PONG :" + params[0]);//getColonMsg(params, 0));
	
	else if (params.size() >= 2)
	{
		User *to = cmd.server->getUserByName(params[1]);
		if (!to)
			usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchserver(usr->getNickname(), params[1]));
		else
			to->pushReply(":" + usr->getNickname() + " PONG " + params[0]); //hum not that sur about pong shall do some test
	}
	usr->pushReply("PONG " + params[0]); //hum not that sur about pong shall do some test
}
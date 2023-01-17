#include "commandHandlers.hpp"

void	pong(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noorigin(usr->getNickname()));

	if (getColonMsg(params, 0) == cmd.server->getPingValue())
		usr->subPing();
	
	if (params.size() >= 2)
	{
		User *to = cmd.server->getUserByName(params[1]);
		if (!to)
			usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchserver(usr->getNickname(), params[1]));
		else
			to->pushReply(":" + usr->getNickname() + " PONG " +  params[0]); //hum not that sur about pong shall do some test
	}

}
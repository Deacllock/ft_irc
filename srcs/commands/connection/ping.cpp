#include "commandHandlers.hpp"

void	ping(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noorigin(usr->getNickname()));
	// if (params[0][0] == ':')
	// 	return usr->pushReply("PONG :" + params[0]);
	
	else if (params.size() >= 2)
	{
		User *to = cmd.server->getUserByName(params[1]);
		if (!to)
			usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchserver(usr->getNickname(), params[1]));
		else
			to->pushReply(":" + usr->getFullName() + " PONG " + params[0]);
	}
	usr->pushReply("PONG " + params[0]);
}
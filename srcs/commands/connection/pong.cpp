#include "commandHandlers.hpp"

void	pong(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		usr->pushReply(err_noorigin(usr->getNickname()));
	else if (params.size() >= 2)
	{
		User *to = cmd.server->getUserByName(params[1]);
		if (!to)
			usr->pushReply(err_nosuchserver(usr->getNickname(), params[1]));
		else
			to->pushReply("PONG " + params[0]); //hum not that sur about pong shall do some test
	}

	//check pong is a reply to server ping
}
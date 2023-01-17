#include "commandHandlers.hpp"

void	privmsg(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_norecipient(usr->getNickname(), "PRIVMSG"));
	if (cmd.getParams().size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_notexttosend(usr->getNickname()));
	
	std::string target = cmd.getParams()[0];
	std::string msg = ":" + usr->getNickname() + " PRIVMSG " + target + " " + getColonMsg(cmd.getParams(), 1);

	if (Command::server->isExistingChannelByName(target))
	{
		Channel	*chan = Command::server->getChannelByName(target);
		if (!usr->isOnChan(target))
			return usr->pushReply(":" + cmd.server->getName() + " " + err_cannotsendtochan(usr->getNickname(), target));
		sendAll(chan->getUsers(), usr, msg);
	}
	else
	{
		if (!Command::server->isExistingUserByName(target))
			return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchnick(usr->getNickname(), target));
		
		User *userTarget = Command::server->getUserByNickname(target);
		userTarget->pushReply(msg);
	}
}

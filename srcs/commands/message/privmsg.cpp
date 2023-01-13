#include "commandHandlers.hpp"

#include <iostream>

void	privmsg(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return cmd.addOutput(err_norecipient("PRIVMSG"));
	if (cmd.getParams().size() < 2)
		return cmd.addOutput(err_notexttosend());
	
	std::string target = cmd.getParams()[0];
	std::string text = cmd.getParams()[1];

	if (Command::server->isExistingChannelByName(target))
	{
		Channel	*chan = Command::server->getChannelByName(target);
		if (!user->isOnChan(target))
			return cmd.addOutput(err_cannotsendtochan(target));

		std::vector<User *> users = chan->getUsers();

		std::vector<User *>::iterator it = users.begin();
		std::vector<User *>::iterator it_end = users.end();
		for (; it < it_end; it++)
			(*it)->pushReply(text);
	}
	else
	{
		if (!Command::server->isExistingUserByName(target))
			return cmd.addOutput(err_nosuchnick(target));
		
		User *userTarget = Command::server->getUserByNickname(target);
		userTarget->pushReply(text);
	}
}

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
		if (!user->isOnChan(target)) // CHECK MODE
			return cmd.addOutput(err_cannotsendtochan(target));
		// SEND MESSAGE TO CHAN
		// SEND ALL USER pushreply for all users
		(void) chan;
	}
	else
	{
		if (!Command::server->isExistingUserByName(target))
			return cmd.addOutput(err_nosuchnick(target));
		User *userTarget = Command::server->getUserByNickname(target);
		// SEND MESSAGE TO USER
		// SEND QUEUE REPLY pushreply
		(void) userTarget;
	}
}

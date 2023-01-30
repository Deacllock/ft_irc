#include "commandHandlers.hpp"

static void	sendMessage(Command cmd, bool sendReply)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
	{
		if (sendReply)
			usr->pushReply(":" + Command::server->getName() + " " + err_norecipient(usr->getNickname(), "PRIVMSG"));
		return;
	}

	if (cmd.getParams().size() < 2)
	{ 
		if (sendReply)
			usr->pushReply(":" + Command::server->getName() + " " + err_notexttosend(usr->getNickname()));
		return;
	}
		
	std::string target = cmd.getParams()[0];
	std::string msg;
	if (sendReply)
		msg = ":" + usr->getFullName() + " PRIVMSG " + target + " " + cmd.getParams()[1];
	else
		msg = ":" + usr->getFullName() + " NOTICE " + target + " " + cmd.getParams()[1];

	if (Command::server->isExistingChannelByName(target))
	{
		Channel	*chan = Command::server->getChannelByName(target);
		if (!chan->isJoinedUser(usr))
		{
			if (sendReply)
				usr->pushReply(":" + Command::server->getName() + " " + err_cannotsendtochan(usr->getNickname(), target));
			return;
		}
		sendAll(chan->getUsers(), usr, msg);		
	}
	else
	{
		if (!Command::server->isExistingUserByName(target))
		{
			if (sendReply)
				usr->pushReply(":" + Command::server->getName() + " " + err_nosuchnick(usr->getNickname(), target));
			return;
		}
		
		User *userTarget = Command::server->getUserByNickname(target);
		userTarget->pushReply(msg);
	}
}

/**
 * @brief PRIVMSG is used to send private messages between users, as well as to send messages to channels.
 * 
 * Parameters: <msgtarget> <text to be sent>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	privmsg(Command cmd)
{
	sendMessage(cmd, true);
}


void	notice(Command cmd)
{
	sendMessage(cmd, false);
}
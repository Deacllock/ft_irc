#include "commandHandlers.hpp"

/**
 * @brief PRIVMSG is used to send private messages between users, as well as to send messages to channels.
 * 
 * Parameters: <msgtarget> <text to be sent>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	privmsg(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + Command::server->getName() + " " + err_norecipient(usr->getNickname(), "PRIVMSG"));

	if (cmd.getParams().size() < 2)
		return usr->pushReply(":" + Command::server->getName() + " " + err_notexttosend(usr->getNickname()));
		
	std::string target = cmd.getParams()[0];
	std::string msg = ":" + usr->getFullName() + " PRIVMSG " + target + " " + cmd.getParams()[1];//getColonMsg(cmd.getParams(), 1);

	if (Command::server->isExistingChannelByName(target))
	{
		Channel	*chan = Command::server->getChannelByName(target);
		if (!chan->isJoinedUser(usr)) //works with banned user too
			return usr->pushReply(":" + Command::server->getName() + " " + err_cannotsendtochan(usr->getNickname(), target));
		sendAll(chan->getUsers(), usr, msg);		
	}
	else
	{
		if (!Command::server->isExistingUserByName(target))
			return usr->pushReply(":" + Command::server->getName() + " " + err_nosuchnick(usr->getNickname(), target));
		
		User *userTarget = Command::server->getUserByNickname(target);
		userTarget->pushReply(msg);
	}
}
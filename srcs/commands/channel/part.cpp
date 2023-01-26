#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief  The PART command causes the user sending the message to be removed from channel(s).
 * 
 * Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	part(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "PART"));
	
	std::string reason = "";
	if (cmd.getParams().size() > 1)
		reason += " " + cmd.getParams()[1];

	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	for (; it < it_end; it++)
	{
		Channel	*chan = Command::server->getChannelByName(*it);

		if (!chan)
		{
			usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchchannel(usr->getNickname(), *it));
			continue;
		}

		if (!chan->isJoinedUser(usr))
			usr->pushReply(":" + cmd.server->getName() + " " + err_notonchannel(usr->getNickname(), chan->getName()));

		else
		{
			sendAll(chan->getUsers(), NULL, ":" + usr->getFullName() + " PART " + chan->getName() + reason);
			chan->removeOperator(usr);
			chan->removeUser(usr);
			usr->removeJoinedChan(chan);
		}
	}
}

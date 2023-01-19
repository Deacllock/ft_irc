#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief List All chan existing on server.
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
static void	listAllChan(Command cmd)
{
	std::vector<Channel *> channels = Command::server->getChannels();

	std::vector<Channel *>::iterator it = channels.begin();
	std::vector<Channel *>::iterator it_end = channels.end();
	User *usr = cmd.getUser();
	
	for (; it < it_end; it++)
		usr->pushReply(":" + cmd.server->getName() + " " + rpl_list(usr->getNickname(), (*it)->getName(), intToString((*it)->getUsers().size()), (*it)->getTopic()));
}

/**
 * @brief The list command is used to list channels and their topics.
 * 
 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	list(Command cmd)
{
	User *usr = cmd.getUser();

	if (cmd.getParams().size() > 0)
	{
		std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);

		std::vector<std::string>::iterator it = channels.begin();
		std::vector<std::string>::iterator it_end = channels.end();
		for (; it < it_end; it++)
		{
			if (!Command::server->isExistingChannelByName(*it))
				continue;

			Channel	*chan = Command::server->getChannelByName(*it);
			usr->pushReply(":" + cmd.server->getName() + " " + rpl_list(usr->getNickname(), chan->getName(), intToString(chan->getUsers().size()), chan->getTopic()));
		}
	}
	else { listAllChan(cmd); }
	usr->pushReply(":" + cmd.server->getName() + " " +rpl_listend(usr->getNickname()));
}

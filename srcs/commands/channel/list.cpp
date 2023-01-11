#include "commandHandlers.hpp"
#include "utils.hpp"

// ERR_TOOMANYMATCHES

static void	listAllChan(Command &cmd)
{
	std::vector<Channel *> channels = Command::server->getChannels();

	std::vector<Channel *>::iterator it = channels.begin();
	std::vector<Channel *>::iterator it_end = channels.end();
	User *user = cmd.getUser();
	
	for (; it < it_end; it++)
		user->pushReply(rpl_list((*it)->getName(), "#", (*it)->getTopic())); // what for <# visible>
}

void	list(Command &cmd)
{
	User *user = cmd.getUser();

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
			user->pushReply(rpl_list(chan->getName(), "#", chan->getTopic())); // what for <# visible>
		}
	}
	else { listAllChan(cmd); }
	user->pushReply(rpl_listend());
}

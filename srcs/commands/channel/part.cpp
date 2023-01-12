#include "commandHandlers.hpp"
#include "utils.hpp"

void	part(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "PART"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	for (; it < it_end; it++)
	{
		if (!Command::server->isExistingChannelByName(*it))
		{
			usr->pushReply(err_nosuchchannel(usr->getNickname(), *it));
			continue;
		}
		Channel	*chan = Command::server->getChannelByName(*it);
		if (!chan->isJoinedUser(usr))
		{
			usr->pushReply(err_notonchannel(usr->getNickname(), chan->getName()));
			continue;
		}
		chan->removeUser(usr);
		usr->removeJoinedChan(chan);
	}
}

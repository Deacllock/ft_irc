#include "commandHandlers.hpp"
#include "utils.hpp"

void	part(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return user->pushReply(err_needmoreparams(user->getUsername().c_str(), "PART"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	for (; it < it_end; it++)
	{
		if (!Command::server->isExistingChannelByName(*it))
		{
			user->pushReply(err_nosuchchannel(*it));
			continue;
		}
		Channel	*chan = Command::server->getChannelByName(*it);
		if (!chan->isJoinedUser(user))
		{
			user->pushReply(err_notonchannel(chan->getName()));
			continue;
		}
		chan->removeUser(user);
		user->removeJoinedChan(chan);
	}
}

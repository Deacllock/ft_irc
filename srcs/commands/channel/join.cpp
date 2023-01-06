#include "commandHandlers.hpp"

#include <iostream>

// ERR_INVITEONLYCHAN
// ERR_TOOMANYTARGETS
// ERR_UNVAILRESOURCE
// ERR_BADCHANMASK

static std::vector<std::string>	splitByComma(std::string str)
{
	std::vector<std::string> vec;

	std::string elem;
	std::istringstream ss(str);
	while (getline(ss, elem, ','))
		vec.push_back(elem);
	
	return vec;
}

void	join(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return cmd.addOutput(err_needmoreparams(user->getUsername().c_str(), "JOIN"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);
	std::vector<std::string> keys;
	if (cmd.getParams().size() > 1)
		keys = splitByComma(cmd.getParams()[1]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	std::vector<std::string>::iterator it_k = keys.begin();
	std::vector<std::string>::iterator it_k_end = keys.end();
	for (; it < it_end; it++, it_k++)
	{
		if (*it == "0")
		{
			user->quitAllChan();
			continue;
		}
		if (!Command::server->isExistingChannelByName(*it))
		{
			cmd.addOutput(err_nosuchchannel(*it));
			continue;
		}
		Channel	*chan = Command::server->getChannelByName(*it);
		if (it_k < it_k_end)
		{
			if (*it_k != chan->getKey())
			{
				cmd.addOutput(err_badchannelkey(chan->getName()));
				continue;
			}
		}
		if (chan->isBannedUser(*user))
		{
			cmd.addOutput(err_bannedfromchan(chan->getName()));
			continue;
		}
		if (user->tooManyChanJoined())
			return cmd.addOutput(err_toomanychannels(chan->getName()));
		if (chan->isChannelFull())
		{
			cmd.addOutput(err_channelisfull(chan->getName()));
			continue;
		}
		if (chan->getTopic() != "")
			cmd.addOutput(rpl_topic(chan->getName(), chan->getTopic()));

		// join the chan
		chan->addUser(user);
		user->addJoinedChan(chan);
	}
}

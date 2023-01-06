#include "commandHandlers.hpp"

#include <iostream>

// ERR_INVITEONLYCHAN
// ERR_BADCHANNELKEY
// ERR_UNVAILRESOURCE

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

	if (cmd.getParams().size() < 1 || cmd.getParams().size() > 2) // how we do when more params ?
		return user->pushReply(err_needmoreparams(user->getUsername().c_str(), "JOIN"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);
	std::vector<std::string> keys = splitByComma(cmd.getParams()[1]);

	if (channels.size() < keys.size()) //what do we do?
	{
		std::cout << "Error" << std::endl;
		return;
	}
	
	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	for (; it < it_end; it++)
	{
		if (*it == "0")
		{
			user->quitAllChan();
			continue;
		}
		if (!Command::server->isExistingChannelByName(*it))
		{
			user->pushReply(err_nosuchchannel(*it));
			continue;
		}
		// if to many chan with this name	ERR_TOOMANYTARGETS
		// if bad mask						ERR_BADCHANMASK
		Channel	*chan = Command::server->getChannelByName(*it);
		if (chan->isBannedUser(user))
		{
			user->pushReply(err_bannedfromchan(chan->getName()));
			continue;
		}
		if (user->tooManyChanJoined())
			return user->pushReply(err_toomanychannels(chan->getName()));
		if (chan->isChannelFull())
		{
			user->pushReply(err_channelisfull(chan->getName()));
			continue;
		}
	}
	// RPL_TOPIC
}

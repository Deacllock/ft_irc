#include "commandHandlers.hpp"

#include <iostream>

// ERR_INVITEONLYCHAN
// ERR_BADCHANNELKEY
// ERR_UNVAILRESOURCE

void	join(Command &cmd)
{
	User	*user = cmd.getUser();
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	if (cmd.getParams().size() < 1 || cmd.getParams().size() > 2) // how we do when more params ?
		return cmd.addOutput(err_needmoreparams(user->getUsername().c_str(), "JOIN"));
	
	std::string elem;
	std::istringstream ss(cmd.getParams()[0]);
	while (getline(ss, elem, ','))
		channels.push_back(elem);
	std::istringstream ss1(cmd.getParams()[1]);
	while (getline(ss1, elem, ','))
		keys.push_back(elem);

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
			cmd.addOutput(err_nosuchchannel(*it));
			continue;
		}
		// if to many chan with this name	ERR_TOOMANYTARGETS
		// if bad mask						ERR_BADCHANMASK
		Channel	*chan = Command::server->getChannelByName(*it);
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
	}
	// RPL_TOPIC
}

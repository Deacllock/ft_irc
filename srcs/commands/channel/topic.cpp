#include "commandHandlers.hpp"

#include <iostream>

// ERR_CHANOPRIVSNEEDED
// EER_NOCHANMODES
void	topic(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() < 1 || cmd.getParams().size() > 2) // how we do when more params ?
		return cmd.addOutput(err_needmoreparams(user->getUsername().c_str(), "TOPIC"));
	
	std::string	channel = cmd.getParams()[0];
	bool		hasTopic = cmd.getParams().size() > 1 && cmd.getParams()[1].at(0) == ':';
	std::string	topic = "";
	if (hasTopic && cmd.getParams()[1].size() > 1)
		topic = cmd.getParams()[1].substr(1, str.size() - 1);

	if (!user->isOnChan(channel))
		return cmd.addOutput(err_notonchannel(channel));
	Channel	*chan = Command::server->getChannelByName(channel);
	if (hasTopic)
		chan->setTopic(topic);
	else
	{
		if (chan->getTopic() == "")
			return cmd.addOutput(rpl_notopic(channel));
		return cmd.addOutput(rpl_topic(channel, chan->getTopic()));
	}
}

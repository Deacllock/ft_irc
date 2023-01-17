#include "commandHandlers.hpp"

void	topic(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "TOPIC"));
	
	std::string	channel = cmd.getParams()[0];
	bool		hasTopic = cmd.getParams().size() > 1 && cmd.getParams()[1].at(0) == ':';
	std::string	topic = "";

	if (hasTopic && cmd.getParams()[1].size() > 1)
		topic = cmd.getParams()[1].substr(1, cmd.getParams()[1].size() - 1);

	if (!usr->isOnChan(channel))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_notonchannel(usr->getNickname(), channel));

	Channel	*chan = Command::server->getChannelByName(channel);

	if (!chan->isOperatorUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	if (hasTopic)
		chan->setTopic(topic);
	else
	{
		if (chan->getTopic() == "")
			return usr->pushReply(":" + cmd.server->getName() + " " + rpl_notopic(usr->getNickname(), channel));
		return usr->pushReply(":" + cmd.server->getName() + " " + rpl_topic(usr->getNickname(), channel, chan->getTopic()));
	}
}

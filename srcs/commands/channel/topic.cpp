#include "commandHandlers.hpp"

/**
 * @brief The TOPIC command is used to change or view the topic of a channel.
 * 
 * Parameters: <channel> [ <topic> ]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	topic(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "TOPIC"));

	Channel *chan = Command::server->getChannelByName(cmd.getParams()[0]);

	if (cmd.getParams().size() == 1)
	{
		if (chan->getTopic() == "")
			return usr->pushReply(":" + cmd.server->getName() + " " + rpl_notopic(usr->getNickname(), chan->getName()));
		return usr->pushReply(":" + cmd.server->getName() + " " + rpl_topic(usr->getNickname(), chan->getName(), chan->getTopic()));
	}

	std::string topic;
	if (cmd.getParams()[1][0] == ':')
		topic = cmd.getParams()[1].substr(1, cmd.getParams()[1].size() - 1);
	else
		topic = cmd.getParams()[1];

	if (!chan->isJoinedUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_notonchannel(usr->getNickname(), chan->getName()));

	if (!chan->isOperatorUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	chan->setTopic(topic);
	sendAll(chan->getUsers(), NULL, ":" + cmd.server->getName() + " " + rpl_topic(usr->getNickname(), chan->getName(), chan->getTopic()));
	
}

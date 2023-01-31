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

	if (cmd.getParams().size() < 1 || cmd.getParams()[0] == "")
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "TOPIC"));

	Channel *chan = Command::server->getChannelByName(cmd.getParams()[0]);
	if (!chan)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchchannel(usr->getNickname(), cmd.getParams()[0]));

	if (cmd.getParams().size() == 1 || cmd.getParams()[1] != "")
	{
		if (chan->getTopic() == "")
			return usr->pushReply(":" + cmd.server->getName() + " " + rpl_notopic(usr->getNickname(), chan->getName()));
		return usr->pushReply(":" + cmd.server->getName() + " " + rpl_topic(usr->getNickname(), chan->getName(), chan->getTopic()));
	}

	if (!chan->isJoinedUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_notonchannel(usr->getNickname(), chan->getName()));

	std::string topic;
	topic = cmd.getParams()[1];

	chan->setTopic(topic);
	sendAll(chan->getUsers(), NULL, ":" + usr->getFullName() + " TOPIC " + chan->getName() + " " + topic);	
}

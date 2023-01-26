#include "commandHandlers.hpp"

/**
 * @brief The INVITE command is used to invite a user to a channel.
 * 
 * Parameters: <nickname> <channel>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	invite(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "INVITE"));
	
	std::string nickname = cmd.getParams()[0];
	std::string channel = cmd.getParams()[1];

	Channel	*chan = Command::server->getChannelByName(channel);
	if (!chan)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchchannel(usr->getNickname(), channel));

	if (!chan->isJoinedUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_notonchannel(usr->getNickname(), chan->getName()));
	
	if (!chan->isOperatorUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	if (!Command::server->isExistingUserByName(nickname))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchnick(usr->getNickname(), nickname));

	User	*userToInvite = Command::server->getUserByName(nickname);
	if (chan->isJoinedUser(userToInvite))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_useronchannel(usr->getNickname(), nickname, channel));

	chan->addInvited(userToInvite);

	usr->pushReply(":" + cmd.server->getName() + " " + rpl_inviting(usr->getNickname(), channel, nickname));
	userToInvite->pushReply(":" + usr->getFullName() + " INVITE " + nickname + " " + channel);
}

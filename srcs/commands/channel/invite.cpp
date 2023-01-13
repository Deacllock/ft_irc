#include "commandHandlers.hpp"

void	invite(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 2)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "INVITE"));
	
	std::string nickname = cmd.getParams()[0];
	std::string channel = cmd.getParams()[1];

	Channel	*chan = Command::server->getChannelByName(channel);
	if (!chan->isJoinedUser(usr))
		return usr->pushReply(err_notonchannel(usr->getNickname(), chan->getName()));
	//ERR_CHANOPRIVSNEEDED
	if (!Command::server->isExistingUserByName(nickname))
		return usr->pushReply(err_nosuchnick(usr->getNickname(), nickname));
	User	*userToInvite = Command::server->getUserByName(nickname);
	if (chan->isJoinedUser(userToInvite))
		return usr->pushReply(err_useronchannel(usr->getNickname(), nickname, channel));
	// INVITE
	usr->pushReply(rpl_inviting(usr->getNickname(), channel, nickname));
	//RPL_AWAY
}

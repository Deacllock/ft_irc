#include "commandHandlers.hpp"

#include <iostream>

void	invite(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() != 2)
		return user->pushReply(err_needmoreparams(user->getUsername().c_str(), "INVITE"));
	
	std::string nickname = cmd.getParams()[0];
	std::string channel = cmd.getParams()[1];

	Channel	*chan = Command::server->getChannelByName(channel);
	if (!chan->isJoinedUser(*user))
		return user->pushReply(err_notonchannel(chan->getName()));
	//ERR_CHANOPRIVSNEEDED
	if (!Command::server->isExistingUserByName(nickname))
		return user->pushReply(err_nosuchnick(nickname));
	User	*userToInvite = Command::server->getUserByName(nickname);
	if (chan->isJoinedUser(*userToInvite))
		return user->pushReply(err_useronchannel(nickname, channel));
	// INVITE
	user->pushReply(rpl_inviting(channel, nickname));
	//RPL_AWAY
}

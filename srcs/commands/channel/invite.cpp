#include "commandHandlers.hpp"

#include <iostream>

//RPL_INVITING
//RPL_AWAY

void	invite(Command &cmd)
{
	User	*user = cmd.getUser();

	if (cmd.getParams().size() != 2)
		return cmd.addOutput(err_needmoreparams(user->getUsername().c_str(), "INVITE"));
	
	std::string nickname = cmd.getParams()[0];
	std::string channel = cmd.getParams()[1];

	Channel	*chan = Command::server->getChannelByName(channel);
	if (!chan->isJoinedUser(*user))
		return cmd.addOutput(err_notonchannel(chan->getName()));
	//ERR_CHANOPRIVSNEEDED
	if (!Command::server->isExistingUserByName(nickname))
		return cmd.addOutput(err_nosuchnick(nickname));
	User	*userToInvite = Command::server->getUserByName(nickname);
	if (chan->isJoinedUser(*userToInvite))
		return cmd.addOutput(err_userinchannel(nickname, channel));
	// INVITE
}

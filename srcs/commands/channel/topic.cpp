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
	bool		hasTopic = cmd.getParams().size() > 1;
	if (hasTopic)
		std::string topic = cmd.getParams()[1];

	if (!user->isOnChan(channel))
		return cmd.addOutput(err_notonchannel(channel));
}

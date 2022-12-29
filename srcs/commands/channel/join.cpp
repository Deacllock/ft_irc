#include "CommandHandlers.hpp"

/*
ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
ERR_CHANNELISFULL               ERR_BADCHANMASK
ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
RPL_TOPIC
*/

void	join(Command &cmd)
{
	const char	*username = cmd.getUser()->getUsername().c_str();
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	if (cmd.getParams().size() < 1)
		cmd.setOutput(err_needmoreparams(username, "JOIN"));
}

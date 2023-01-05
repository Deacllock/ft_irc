#include "commandHandlers.hpp"

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
	User	*user = cmd.getUser();
	std::vector<std::string> channels;
	std::vector<std::string> keys;

	if (cmd.getParams().size() < 1 || cmd.getParams().size() > 2) // how we do when more params ?
		user->pushReply(err_needmoreparams(user->getUsername().c_str(), "JOIN"));
	
	std::string elem;
	std::istringstream ss(cmd.getParams()[0]);
	while (getline(ss, elem, ','))
		channels.push_back(elem);
	std::istringstream ss1(cmd.getParams()[1]);
	while (getline(ss1, elem, ','))
		keys.push_back(elem);
}

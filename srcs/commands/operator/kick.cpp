#include "commandHandlers.hpp"

/**
 * @brief ExtractList split a string with ',' delimiter.
 * 
 * @param input String to parse.
 * @return std::vector<std::string> Vector containing splitted string elements.
 */
static std::vector<std::string> extractList( std::string input )
{
	std::vector<std::string> ret;
	std::istringstream ss(input);
	std::string elm;
	while (getline(ss, elm, ' '))
		ret.push_back(elm);
	return ret;
}

/**
 * @brief Procede to channel and user commanding kick user to make sure the kick is possible.
 * 
 * @param channel Channel to kick a user from.
 * @param usr User who operate the kick command.
 * @return bool If everythink is validated, returns true, otherwise false.
 */
static bool isKickPossible( Channel *channel, User *usr )
{
	if (!channel)
	{
		usr->pushReply(err_nosuchchannel(channel->getName()));
		return false;
	}
	if (!channel->isJoinedUser(usr))
	{	
		usr->pushReply(err_notonchannel(channel->getName()));
		return false;
	}
	if (!channel->isOperatorUser(usr))
	{
		usr->pushReply(err_chanoprivsneeded(channel->getName()));
		return false;
	}
	return true;
}

/**
 * @brief Procede to kick a user from a channel.
 * 
 * @param channel Channel to kick the user from.
 * @param cmd Class containing user processing the command and Server information.
 * @param nickToKill User to kick from the channel.
 */
static void kickUser( Channel *channel, Command &cmd, std::string nickToKill )
{
	User *toKick = cmd.server->getUserByName(nickToKill);
	if (!channel->isJoinedUser(toKick))
		cmd.getUser()->pushReply(err_usernotinchannel(nickToKill, channel->getName()));
	// else
	// 	curChan->sendMessage()
}

/**
 * @brief  The KICK command can be used to request the forced removal of a user from a channel.
 * Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
 * @param cmd Command class containing parameters, usr and connection state to use.
 */
void	kick(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() < 2)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "KICK"));	

	std::vector<std::string> channels = extractList(params[0]);
	std::vector<std::string> users = extractList(params[1]);

	if (channels.size() != users.size() && channels.size() != 1)
		return usr->pushReply(error("Syntax error")); //??
	
	if (channels.size() == 1)
	{
		Channel *curChan = cmd.server->getChannelByName(channels[0]);
		if (isKickPossible(curChan, usr))
			for (size_t i = 0; i < users.size(); i++)
				kickUser(curChan, cmd, users[i]);
		return;
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel *curChan = cmd.server->getChannelByName(channels[i]);
		if (isKickPossible(curChan, usr))
			kickUser(curChan, cmd, users[i]);
	} 
}
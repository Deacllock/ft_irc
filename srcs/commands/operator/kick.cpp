#include "commandHandlers.hpp"
#include "utils.hpp"

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
		usr->pushReply(":" + usr->server->getName() + " " + err_nosuchchannel(usr->getNickname(), channel->getName()));
		return false;
	}
	if (!channel->isJoinedUser(usr))
	{	
		usr->pushReply(":" + usr->server->getName() + " " + err_notonchannel(usr->getNickname(), channel->getName()));
		return false;
	}
	if (!channel->isOperatorUser(usr))
	{
		usr->pushReply(":" + usr->server->getName() + " " + err_chanoprivsneeded(channel->getName()));
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
static void kickUser( Channel *channel, Command &cmd, std::string nickToKick )
{
	User *toKick = cmd.server->getUserByName(nickToKick);
	User *usr = cmd.getUser();
	if (!channel->isJoinedUser(toKick))
		usr->pushReply(":" + cmd.server->getName() + " " + err_usernotinchannel(cmd.getUser()->getNickname(), nickToKick, channel->getName()));
	else
	{
		std::string msg = "";
		size_t i = 1;
		while (i < cmd.getParams().size() && cmd.getParams()[i][0] != ':')
			i++;
		if (i < cmd.getParams().size())
			msg = " :" + getColonMsg(cmd.getParams(), i);
		sendAll(cmd.server->getUsers(), NULL, ":" + usr->getNickname() + " KICK " + channel->getName() + " " + nickToKick + msg);
	}
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
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "KICK"));	

	std::vector<std::string> channels = splitByComma(params[0]);
	std::vector<std::string> users = splitByComma(params[1]);

	if (channels.size() != users.size() && channels.size() != 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + error(usr->getNickname(), "Syntax error")); //??
	
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

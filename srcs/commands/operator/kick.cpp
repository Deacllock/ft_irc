#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief Procede to channel and user commanding kick user to make sure the kick is possible.
 * 
 * @param channel Channel to kick a user from.
 * @param usr User who operate the kick command.
 * @return bool If everythink is valid, returns true, otherwise false.
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
 * @param cmd Contains command, parameters, user and server infos.
 * @param nickToKill User to kick from the channel.
 * @param comment Msg to send to user to explain kick.
 */
static void kickUser( Channel *channel, Command cmd, std::string nickToKick, std::string comment )
{
	User *toKick = cmd.server->getUserByName(nickToKick);
	User *usr = cmd.getUser();

	if (!channel->isJoinedUser(toKick))
		usr->pushReply(":" + cmd.server->getName() + " " + err_usernotinchannel(cmd.getUser()->getNickname(), nickToKick, channel->getName()));

	else
	{
		toKick->pushReply(":" + usr->getFullName() + " KICK " + channel->getName() + " " + nickToKick + comment);
		sendAll(channel->getUsers(), toKick, ":" + toKick->getFullName() + " PART " + channel->getName() + " :Kicked by " + usr->getNickname() + comment);
		channel->removeOperator(toKick);
		channel->removeUser(toKick);
		toKick->removeJoinedChan(channel);
	}
}

/**
 * @brief  The KICK command can be used to request the forced removal of a user from a channel.
 * 
 * Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	kick(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "KICK"));	

	std::vector<std::string> channels = splitByComma(params[0]);
	std::vector<std::string> users = splitByComma(params[1]);
	std::string comment = " :Pitiful kicker kicked again";

	if (params.size() > 2 && params[2] != ":")
		comment = " " + params[2];

	if (channels.size() != users.size() && channels.size() != 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + error("KICK :Syntax error"));
	
	if (channels.size() == 1)
	{
		Channel *curChan = cmd.server->getChannelByName(channels[0]);
		if (!curChan)
			return usr->pushReply(":" + usr->server->getName() + " " + err_nosuchchannel(usr->getNickname(), channels[0]));
	
		if (isKickPossible(curChan, usr))
			for (size_t i = 0; i < users.size(); i++)
				kickUser(curChan, cmd, users[i], comment);
		return;
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		Channel *curChan = cmd.server->getChannelByName(channels[i]);
		if (!curChan)
			return usr->pushReply(":" + usr->server->getName() + " " + err_nosuchchannel(usr->getNickname(), channels[i]));
	
		if (isKickPossible(curChan, usr))
			kickUser(curChan, cmd, users[i], comment);
	} 
}

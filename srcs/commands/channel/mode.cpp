#include "commandHandlers.hpp"

/**
 * @brief Set operator Mode in channel for a user;
 * 
 * @param usr 
 * @param chan 
 * @param params 
 * @param sym 
 * @param i 
 * @return std::string 
 */
static void operatorModeInChan(User *usr, Channel *chan, std::vector<std::string> &params, char sym, size_t i)
{
	User	*newOp;
	std::string	param;

	if (params.size() <= i || params[i][0] == '+' || params[i][0] == '-')
		return usr->pushReply(":" + usr->server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));
	
	param = params[i];

	params.erase(params.begin() + i);
	if (!Command::server->isExistingUserByName(param))
		return usr->pushReply(":" + usr->server->getName() + " " + err_usernotinchannel(usr->getNickname(), param, chan->getName()));
	
	newOp = Command::server->getUserByName(param);
	if (!chan->isJoinedUser(newOp))
		return usr->pushReply(":" + usr->server->getName() + " " + err_usernotinchannel(usr->getNickname(), newOp->getNickname(), chan->getName()));	
	
	if (sym == '+')
		chan->addOperator(newOp);
	else
		chan->removeOperator(newOp);

	sendAll(chan->getUsers(), NULL, ":" + usr->server->getName() + " " +  rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "o", param));
}

static void	setLimitInChan(User *usr, Channel *chan, std::vector<std::string> &params, char sym, size_t i)
{
	std::string	param;

	if (sym == '+')
	{
		if (params.size() <= i || params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(":" + usr->server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));
		param = params[i];
		chan->setLimit(stringToULong(param)); //no verif?
		params.erase(params.begin() + i);
	}
	else
	{
		chan->setLimit(-1);
		param = "";
	}
	sendAll(chan->getUsers(), NULL, ":" + usr->server->getName() + " " + rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "l", param));
}

static void	setInviteOnlyForChan(User *usr, Channel *chan, char sym)
{
	chan->setInviteOnly(sym == '+');
	sendAll(chan->getUsers(), NULL, ":" + usr->server->getName() + " " +  rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "i", ""));
}

static void	setKeyForChan(User *usr, Channel *chan, std::vector<std::string> &params, char sym, size_t i)
{
	std::string	param;

	if (params.size() <= i || params[i][0] == '+' || params[i][0] == '-')
		return usr->pushReply(":" + usr->server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));
	
	param = params[i];

	params.erase(params.begin() + i);
	if (sym == '+')
	{
		if (chan->getKey() != "")
			return usr->pushReply(":" + usr->server->getName() + " " + err_keyset(usr->getNickname(), chan->getName()));
		chan->setKey(param);
	}
	else if (chan->getKey() == param)
		chan->setKey("");

	sendAll(chan->getUsers(), NULL, ":" + usr->server->getName() + " " + rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "k", param));
}

static	void	do_rpl_banlist(Command cmd, User *usr, Channel *chan)
{
	std::vector<User *>	banned = chan->getBanned();

	if (!banned.empty())
	{
		std::vector<User *>::iterator	it = banned.begin();
		std::vector<User *>::iterator	it_end = banned.end();

		for (; it < it_end; it++)
			sendAll(chan->getUsers(), NULL, ":" + cmd.server->getName() + " " + rpl_banlist(usr->getNickname(), chan->getName(), (*it)->getNickname()));
	}
	sendAll(chan->getUsers(), NULL, ":" + cmd.server->getName() + " " + rpl_banlistend(usr->getNickname(), chan->getName()));
}

static  void	setBanForChan(Command cmd, User *usr, Channel *chan, std::vector<std::string> &params, char sym, size_t i)
{
	std::string					param;
	User						*usrBan;

	if (params.size() <= i || params[i][0] == '+' || params[i][0] == '-')
	{
		if (sym == '+')
			return do_rpl_banlist(cmd, usr, chan);
		else
			return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));
	}

	param = params[i];

	params.erase(params.begin() + i);

	std::vector<std::string> users = splitByComma(param);
	std::vector<std::string>::iterator	it = users.begin();
	std::vector<std::string>::iterator	it_end = users.end();

	for (; it < it_end; it++)
	{
		if (Command::server->isExistingUserByName(*it))
		{
			usrBan = Command::server->getUserByNickname(*it);
			if (sym == '-')
				chan->removeBannedUser(usrBan);
			else
			{
				chan->addBannedUser(usrBan);
				kick(Command(usr, "KICK " + chan->getName() + " " + *it + " :Banned from " + chan->getName()));
			}
		}
	}
	sendAll(chan->getUsers(), NULL, ":" + cmd.server->getName() + " " + rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "b", param));
}

static void	infos_chan(User *usr, Channel *chan)
{
	std::string		mode = "+";
	unsigned long	limit = -1;
	
	if (chan->isInviteOnly())
		mode += "i";
	if (chan->getLimit() != limit)
		mode += "l " + intToString(chan->getLimit());

	sendAll(chan->getUsers(), NULL, ":" + usr->server->getName() + " " + rpl_channelmodeis(usr->getNickname(), chan->getName(), mode, ""));
}

/**
 * @brief The MODE command is provided so that users may query and change the characteristics of a channel.
 * 
 * Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
 * o - add/remove channel operator mode on user
 * l - set user limit for the channel
 * i - set invite only option on channel
 * k - set key for the channel
 * b - set ban for the channel
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	channel_mode(Command cmd)
{
	User						*usr = cmd.getUser();
	std::vector<std::string>	params = cmd.getParams();

	Channel	*chan = Command::server->getChannelByName(params[0]);

	if (!chan->isJoinedUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_usernotinchannel(usr->getNickname(), usr->getNickname(), chan->getName()));
	
	if (params.size() == 1)
		return infos_chan(cmd.getUser(), chan);
	
	if (!chan->isOperatorUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	char sym = '+';
	size_t i = 1;
	while( i < params.size())
	{
		for (size_t j = 0; j < params[i].size(); j++)
		{
			switch (params[i][j])
			{
				case '+':
					sym = '+';
					break;
				case '-':
					sym = '-';
					break;
				case 'o': // make someone op in chan - or supp op
					operatorModeInChan(usr, chan, params, sym, i + 1);
					break;
				case 'l': // set limit for chan
					setLimitInChan(usr, chan, params, sym, i + 1);
					break;
				case 'i': // set inviteonly chan
					setInviteOnlyForChan(usr, chan, sym);
					break;
				case 'k': // set key for chan
					setKeyForChan(usr, chan, params, sym, i + 1);
					break;
				case 'b': // set ban for chan
					setBanForChan(cmd, usr, chan, params, sym, i + 1);
					break;
				default:
					usr->pushReply(":" + cmd.server->getName() + " " + err_unknownmode(usr->getNickname(), charToString(params[i][j]), chan->getName()));
			}
		}
		i++;
	}
}

/*
	limit of 3 changes per commands
*/


/**
 * @brief Mode command is used to set or remove options from target
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	mode(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));

	std::string name = cmd.getParams()[0];
	if (Command::server->isExistingChannelByName(name))
		channel_mode(cmd);
	else
		user_mode(cmd);
}

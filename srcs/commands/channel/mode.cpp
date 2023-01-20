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
static std::string operatorModeInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	User	*newOp;
	std::string	param = params[i];

	if (sym == '+')
	{
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");
		if (!Command::server->isExistingUserByName(param))
			return err_usernotinchannel(usr->getNickname(), param, chan->getName());
		newOp = Command::server->getUserByName(param);
		if (!chan->isJoinedUser(newOp))
			return err_usernotinchannel(usr->getNickname(), newOp->getNickname(), chan->getName());
		chan->addOperator(newOp);
	}
	else
	{
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");
		if (!Command::server->isExistingUserByName(param))
			return err_usernotinchannel(usr->getNickname(), param, chan->getName());
		newOp = Command::server->getUserByName(param);
		if (!chan->isJoinedUser(newOp))
			return err_usernotinchannel(usr->getNickname(), newOp->getNickname(), chan->getName());
		chan->removeOperator(newOp);
	}
	if (param[0] == '+' || param[0] == '-')
		param = "";
	return rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "o", param);
}

static  std::string	setLimitInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::string	param = params[i];
	
	if (sym == '+')
	{
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");
		chan->setLimit(stringToULong(param));
		if (param[0] == '+' || param[0] == '-')
			param = "";
	}
	else
	{
		chan->setLimit(-1);
		param = "";
	}
	return rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "l", param);
}

static  std::string	setInviteOnlyForChan(User *usr, Channel *chan, char sym)
{
	chan->setInviteOnly(sym == '+');
	return rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "i", "");
}

static  std::string	setKeyForChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::string	param = params[i];

	if (sym == '+')
	{
		if (chan->getKey() != "")
			return err_keyset(usr->getNickname(), chan->getName());
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");
		chan->setKey(param);
	}
	else
	{
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");
		if (chan->getKey() == param)
			chan->setKey("");
	}
	if (param[0] == '+' || param[0] == '-')
		param = "";
	return rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "o", param);
}

static	std::string		do_rpl_banlist(User *usr)
{
	return err_needmoreparams(usr->getNickname(), "MODE");
}

static  std::string	setBanForChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::string					param = params[i];
	std::vector<std::string>	users;
	User						*usrBan;

	if (sym == '+')
	{
		if (param[0] == '+' || param[0] == '-')
			return do_rpl_banlist(usr);
		
		users = splitByComma(param);
		std::vector<std::string>::iterator	it = users.begin();
		std::vector<std::string>::iterator	it_end = users.end();

		for (; it < it_end; it++)
		{
			if (Command::server->isExistingUserByName(*it))
			{
				usrBan = Command::server->getUserByNickname(*it);
				chan->addBannedUser(usrBan);
				chan->removeUser(usrBan); // Supp user from chan ??
			}
		}
	}
	else
	{
		if (param[0] == '+' || param[0] == '-')
			return err_needmoreparams(usr->getNickname(), "MODE");

		users = splitByComma(param);
		std::vector<std::string>::iterator	it = users.begin();
		std::vector<std::string>::iterator	it_end = users.end();

		for (; it < it_end; it++)
		{
			if (Command::server->isExistingUserByName(*it))
			{
				usrBan = Command::server->getUserByNickname(*it);
				chan->removeBannedUser(usrBan);
			}
		}
	}
	if (param[0] == '+' || param[0] == '-')
		param = "";
	return rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "b", param);
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
	
	if (!chan->isOperatorUser(usr))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	char sym = '+';
	for (size_t i = 1; i < params.size(); i++)
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
					usr->pushReply(":" + cmd.server->getName() + " " + operatorModeInChan(usr, chan, params, sym, i + 1));
					break;
				case 'l': // set limit for chan
					usr->pushReply(":" + cmd.server->getName() + " " + setLimitInChan(usr, chan, params, sym, i + 1));
					break;
				case 'i': // set inviteonly chan
					usr->pushReply(":" + cmd.server->getName() + " " + setInviteOnlyForChan(usr, chan, sym));
					break;
				case 'k': // set key for chan
					usr->pushReply(":" + cmd.server->getName() + " " + setKeyForChan(usr, chan, params, sym, i + 1));
					break;
				case 'b': // set ban for chan
					usr->pushReply(":" + cmd.server->getName() + " " + setBanForChan(usr, chan, params, sym, i + 1));
					break;
				default:
					usr->pushReply(":" + cmd.server->getName() + " " + err_unknownmode(usr->getNickname(), charToString(params[i][j]), chan->getName()));
			}
		}
	}
}

/*
	ERR_KEYSET
    RPL_CHANNELMODEIS

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

	if (cmd.getParams().size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));

	std::string name = cmd.getParams()[0];
	if (Command::server->isExistingChannelByName(name))
		channel_mode(cmd);
	else
		user_mode(cmd);
}

#include "commandHandlers.hpp"

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
		if (!newOp->isOnChan(chan->getName()))
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
		if (!newOp->isOnChan(chan->getName()))
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

void	channel_mode(Command &cmd)
{
	User	*usr = cmd.getUser();
	std::vector<std::string> params = cmd.getParams();

	if (!Command::server->isExistingChannelByName(params[0]))
		return;
	
	Channel	*chan = Command::server->getChannelByName(params[0]);

	if (!usr->isOnChan(chan->getName()))
		return usr->pushReply(":" + cmd.server->getName() + " " + err_usernotinchannel(usr->getNickname(), usr->getNickname(), chan->getName()));
	
	if (!usr->isOperator())
		return usr->pushReply(":" + cmd.server->getName() + " " + err_chanoprivsneeded(chan->getName()));

	for (size_t i = 1; i < params.size(); i++)
	{
		char	sym = params[i][0];
		if (sym != '-' && sym != '+')
			continue;
		for (size_t j = 1; j < params[i].size(); j++)
		{
			switch (params[i][j])
			{
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
				default:
					usr->pushReply(":" + cmd.server->getName() + " " + err_unknownmode(usr->getNickname(), charToString(params[i][j]), chan->getName()));
			}
		}
	}
}

void	mode(Command &cmd) // See how to organize this part
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));

	if (Command::server->isExistingUserByName(usr->getNickname()))
		user_mode(cmd);
	else
		channel_mode(cmd);
}

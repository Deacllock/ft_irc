#include "commandHandlers.hpp"

static  void	operatorModeInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	User	*newOp;
	std::string	param = params[i];

	if (sym == '+')
	{
		if (param[0] == '+' || param[0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (!Command::server->isExistingUserByName(param))
			return usr->pushReply(err_usernotinchannel(usr->getNickname(), param, chan->getName()));
		newOp = Command::server->getUserByName(param);
		if (!newOp->isOnChan(chan->getName()))
			return usr->pushReply(err_usernotinchannel(usr->getNickname(), newOp->getNickname(), chan->getName()));
		chan->addOperator(newOp);
	}
	else
	{
		if (param[0] == '+' || param[0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (!Command::server->isExistingUserByName(param))
			return usr->pushReply(err_usernotinchannel(usr->getNickname(), param, chan->getName()));
		newOp = Command::server->getUserByName(param);
		if (!newOp->isOnChan(chan->getName()))
			return usr->pushReply(err_usernotinchannel(usr->getNickname(), newOp->getNickname(), chan->getName()));
		chan->removeOperator(newOp);
	}
	if (param[0] == '+' || param[0] == '-')
		param = "";
	usr->pushReply(rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "o", param));
}

static  void	setLimitInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::string	param = params[i];
	
	if (sym == '+')
	{
		if (param[0] == '+' || param[0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		chan->setLimit(stringToULong(param));
		if (param[0] == '+' || param[0] == '-')
			param = "";
	}
	else
	{
		chan->setLimit(-1);
		param = "";
	}
	usr->pushReply(rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "l", param));
}

static  void	setInviteOnlyForChan(User *usr, Channel *chan, char sym)
{
	if (sym == '+')
		chan->setInviteOnly(true);
	else
		chan->setInviteOnly(false);
	usr->pushReply(rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "i", ""));
}

static  void	setKeyForChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::string	param = params[i];

	if (sym == '+')
	{
		if (chan->getKey() != "")
			return usr->pushReply(err_keyset(usr->getNickname(), chan->getName()));
		if (param[0] == '+' || param[0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		chan->setKey(param);
	}
	else
	{
		if (param[0] == '+' || param[0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (chan->getKey() == param)
			chan->setKey("");
	}
	if (param[0] == '+' || param[0] == '-')
		param = "";
	usr->pushReply(rpl_channelmodeis(usr->getNickname(), chan->getName(), charToString(sym) + "o", param));
}

void	channel_mode(Command &cmd)
{
	User	*usr = cmd.getUser();
	std::vector<std::string> params = cmd.getParams();

	if (!Command::server->isExistingChannelByName(params[0]))
		return;
	
	Channel	*chan = Command::server->getChannelByName(params[0]);

	if (!usr->isOnChan(chan->getName()))
		return usr->pushReply(err_usernotinchannel(usr->getNickname(), usr->getNickname(), chan->getName()));
	
	if (!usr->isOperator())
		return usr->pushReply(err_chanoprivsneeded(chan->getName()));

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
				default:
					usr->pushReply(err_unknownmode(usr->getNickname(), charToString(params[i][j]), chan->getName()));
			}
		}
	}
}

void	mode(Command &cmd) // See how to organize this part
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 2)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));

	if (Command::server->isExistingUserByName(usr->getNickname()))
		user_mode(cmd);
	else
		channel_mode(cmd);
}

#include "commandHandlers.hpp"

static  void	operatorModeInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	User	*newOp;

	if (sym == '+')
	{
		if (params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (!Command::server->isExistingUserByName(params[i]))
			return usr->pushReply(err_usernotinchannel(params[i], chan->getName()));
		newOp = Command::server->getUserByName(params[i]);
		if (!newOp->isOnChan(chan->getName()))
			return usr->pushReply(err_usernotinchannel(newOp->getNickname(), chan->getName()));
		chan->addOperator(newOp);
	}
	else
	{
		if (params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (!Command::server->isExistingUserByName(params[i]))
			return usr->pushReply(err_usernotinchannel(params[i], chan->getName()));
		newOp = Command::server->getUserByName(params[i]);
		if (!newOp->isOnChan(chan->getName()))
			return usr->pushReply(err_usernotinchannel(newOp->getNickname(), chan->getName()));
		chan->removeOperator(newOp);
	}
}

static  void	setLimitInChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	std::stringstream	ss;
	unsigned long		limit;

	if (sym == '+')
	{
		if (params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		ss << params[i];
		ss >> limit;
		chan->setLimit(limit);
	}
	else
		chan->setLimit(-1);
}

static  void	setInviteOnlyForChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	(void)usr;
	(void)chan;
	(void)params;
	(void)sym;
	(void)i;
}

static  void	setKeyForChan(User *usr, Channel *chan, std::vector<std::string> params, char sym, size_t i)
{
	if (sym == '+')
	{
		if (chan->getKey() != "")
			return usr->pushReply(err_keyset(usr->getNickname(), chan->getName()));
		if (params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		chan->setKey(params[i]);
	}
	else
	{
		if (params[i][0] == '+' || params[i][0] == '-')
			return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
		if (chan->getKey() == params[i])
			chan->setKey("");
	}
}

// ERR_NOCHANMODES channel doesn't support modes ??

// RPL_CHANNELMODEIS
// RPL_INVITELIST RPL_ENDOFINVITELIST
// RPL_UNIQOPIS

void	channel_mode(Command &cmd)
{
	User	*usr = cmd.getUser();
	std::vector<std::string> params = cmd.getParams();
	Channel	*chan = Command::server->getChannelByName(params[0]);

	if (!usr->isOnChan(params[0]))
		return usr->pushReply(err_usernotinchannel(usr->getNickname(), params[0], chan->getName()));
	
	if (!usr->isOperator())
		return usr->pushReply(err_chanoprivsneeded(usr->getNickname(), params[0]));
	
	if (!usr->isOnChan(chan->getName()))
		return usr->pushReply(err_usernotinchannel(usr->getNickname(), chan->getName()));
	
	if (!usr->isOperator())
		return usr->pushReply(err_chanoprivsneeded(usr->getNickname(), chan->getName()));

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
					setInviteOnlyForChan(usr, chan, params, sym, i + 1);
					break;
				case 'k': // set key for chan
					setKeyForChan(usr, chan, params, sym, i + 1);
					break;
				default:
					usr->pushReply(err_unknownmode(usr->getNickname(), params[i][j], chan->getName()));
			}
		}
	}
}

void	mode(Command &cmd) // See how to organize this part
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 2)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));
	channel_mode(cmd);
}

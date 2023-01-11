#include "commandHandlers.hpp"
#include "utils.hpp"

// ERR_INVITEONLYCHAN
// ERR_TOOMANYTARGETS
// ERR_UNVAILRESOURCE

void	join(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "JOIN"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);
	std::vector<std::string> keys;
	if (cmd.getParams().size() > 1)
		keys = splitByComma(cmd.getParams()[1]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	std::vector<std::string>::iterator it_k = keys.begin();
	std::vector<std::string>::iterator it_k_end = keys.end();
	for (; it < it_end; it++, it_k++)
	{
		if (*it == "0")
		{
			usr->quitAllChan();
			continue;
		}
		if (!Command::server->isExistingChannelByName(*it))
		{
			usr->pushReply(err_nosuchchannel(usr->getNickname(), *it));
			continue;
		}
		Channel	*chan = Command::server->getChannelByName(*it);
		if (it_k < it_k_end)
		{
			if (*it_k != chan->getKey())
			{
				usr->pushReply(err_badchannelkey(usr->getNickname(), chan->getName()));
				continue;
			}
		}
		if (chan->isBannedUser(usr))
		{
			usr->pushReply(err_bannedfromchan(usr->getNickname(), chan->getName()));
			continue;
		}
		if (usr->tooManyChanJoined())
			return usr->pushReply(err_toomanychannels(usr->getNickname(), chan->getName()));
		if (chan->isChannelFull())
		{
			usr->pushReply(err_channelisfull(usr->getNickname(), chan->getName()));
			continue;
		}
		if (chan->getTopic() != "")
			usr->pushReply(rpl_topic(usr->getNickname(), chan->getName(), chan->getTopic()));

		// join the chan
		chan->addUser(usr);
		usr->addJoinedChan(chan);
	}
}

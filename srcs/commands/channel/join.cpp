#include "commandHandlers.hpp"
#include "utils.hpp"

void	join(Command &cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "JOIN"));
	
	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);
	std::vector<std::string> keys;
	if (cmd.getParams().size() > 1)
		keys = splitByComma(cmd.getParams()[1]);

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	std::vector<std::string>::iterator it_k = keys.begin();
	std::vector<std::string>::iterator it_k_end = keys.end();
	for (; it != it_end; it++)
	{
		if (*it == "0")
		{
			usr->quitAllChan();
			continue;
		}
		// CHECK NAME IS VALID
		if (!checkChannelName(*it))
		{
			usr->pushReply(":" + cmd.server->getName() + " " + err_badnamechannel(usr->getNickname(), *it));
			continue;
		}
		// CREATE CHAN
		if (!Command::server->isExistingChannelByName(*it))
		{
			Command::server->createChan(*it);
			Channel	*chanTMP = Command::server->getChannelByName(*it);
			chanTMP->addOperator(usr);
		}

		Channel	*chan = Command::server->getChannelByName(*it);
		
		// VERIF KEY
		if (it_k < it_k_end)
		{
			if (*it_k != chan->getKey())
			{
				usr->pushReply(":" + cmd.server->getName() + " " + err_badchannelkey(usr->getNickname(), chan->getName()));
				it_k++;
				continue;
			}
			it_k++;
		}

		if (chan->isBannedUser(usr))
		{
			usr->pushReply(":" + cmd.server->getName() + " " + err_bannedfromchan(usr->getNickname(), chan->getName()));
			continue;
		}

		if (chan->isInviteOnly() && !chan->isInvitedUser(usr))
			return usr->pushReply(":" + cmd.server->getName() + " " + err_inviteonlychan(usr->getNickname(), chan->getName()));
		if (usr->tooManyChanJoined())
			return usr->pushReply(":" + cmd.server->getName() + " " + err_toomanychannels(usr->getNickname(), chan->getName()));
		if (chan->isChannelFull())
		{
			usr->pushReply(":" + cmd.server->getName() + " " + err_channelisfull(usr->getNickname(), chan->getName()));
			continue;
		}
		
		if (chan->getTopic() != "")
			usr->pushReply(rpl_topic(usr->getNickname(), chan->getName(), chan->getTopic()));

		// JOIN
		chan->addUser(usr);
		sendAll(chan->getUsers(), NULL, ":" + usr->getNickname() + " JOIN " + chan->getName());
		usr->addJoinedChan(chan);
		chan->removeInvited(usr);
	}
}

#include "commandHandlers.hpp"

void	whois( Command cmd )
{
	User			*usr = cmd.getUser();
	User			*target;
	std::string		nick;
	std::string		channels_str = "";
	std::vector<Channel *>	channels;

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nonicknamegiven(usr->getNickname()));

	nick = cmd.getParams()[0];
	target = Command::server->getUserByNickname(nick);

	if (!target)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchnick(usr->getNickname(), nick));

	//rpl_whoisserver	->infos server params ?
	//rpl_away		->are we using away ?
	//rpl_whoisidle		->what is idle ?
	
	usr->pushReply(":" + cmd.server->getName() + " " + rpl_whoisuser(nick, target->getUsername(), "", target->getRealName()));

	channels = target->getJoinedChan();
	std::vector<Channel *>::iterator	it = channels.begin();
	std::vector<Channel *>::iterator	it_end = channels.end();
	for (; it < it_end; it++)
	{
		if ((*it)->isOperatorUser(target))
			channels_str += "@";
		else
			channels_str += "+";
		channels_str += (*it)->getName();
		channels_str += " ";
	}
	usr->pushReply(":" + cmd.server->getName() + " " + rpl_whoischannels(nick, channels_str));
	
	usr->pushReply(":" + cmd.server->getName() + " " + rpl_whoisserver(nick, cmd.server->getName(), ""));

	if (target->isOperator())
		usr->pushReply(":" + cmd.server->getName() + " " + rpl_whoisoperator(nick));

	usr->pushReply(":" + cmd.server->getName() + " " + rpl_endofwhois(nick));
}

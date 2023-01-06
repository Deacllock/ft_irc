#include "commandHandlers.hpp"

#include <iostream>

// ERR_TOOMANYMATCHES

static std::vector<std::string>	splitByComma(std::string str)
{
	std::vector<std::string> vec;

	std::string elem;
	std::istringstream ss(str);
	while (getline(ss, elem, ','))
		vec.push_back(elem);
	
	return vec;
}

static void	listAllUsers(Command &cmd)
{
	std::vector<std::string> channels = Command::server->getChannels();

	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();
	for (; it < it_end; it++)
	{
		std::vector<std::string> nicks;
		std::vector<Users *> users = (*it)->getUsers();
		std::vector<std::string>::iterator it_usr = users.begin();
		std::vector<std::string>::iterator it_usr_end = users.end();
		for (; it_usr < it_usr_end; it_usr++)
			nicks.push_back((*it_usr)->getNickname());
		cmd.addOutput(rpl_namreply((*it)->getName(), nicks));
	}
}

void	names(Command &cmd) // VISIBILITIES ??
{
	if (cmd.getParams().size() > 0)
	{
		std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);

		std::vector<std::string>::iterator it = channels.begin();
		std::vector<std::string>::iterator it_end = channels.end();
		for (; it < it_end; it++)
		{
			if (!Command::server->isExistingChannelByName(*it))
				continue;

			Channel	*chan = Command::server->getChannelByName(*it);
			std::vector<std::string> nicks;
			std::vector<Users *> users = chan->getUsers();
			std::vector<std::string>::iterator it_usr = users.begin();
			std::vector<std::string>::iterator it_usr_end = users.end();
			for (; it_usr < it_usr_end; it_usr++)
				nicks.push_back((*it_usr)->getNickname());
			cmd.addOutput(rpl_namreply(chan->getName(), nicks));
		}
	}
	else { listAllUsers(cmd); }
	cmd.addOutput(rpl_listend());
}
#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief List all users existing on server.
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
// static void	listAllUsers(Command cmd)
// {
// 	std::vector<Channel *> channels = Command::server->getChannels();

// 	std::vector<Channel *>::iterator it = channels.begin();
// 	std::vector<Channel *>::iterator it_end = channels.end();
// 	for (; it < it_end; it++)
// 	{
// 		std::vector<std::string> nicks;
// 		std::vector<User *> users = (*it)->getUsers();
// 		std::vector<User *>::iterator it_usr = users.begin();
// 		std::vector<User *>::iterator it_usr_end = users.end();
// 		for (; it_usr < it_usr_end; it_usr++)
// 			nicks.push_back((*it_usr)->getNickname());
// 		cmd.getUser()->pushReply(":" + cmd.server->getName() + " " +rpl_namreply(cmd.getUser()->getNickname(), (*it)->getName(), nicks));
// 	}
// }

static void	listAllUsers( std::vector<std::string> channels, User *usr )
{
	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it_end = channels.end();

	for (; it < it_end; it++)
	{
		if (!Command::server->isExistingChannelByName(*it))
			continue;
		
		Channel	*chan = Command::server->getChannelByName(*it);
		std::vector<User *> users = chan->getUsers();

		std::vector<User *>::iterator it_usr = users.begin();
		std::vector<User *>::iterator it_usr_end = users.end();
		for (; it_usr < it_usr_end; it_usr++)
			usr->pushReply(":" + Command::server->getName() + " " + rpl_namreply(usr->getNickname(), chan->getName(), (*it)->getName()));
		cmd.getUser()->pushReply(":" + cmd.server->getName() + " " + rpl_endofnames(cmd.getUser()->getNickname(), chan->getName()));
	}
}

/**
 * @brief By using the NAMES command, a user can list all nicknames that are visible to him.
 * 
 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	names(Command cmd)
{
	User *usr = cmd.getUser();
	if (cmd.getParams().size() == 0)
		return listAllUsers(urs->listAllChans(), usr);
	return listAllUsers(splitByComma(cmd.getParams()[0]), usr);


	
}

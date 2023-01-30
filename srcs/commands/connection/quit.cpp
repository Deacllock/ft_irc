#include "commandHandlers.hpp"

static void disconnectFromAllChannels(User *user)
{
	std::vector<Channel *> joinedChan = user->getJoinedChan();
	for (std::vector<Channel *>::iterator it = joinedChan.begin();
	it != joinedChan.end(); it++)
	{
		(*it)->removeBannedUser(user);
		(*it)->removeOperator(user);
		(*it)->removeUser(user);
	}
}

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * Parameters: [ <Quit Message> ]
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	quit(Command cmd)
{
	User *usr = cmd.getUser();

	usr->pushReply(":" + cmd.server->getName() + " " + error("Closing Link"));

	std::string msg = "";
	if (cmd.getParams().size())
		msg = " " + cmd.getParams()[0];

	usr->setStatus(DISCONNECTED);
	usr->sendAllChannels(":" + usr->getFullName() + " QUIT :Quit:" + msg);
	disconnectFromAllChannels(usr);
}

#include "commandHandlers.hpp"

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	quit(Command &cmd)
{
	User *usr = cmd.getUser();
	std::string msg = "";
	if (cmd.getParams().size())
		msg = getColonMsg(cmd.getParams(), 0);
	usr->pushReply(":" + cmd.server->getName() + " " + error(usr->getNickname(), msg));
	usr->setStatus(DISCONNECTED);
	usr->sendAllChannels(":" + usr->getNickname() + " QUIT " + msg);
}

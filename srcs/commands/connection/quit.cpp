#include "commandHandlers.hpp"

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	quit(Command cmd)
{
	User *usr = cmd.getUser();
	std::string msg = "";
	if (cmd.getParams().size())
		msg = cmd.getParams()[0];//getColonMsg(cmd.getParams(), 0);
	usr->pushReply(":" + cmd.server->getName() + " " + error("Closing Link: " + msg));
	usr->setStatus(DISCONNECTED);
	usr->sendAllChannels(":" + usr->getFullName() + " QUIT " + msg);
}

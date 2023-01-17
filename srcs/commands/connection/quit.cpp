#include "commandHandlers.hpp"

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	quit(Command &cmd)
{
	User *usr = cmd.getUser();

	usr->pushReply(":" + cmd.server->getName() + " " + error(usr->getNickname(), getColonMsg(cmd.getParams(), 0)));
	//shall output to all that a user has left ->request to all channel the user belongs to to send info to everyone except them
	usr->setStatus(DISCONNECTED);
	std::string msg = "";
	if (cmd.getParams().size())
		msg = getColonMsg(cmd.getParams(), 0);
	usr->sendAllChannels(":" + usr->getNickname() + " QUIT " + msg);
}

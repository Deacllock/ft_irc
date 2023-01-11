#include "commandHandlers.hpp"

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	quit(Command &cmd)
{
	cmd.getUser()->pushReply(error(cmd.getUser()->getNickname(), getColonMsg(cmd.getParams(), 0)));
	//shall output to all that a user has left ->request to all channel the user belongs to to send info to everyone except them
	cmd.getUser()->setStatus(DISCONNECTED);
}

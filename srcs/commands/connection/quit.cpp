#include "commandHandlers.hpp"

/**
 * @brief The QUIT command close the client session with a quit message.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	quit(Command &cmd)
{
	cmd.addOutput(error(getColonMsg(cmd.getParams(), 0)));
	cmd.server->removeUser(cmd.getUser());
	//shall output to all that a user has left
}

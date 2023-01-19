#include "commandHandlers.hpp"

/**
 * @brief An operator can use the DIE command to shutdown the server->
 * 
 * Parameters: None
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	die(Command cmd) 
{
	User	*usr = cmd.getUser();
	
	if (!usr->isOperator())
		usr->pushReply(":" + cmd.server->getName() + " " + err_noprivileges(usr->getNickname()));

	else
		cmd.server->setIsUp(false);
}
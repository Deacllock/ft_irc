#include "commandHandlers.hpp"

/**
 * @brief An operator can use the DIE command to shutdown the server->
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	die(Command &cmd) 
{
	User	*usr = cmd.getUser();
	
	if (!usr->isOperator())
		usr->pushReply(err_noprivileges());

	else
		cmd.server->setIsUp(false);
}

//CHECK WHEN HANDLING SEVERAL USERS
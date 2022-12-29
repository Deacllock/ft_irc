#include "commandHandlers.hpp"

/**
 * @brief The PASS command is used to set a 'connection password'
 * 
 * This command is used to verify the connection to the server is autorized by comparing
 * given password with server password.
 * 
 * @param cmd Command class containing parameters, user and connection state to use
 */

void	pass(Command &cmd)
{
	const char	*username = cmd.getUser()->getUsername().c_str();

	if (cmd.getUser()->getUsername() != "") //what is a registred user?
	 	cmd.addOutput(err_alreadyregistered(cmd.getUser()->getUsername().c_str()));
	else if (cmd.getParams().size() < 1)
		cmd.addOutput(err_needmoreparams(username, "PASS"));
	else if (Command::server->checkPassword(cmd.getParams()[0]))
	 	cmd.getUser()->setIsConnected(true);
	else
	 	cmd.getUser()->setIsConnected(false);
}

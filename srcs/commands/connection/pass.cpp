#include "commandHandlers.hpp"

/**
 * @brief The PASS command is used to set a 'connection password'
 * 
 * This command is used to verify the connection to the server is autorized by comparing
 * given password with server password.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	pass(Command &cmd)
{
	std::string	username = cmd.getUser()->getUsername();

	if (cmd.getUser()->getIsRegistered())
	 	cmd.setOutput(err_alreadyregistered(username));

	else if (cmd.getParams().size() < 1)
		cmd.setOutput(err_needmoreparams(username, "PASS"));

	else
		cmd.getUser()->setIsConnected(Command::server->checkPassword(cmd.getParams()[0]));
}
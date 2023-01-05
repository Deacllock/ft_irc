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
	User		*user = cmd.getUser();
	std::string	username = user->getUsername();

	if (user->getIsRegistered())
	 	user->pushReply(err_alreadyregistered(username));

	else if (cmd.getParams().size() < 1)
		user->pushReply(err_needmoreparams(username, "PASS"));

	else if (Command::server->checkPassword(cmd.getParams()[0]))
		user->setStatus(CONNECTED);

	else
		user->setStatus(STARTING);

}

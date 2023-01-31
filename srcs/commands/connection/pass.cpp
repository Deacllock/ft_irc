#include "commandHandlers.hpp"

/**
 * @brief The PASS command is used to set a 'connection password'
 * 
 * This command is used to verify the connection to the server is autorized by comparing
 * given password with server password.
 *
 * Parameters: <password>
 *  
 * @param cmd Contains command, parameters, user and server infos.
 */
void	pass(Command cmd)
{
	User		*usr = cmd.getUser();
	std::string	username = usr->getUsername();

	if (usr->isRegistered())
	 	usr->pushReply(":" + cmd.server->getName() + " " + err_alreadyregistered(usr->getNickname(), username));

	else if (cmd.getParams().size() < 1 || cmd.getParams()[0] == "")
		usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "PASS"));

	else if (Command::server->checkPassword(cmd.getParams()[0]))
		usr->setStatus(CONNECTED);

	else
		usr->setStatus(STARTING);
}

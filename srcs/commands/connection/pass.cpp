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
	User		*usr = cmd.getUser();
	std::string	username = usr->getUsername();

	if (usr->isRegistered())
	 	usr->pushReply(err_alreadyregistered(usr->getNickname(), username));

	else if (cmd.getParams().size() < 1)
		usr->pushReply(err_needmoreparams(usr->getNickname(), "PASS"));

	else if (Command::server->checkPassword(cmd.getParams()[0]))
		usr->setStatus(CONNECTED);

	else
		usr->setStatus(STARTING);

}

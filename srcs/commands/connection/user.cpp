#include "commandHandlers.hpp"

/**
 * @brief Check if user is newly registered to a server. If so greet them.
 * 
 * @param cmd Class containing the user to eventually greet.
 */
void greetNewComer( Command &cmd )
{
	User *usr = cmd.getUser();
	if (usr->isConnected() && usr->getNickname() != "" && usr->getUsername() != "")
	{
		usr->setStatus(REGISTERED);
		usr->pushReply(rpl_welcome(usr->getNickname(), cmd.server->getName()));
	}
}

/**
 * @brief The USER command is used at the beginning of connection to configure user.
 * 
 * User shall specify the username, hostname and realname of a new user.
 * A mode shall be given when creating the user.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	user( Command &cmd )
{
	User *usr = cmd.getUser();
	std::vector <std::string> params = cmd.getParams();

	if (usr->isRegistered())
		usr->pushReply(":" + cmd.server->getName() + " " + err_alreadyregistered(usr->getNickname(), usr->getUsername()));

	else if (params.size() < 4)
		usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "USER"));

	else
	{
		usr->setUsername(params[0]);
		usr->setRealName(getColonMsg(params, 3));
		greetNewComer(cmd);
	}
}
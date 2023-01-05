#include "commandHandlers.hpp"

void greetNewComer( Command &cmd )
{
	User *usr = cmd.getUser();
	if (usr->getIsConnected() && usr->getNickname() != "" && usr->getUsername() != "")
	{
		usr->setStatus(REGISTERED);
		usr->pushReply(rpl_welcome(usr->getNickname(), usr->getUsername(), cmd.server->getName()));
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

	if (usr->getIsRegistered())
		usr->pushReply(err_alreadyregistered(usr->getUsername()));
	else if (params.size() < 4)
		usr->pushReply(err_needmoreparams(usr->getUsername(), "USER"));
	else
	{
		usr->setUsername(params[0]);
		usr->setRealName(getColonMsg(params, 3));
		greetNewComer(cmd);
	}
}


//what about the order?
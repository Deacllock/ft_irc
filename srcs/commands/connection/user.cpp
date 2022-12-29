#include "commandHandlers.hpp"

void greetNewComer( Command &cmd )
{
	User *usr = cmd.getUser();
	if (!usr->getIsRegistered() && usr->getIsConnected() && usr->getNickname() != "" && usr->getUsername() != "")
	{
		usr->setIsRegistered(true);
		cmd.setOutput(rpl_welcome(usr->getNickname(), usr->getUsername(), cmd.server->getName()));
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
		cmd.setOutput(err_alreadyregistered(usr->getUsername()));
	else if (params.size() < 4)
		cmd.setOutput(err_needmoreparams(usr->getUsername(), "USER"));
	else
	{
		usr->setUsername(params[0]);
		std::string realName = params[3].substr(1, params[3].length()); // shall have : -> shall I check?

		for (size_t i = 4; i < params.size(); i++)
			realName = realName + " " + params[i];
		usr->setRealName(realName);
		greetNewComer(cmd);
	}
}


//what about the order?
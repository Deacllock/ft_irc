#include "commandHandlers.hpp"

/**
 * @brief Check if user is newly registered to a server. If so greet them.
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void greetNewComer( Command cmd )
{
	User *usr = cmd.getUser();
	if (usr->isConnected() && usr->getNickname() != "" && usr->getUsername() != "")
	{
		usr->setStatus(REGISTERED);
		usr->pushReply(":" + cmd.server->getName() + " " +rpl_welcome(usr->getNickname(), cmd.server->getName()));
		list(Command(usr, "LIST"));
	}
}

/**
 * @brief Check if given username is valid.
 * 
 * @param username username to check.
 * @return true if valid, false otherwise.
 */
static bool	isUsernameValid( std::string username )
{
	if (username == "")
		return false;

	for (size_t i = 0; i < username.length(); i++)
		if (username[i] == '\r' || username[i] == '\n' || username[i] == ' ' || username[i] == '@')
			return false;
	return true;
}

/**
 * @brief The USER command is used at the beginning of connection to configure user.
 * 
 * User shall specify the username, hostname and realname of a new user.
 * A mode shall be given when creating the user.
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	user( Command cmd )
{
	User *usr = cmd.getUser();
	std::vector <std::string> params = cmd.getParams();

	if (usr->isRegistered())
		usr->pushReply(":" + cmd.server->getName() + " " + err_alreadyregistered(usr->getNickname(), usr->getUsername()));

	else if (params.size() < 4)
		usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "USER"));

	else if (isUsernameValid(params[0]))
	{
		usr->setUsername(params[0]);
		if (params[3][0] == ':')
			usr->setRealName(params[3].substr(1, params[3].length()));
		else
			usr->setRealName(params[3]);
		greetNewComer(cmd);
	}
}
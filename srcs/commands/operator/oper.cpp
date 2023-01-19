#include "commandHandlers.hpp"

/**
 * @brief Oper command allow a user to become operator if valid credentials are provided.
 * 
 * Parameters: <name> <password>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	oper(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();

	if (params.size() < 2)
		usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "OPER"));

	else if (!cmd.server->checkOpeCredentials(params[0], params[1]))
		usr->pushReply(":" + cmd.server->getName() + " " + err_passwordmismatch(usr->getNickname()));

	else
	{
		usr->setOperator(true);
		usr->pushReply(":" + cmd.server->getName() + " " + rpl_youreoper(usr->getNickname()));
		usr->pushReply(":" + cmd.server->getName() + " " + rpl_umodeis(usr->getNickname(), "+o"));
	}
}

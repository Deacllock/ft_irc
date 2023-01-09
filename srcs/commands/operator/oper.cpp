#include "commandHandlers.hpp"

/**
 * @brief Oper command allow a user to become operator if valid credentials are provided.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	oper(Command &cmd) //what about multiple attempts?
{
	std::vector<std::string> params = cmd.getParams();
	User	*user = cmd.getUser();
	if (!user->isRegistered())
		user->pushReply(err_notregistered());

	else if (params.size() < 2)
		user->pushReply(err_needmoreparams(user->getNickname(), "OPER"));

	else if (!cmd.server->checkOpeCredentials(params[0], params[1]))
		user->pushReply(err_passwordmismatch());

	else
	{
		user->setOperator(true);
		user->pushReply(rpl_youreoper());
		user->pushReply(rpl_umodeis("+o"));
	}
}

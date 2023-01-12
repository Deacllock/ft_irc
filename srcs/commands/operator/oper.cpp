#include "commandHandlers.hpp"

/**
 * @brief Oper command allow a user to become operator if valid credentials are provided.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	oper(Command &cmd) //what about multiple attempts?
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	if (!usr->isRegistered())
		usr->pushReply(err_notregistered(usr->getNickname()));

	else if (params.size() < 2)
		usr->pushReply(err_needmoreparams(usr->getNickname(), "OPER"));

	else if (!cmd.server->checkOpeCredentials(params[0], params[1]))
		usr->pushReply(err_passwordmismatch(usr->getNickname()));

	else
	{
		usr->setOperator(true);
		usr->pushReply(rpl_youreoper(usr->getNickname()));
		usr->pushReply(rpl_umodeis(usr->getNickname(), "+o"));
	}
}

#include "commandHandlers.hpp"

/**
 * @brief Oper comman allow a user to become operator if valid credentials are provided.
 * 
 * @param cmd Command class containing parameters, user and connection state to use.
 */
void	oper(Command &cmd) //what about multiple attempts?
{
	std::vector<std::string> params = cmd.getParams();
	if (!cmd.getUser()->getIsRegistered())
		cmd.addOutput(err_notregistered());

	else if (params.size() < 2)
		cmd.addOutput(err_needmoreparams(cmd.getUser()->getNickname(), "OPER"));

	else if (!cmd.server->checkOpeCredentials(params[0], params[1]))
		cmd.addOutput(err_passwordmismatch());

	else
	{
		cmd.addOutput(rpl_youreoper());
		cmd.addOutput(rpl_umodeis("+o")); //is that really efficient? or shall I call MODE instead?
	}
}

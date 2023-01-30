#include "commandHandlers.hpp"

/**
 * @brief Parse params to get to know if we shall remove operator role to a user.
 * 
 * @param isOp Bool to set depending on input data.
 * @param params Input data.
 * @return bool	Returns if unknown flag has been given. 
 */
static bool	parseParams(bool &isOp, std::vector<std::string> params)
{
	int sign = 1;
	bool unknown = false;
	for (size_t i = 1; i < params.size(); i++)
	{
		for (size_t j = 0; params[i][j]; j++)
		{
			switch (params[i][j])
			{
				case '-':
					sign = -1;
					break;
				case '+':
					sign = 1;
					break;
				case 'o':
					if (sign == -1)
						isOp = false;
					break;
				default:
					unknown = true;
			}
		}
	}
	return unknown;
}

static void	infos_user(User *usr)
{
	std::string		mode = "";
	
	if (usr->isOperator())
		mode += "+o";

	usr->pushReply(":" + usr->server->getName() + " " + rpl_umodeis(usr->getNickname(), mode));
}


/**
 * @brief The user MODE's are typically changes which affect either how the client is seen by others
 * 
 * Parameters: <nickname> *( ( "+" / "-" ) *( "o" ) )
 * 
 * o - operator flag;
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	user_mode(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	bool	isOp = true;

	if ( params.size() < 1)
		usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname() != params[0])
		usr->pushReply(":" + cmd.server->getName() + " " + err_usersdontmatch(usr->getNickname()));
	
	else if (params.size() > 1)
	{
		if (parseParams(isOp, params))
			usr->pushReply(":" + cmd.server->getName() + " " + err_umodeunknownflag(usr->getNickname()));
		if (usr->isOperator() && !isOp)
		{
			usr->setOperator(isOp);
			usr->pushReply(":" + cmd.server->getName() + " " + rpl_umodeis(usr->getNickname(), "-o"));
		}
	}

	else 
		infos_user(usr);
}

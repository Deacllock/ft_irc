#include "commandHandlers.hpp"

static bool	parseParams(bool &isOP, std::vector<std::string> params)
{
	int sign = 1;
	int unknown = 0;
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
						mode &= ~(1UL << OPERATOR);
					break;
				default:
					unknown = 1;;
			}
		}
	}
	return unknown;
}

//Parameters: <nickname> *( ( "+" / "-" ) *( "o" ) )
void	user_mode(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	bool	isOp = false;

	if ( !usr->isRegistered() )
		return (usr->pushReply(err_notregistered()));

	if ( params.size() < 1)
		usr->pushReply(err_needmoreparams(cmd.getUser()->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		usr->pushReply(err_usersdontmatch());
	
	else if (params.size() > 1)
	{
		if (parseParams(isOp, params))
			usr->pushReply(err_umodeunknownflag());
		mode_str = modeToString(usr->getMode(), mode);
		if (mode_str != "")
			rpl_umodeis(mode_str);
	}
	else
		usr->pushReply(rpl_umodeis(modeToString('\0', cmd.getUser()->getMode())));
}
#include "commandHandlers.hpp"

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

//Parameters: <nickname> *( ( "+" / "-" ) *( "o" ) )
void	user_mode(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	bool	isOp = true;

	if ( !usr->isRegistered() )
		(usr->pushReply(err_notregistered(usr->getNickname())));

	else if ( params.size() < 1)
		usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		usr->pushReply(err_usersdontmatch(usr->getNickname()));
	
	else if (params.size() > 1)
	{
		if (parseParams(isOp, params))
			usr->pushReply(err_umodeunknownflag(usr->getNickname()));
		if (usr->isOperator() && !isOp)
			rpl_umodeis(usr->getNickname(), "-o");
	}

	else if (usr->isOperator())
		usr->pushReply(rpl_umodeis(usr->getNickname(), "o"));
}
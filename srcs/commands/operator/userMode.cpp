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

static std::string diff(bool prev, bool cur)
{
	std::string ret = "";
	if (pre
}
//Parameters: <nickname> *( ( "+" / "-" ) *( "o" ) )
void	user_mode(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	bool	isOp = true;

	if ( !usr->isRegistered() )
		return (usr->pushReply(err_notregistered(usr->getNickname())));

	else if ( params.size() < 1)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		return usr->pushReply(err_usersdontmatch(usr->getNickname()));
	
	else if (params.size() > 1)
	{
		if (parseParams(isOp, params))
			usr->pushReply(err_umodeunknownflag(usr->getNickname()));
		
		// if (mode_str != "")
			// rpl_umodeis(usr->getNickname(), mode_str);
	}

	if ( usr->isOperator() && isOp )
	else
	{
		if (isOp)
			usr->pushReply(rpl_umodeis(usr->getNickname(), ));
		
	}
}
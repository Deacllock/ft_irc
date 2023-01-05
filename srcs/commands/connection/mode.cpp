#include "commandHandlers.hpp"

/**
 * @brief Convert bit set mode char into readable string.
 * 
 * @param mode Mode to convert.
 * @return std::string Converted mode.
 */
std::string	modeToString(char mode)
{
	std::string ret = "";

	if (mode != 0)
		ret += '+';
	if (mode | AWAY)
		ret+= 'a';
	if (mode | INVISIBLE)
		ret += 'i';
	if (mode | WALLOPS)
		ret += 'w';
	if (mode | RESTRICTED)
		ret += 'r';
	if (mode | OPERATOR)
		ret += 'O';
	if (mode | LOCAL_OPERATOR)
		ret += 'o';
	if (mode | NOTICE)
		ret += 'n';
	return ret;
}

int	parseParams(char &mode, std::vector<std::string> params)
{
	
}

//Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
//no +a
//no +O nor +o
//no -r
void	user_mode(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*use = cmd.getUser();
	std::string	mode_str;
	char		mode;

	if ( params.size() < 1)
		usr->pushReply(err_needmoreparams(cmd.getUser()->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		usr->pushReply(err_usersdontmatch());
	
	else if (params.size() > 1)
	{
		if (parseParams(&mode, params))
			usr->pushReply(err_umodeunknownflag());
		else
			rpl_umodeis(mode_str);
	}
	else
		usr->pushReply(rpl_umodeis(modeToString(cmd.getUser()->getMode())));
}
#include "commandHandlers.hpp"

/**
 * @brief Check if option is present either in prev mode or current mode.
 * 
 * @param prev Previous mode.
 * @param cur Current mode.
 * @param opt Option to test (bit).
 * @return int Returns -1 if loosing option, 1 if adding, 0 when nothing happenend.
 */
static int	diff(char prev, char cur, int opt)
{
	if (prev | opt && !(cur | opt))
		return -1;
	if (cur | opt && !(prev | opt))
		return 1;
	return 0;
}

/**
 * @brief Convert bit set mode char into readable string.
 * 
 * @param mode Mode to convert.
 * @return std::string Converted mode.
 */
static std::string	modeToString(char prevMode, char mode)
{
	std::string ret_minus = "";
	std::string ret_plus = "";

	char optCharList[] = { 'a', 'i', 'w', 'r', 'o', 'n' };

	for (int i = 0; i < 6; i++)
	{
		int ret = diff(prevMode, mode, 1 << i); //check
		if (ret == 1)
			ret_plus += optCharList[i];
		else if (ret == -1)
			ret_minus += optCharList[i];
	}
	if (ret_minus != "")
		ret_minus = "-" + ret_minus + " ";
	if (ret_plus != "")
		ret_plus = "+" + ret_plus;
	return ret_minus + ret_plus;
}

int	parseParams(char &mode, std::vector<std::string> params)
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
				case 'a':
					break;
				default:
					unknown = 1;;
			}
		}
	}
	return unknown;
}

//Parameters: <nickname> *( ( "+" / "-" ) *( "i" / "w" / "o" / "r" ) )
void	user_mode(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();
	std::string	mode_str;
	char		mode;

	if ( !usr->getIsRegistered() )
		return (usr->pushReply(err_notregistered()));

	if ( params.size() < 1)
		usr->pushReply(err_needmoreparams(cmd.getUser()->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		usr->pushReply(err_usersdontmatch());
	
	else if (params.size() > 1)
	{
		if (parseParams(mode, params))
			usr->pushReply(err_umodeunknownflag());
		mode_str = modeToString(usr->getMode(), mode);
		if (mode_str != "")
			rpl_umodeis(mode_str);
	}
	else
		usr->pushReply(rpl_umodeis(modeToString('\0', cmd.getUser()->getMode())));
}

void	mode(Command &cmd)
{
	user_mode(cmd);
}
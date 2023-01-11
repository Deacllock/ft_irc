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
	User	*usr = cmd.getUser();
	std::string	mode_str;
	char		mode;

	if ( !usr->isRegistered() )
		return (usr->pushReply(err_notregistered(usr->getNickname())));

	if ( params.size() < 1)
		usr->pushReply(err_needmoreparams(cmd.getUser()->getNickname(), "MODE"));

    else if (cmd.getUser()->getNickname().compare(params[0]))
		usr->pushReply(err_usersdontmatch(usr->getNickname()));
	
	else if (params.size() > 1)
	{
		if (parseParams(mode, params))
			usr->pushReply(err_umodeunknownflag(usr->getNickname()));
		mode_str = modeToString(usr->getMode(), mode);
		if (mode_str != "")
			rpl_umodeis(mode_str);
	}
	else
		usr->pushReply(rpl_umodeis(usr->getNickname(), modeToString('\0', cmd.getUser()->getMode())));
}

static  void	operatorModeInChan(User *usr, std::vector<std::string> params, char sym, size_t i)
{
}

static  void	setLimitInchan(User *usr, std::vector<std::string> params, char sym, size_t i)
{
}

static  void	setInviteOnlyForChan(User *usr, std::vector<std::string> params, char sym, size_t i)
{
}

static  void	setKeyForChan(User *usr, std::vector<std::string> params, char sym, size_t i)
{
}

// ERR_NOCHANMODES channel doesn't support modes ??
// ERR_USERNOTINCHANNEL
// ERR_KEYSET

// RPL_CHANNELMODEIS
// RPL_BANLIST RPL_ENDOFBANLIST
// RPL_EXCEPTLIST RPL_ENDOFEXCEPTLIST
// RPL_INVITELIST RPL_ENDOFINVITELIST
// RPL_UNIQOPIS

void	channel_mode(Command &cmd)
{
	User	*usr = cmd.getUser();
	std::vector<std::string> params = cmd.getParams();
	char	sym = params[1][0];

	if (!usr->isOnChan(params[0]))
		return usr->pushReply(err_usernotinchannel(usr->getNickname(), params[0]));
	
	if (!usr->getIsOperator())
		return usr->pushReply(err_chanoprivsneeded(usr->getNickname(), params[0]));

	for (size_t i = 1; i < params[1].size(); i++)
	{
		switch (params[1][i])
		{
			case 'o': // make someone op in chan - or supp op
				operatorModeInChan(usr, params, sym, i);
				break;
			case 'l': // set limit for chan
				setLimitInChan(usr, params, sym, i);
				break;
			case 'i': // set inviteonly chan
				setInviteOnlyForChan(usr, params, sym, i);
				break;
			case 'k': // set key for chan
				setKeyForChan(usr, params, sym, i);
				break;
			default:
				usr->pushReply(err_unknownmode(usr->getNickname(), params[1][i], params[0]));
		}
	}
}

void	mode(Command &cmd) // See how to organize this part
{
	User	*usr = cmd.getUser();

	if (cmd.getParams() < 2)
		return usr->pushReply(err_needmoreparams(usr->getNickname(), "MODE"));

	if (Command::server->isExistingUserByName())
		user_mode(cmd);
	else if (Command::server->isExistingChannelByName())
		channel_mode(cmd);
	// else
}

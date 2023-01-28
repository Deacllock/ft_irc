#include "Command.hpp"

static bool areSpaces( std::string msg, size_t &i )
{
	bool ret = false;
	if ( msg[i] == ' ')
		ret = true;
	while ( msg [i] == ' ')
		i++;
	return ret;
}

static int	isCrlf( std::string msg, size_t &i )
{
	if (msg[i++] == '\r' && msg[i++] == '\n')
		return true;
	return INCOMPLETE;
}

static bool nospcrlfcl( char c )
{
	return c != '\0' && c != '\r' && c != '\n' && c != ' ' && c != ':' ;
}

static bool isMiddle( std::string msg, size_t &i )
{
	if (!nospcrlfcl(msg[i]))
		return (false);
	i++;
	while (nospcrlfcl(msg[i]) || msg[i] == ':') //: not usefull?
		i++;
	return (true);
}

static bool isTrailing( std::string msg, size_t &i )
{
	while (msg[i] == ':' || msg[i] == ' ' || nospcrlfcl(msg[i]))
		i++;
	return true;
}

static bool areParamValids( std::string msg, size_t &i )
{
	size_t j = 1;
	while (isMiddle(msg, i) && areSpaces(msg, i))
		j++;
	if (j > 14)
		return false;
	
	if (msg[i] == ':')
		i++;
	return (isTrailing(msg, i));
}

static bool isCommandValid( std::string msg, size_t &i )
{
	
	if (isalpha(msg[i]))
	{
		while (isalpha(msg[i]))
			i++;
		return true;
	}
	return false;
}

/**
 * @brief Check if the message has a good parsing.
 *
 *	For all the function called in here, check rfc-editor.org/rfc/rfc2812 2.3.1
 *
 * @param msg The extracted message.
 * @return bool
 */
int	isMessageValid( std::string msg, size_t &i )
{
	
	if (!isCommandValid(msg, i))
		return isCrlf(msg, i);

	if (!areSpaces(msg, i))
		return isCrlf(msg, i);

	if (!areParamValids(msg, i))
		return false;

	areSpaces(msg, i);
	return isCrlf(msg, i);
}
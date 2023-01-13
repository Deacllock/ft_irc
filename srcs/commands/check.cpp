#include <string>

static bool areSpaces( std::string msg, size_t &i )
{
	bool ret = false;
	if ( msg.at(i) == ' ')
		ret = true;
	while ( msg [i] == ' ')
		i++;
	return ret;
}

static bool	isCrlf( std::string msg, size_t &i )
{
	return (msg[i++] == '\r' && msg[i++] == '\n');
}

static bool nospcrlfcl( char c )
{
	return c != '\0' && c != '\r' && c != '\n' && c != ' ' && c != ':' ;
}

static bool isMiddle( std::string msg, size_t &i )
{
	if (!nospcrlfcl(msg.at(i)))
		return (false);
	i++;
	while (nospcrlfcl(msg.at(i)) || msg.at(i) == ':') //: not usefull?
		i++;
	return (true);
}

static bool isTrailing( std::string msg, size_t &i )
{
	while (msg.at(i) == ':' || msg.at(i) == ' ' || nospcrlfcl(msg.at(i)))
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
	
	if (msg.at(i) == ':')
		i++;
	return (isTrailing(msg, i));
}

static bool isCommandValid( std::string msg, size_t &i )
{
	// if (isdigit(msg.at(i)))
	// {
	// 	i++;
	// 	return isdigit(msg.at(i++)) && isdigit(msg.at(i++));
	// }
	
	if (isalpha(msg.at(i++)))
	{
		while (isalpha(msg.at(i)))
			i++;
		return true;
	}
	return false;
}

// bool	is_servername(std::string msg, size_t *i)
// {
// 	size_t	j = 1;
	
// 	if (!isalpha(msg.at(*i)) && !isdigit(msg.at(*i)))
// 		return false;

// 	for (; msg.at(*i + j) != '.' && msg.at(*i + j) != ' '; j++)
// 		if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)) && msg.at(*i + j) != '-')
// 			return false;

// 	if (msg.at(*i + j - 1) == '-')
// 		return false;
	
// 	while (msg.at(*i + j) != ' ')
// 	{
// 		if (msg.at(*i + j) != '.')
// 			return false;

// 		j++;
// 		if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)))
// 			return false;

// 		j++;
// 		for (; msg.at(*i + j) != '.' && msg.at(*i + j) != ' '; j++)
// 			if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)) && msg.at(*i + j) != '-')
// 				return false;

// 		if (msg.at(*i + j - 1) == '-')
// 			return false;
// 	}
// 	*i += j;

// 	return true;
// }

// bool	is_other_prefix(std::string msg, size_t *i)
// {
// 	//size_t	j = 0;
// 	(void) msg;
// 	(void) i;
// 	return true;
// }


// static bool isPrefixValid( std::string msg, size_t &i)
// {
// 	return (isServerName(msg, i) || isNickname(msg, i));
// }

//what about space managment
/**
 * @brief Check if the message has a good parsing.
 *
 *	For all the function called in here, check rfc-editor.org/rfc/rfc2812 2.3.1
 *
 * @param msg The extracted message.
 * @return bool
 */
bool	isMessageValid( std::string msg, size_t &i )
{
	// if (msg.at(i) == ':')
	// 	if (isPrefixValid(msg, ++i) && !areSpaces(msg, i))
	// 		return false;
	
	if (!isCommandValid(msg, i))
		return false;

	if (!areSpaces(msg, i))
		return (isCrlf(msg, i));

	if (!areParamValids(msg, i))
		return false;

	areSpaces(msg, i);
	return (isCrlf(msg, i));
}
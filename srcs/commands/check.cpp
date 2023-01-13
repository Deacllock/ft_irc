// #include <cctype>
// #include <string>
// #include <iostream>

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

// bool	has_prefix(std::string msg, size_t *i)
// {
// 	// servername | (nickname [["!" user]"@"host])
// 	if (is_servername(msg, i) || is_other_prefix(msg, i))
// 		return true;

// 	return false;
// }


// bool	is_good_command(std::string msg, size_t *i)
// {
// 	if (isdigit(msg[*i]))
// 	{
// 		if (isdigit(msg[*i + 1]) && isdigit(msg[*i + 2]) && msg[*i + 3] == ' ')
// 		{
// 			*i += 4;
// 			return true;
// 		}
// 		else
// 			return false;
// 	}
// 	size_t j = 0;
// 	for (; msg[*i + j] != ' ' && msg[*i + j] != '\r'; j++)
// 		if (!isalpha(msg[*i + j]))
// 			return false;
// 	*i += j;
	
// 	return true;
// }


// bool	nospcrlfcl(char c)
// {
// 	if (c == 0 || c == '\r' || c == '\n' || c == ' ' || c == ':')
// 		return false;
// 	return true;
// }

// bool	is_trailing(std::string msg, size_t *i)
// {
// 	for (; msg[*i] && msg.at(*i) != '\r'; (*i)++)
// 		if (msg.at(*i) != ':' && msg.at(*i) != ' ' && !nospcrlfcl(msg.at(*i)))
// 			return false;

// 	return true;
// }

// bool	is_space_middle(std::string msg, size_t *i)
// {
// 	size_t j = 0;

// 	if (msg.at(j) != ' ')
// 		return false;
// 	j++;
// 	if (!nospcrlfcl(msg.at(j)))
// 		return false;
// 	j++;
// 	size_t k = 0;
// 	for (; msg[j] && (msg.at(j + 1) == ':' || is_trailing(msg.substr(j + 1), &k)); j++)
// 		if (!nospcrlfcl(msg.at(j)) && msg.at(j) != ':')
// 			return false;
// 	*i += j + 1;
// 	return true;
// }

// bool	has_good_params(std::string msg, size_t *i)
// {
// 	if (msg.at(*i) == '\r' && msg.at(*i + 1) != '\n')
// 		return true;

// 	size_t nb_space_middle = 0;
// 	size_t j = 0;
// 	for (; 1; nb_space_middle++, j++)
// 		if (!is_space_middle(msg.substr(*i + j), &j))
// 			break;
// 	*i += j;

// 	if (nb_space_middle > 14)
// 		return false;
// 	if (msg.at(*i) != ' ')
// 		return false;
// 	(*i)++;
// 	if (nb_space_middle < 14 && msg.at(*i) != ':')
// 		return false;
// 	if (msg.at(*i) == ':')
// 		(*i)++;
// 	if (!is_trailing(msg, i))
// 		return false;

// 	return true;
// }

// /**
//  * @brief Check if the message has a good parsing.
//  *
//  *	For all the function called in here, check rfc-editor.org/rfc/rfc2812 2.3.1
//  *
//  * @param msg The extracted message.
//  * @return bool
//  */
// bool	is_good_message(std::string msg)
// {
// 	size_t i = 0;
// 	if (msg.at(i) == ':')
// 	{
// 		i++;
// 		if (!has_prefix(msg, &i) || msg.at(i) != ' ')
// 			return false;
// 		i++;
// 	}
// 	if (!is_good_command(msg, &i))
// 		return false;
// 	if (!has_good_params(msg, &i))
// 		return false;
// 	if (msg.at(i) != '\r')
// 		return false;
// 	if (msg.at(i + 1) != '\n')
// 		return false;
// 	return true;
// }

#include <string>

static bool areSpaces( std::string msg, size_t &i )
{
	bool ret = false;
	if ( msg[i] == ' ')
		ret = true;
	while ( msg [i] == ' ')
		i++;
	return ret;
}

static bool	isCrlf( std::string msg, size_t &i )
{
	return (msg[i++] == '\r' && msg[i++] == '\n');
}

static bool nospcrlfcl( std::string msg, size_t &i )
{
	return msg[i] != '\0' && msg[i] != '\r' && msg[i] != '\n' && msg[i] != ' ' && msg[i] != ':' ;
}

static bool isMiddle( std::string msg, size_t &i )
{
	if (!nospcrlfcl(msg, i))
		return (false);
	i++;
	while (nospcrlfcl(msg, i) || msg[i] == ':')
		i++;
	return (true);
}

static bool isTrailing( std::string msg, size_t &i )
{
	while (msg[i] == ':' || msg[i] == ' ' || nospcrlfcl(msg, i))
		i++;
	return true;
}

static bool areParamValids( std::string msg, size_t &i )
{
	if (isMiddle(msg, i))
	{
		size_t j = 1;
		while (areSpaces(msg, i) && isMiddle(msg, i))
			j++;
		if (j >= 14)
			return false; 
	}
	areSpaces(msg, i);
	if (msg[i] == ':')
		i++;
	return isTrailing(msg, i);
}

static bool isCommandValid( std::string msg, size_t &i )
{
	// if (isdigit(msg[i]))
	// 	return isdigit(msg[++i]) && isdigit(msg[++i]);
	
	if (isalpha(msg[i]))
	{
		while (isalpha(msg[++i]));
		return true;
	}
	return false;
}

//check space management
bool	isMessageValid( std::string msg, size_t &i )
{
	// if (msg.size() && at(i++) == ':')
	// 	if (!isPrefixValid(msg, &i) || !areSpaces(msg, &i))
	// 		return false;
	areSpaces(msg, i);

	if (!isCommandValid(msg, i))
		return false;

	if (!areSpaces(msg, i))
		return (isCrlf(msg, i));

	if (!areParamValids(msg, i))
		return false;

	areSpaces(msg, i);
	return (isCrlf(msg, i));
}
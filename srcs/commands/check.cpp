#include <cctype>

bool	has_prefix(std::string msg, size_t *i)
{
	return true;
}

bool	is_good_command(std::string msg, int *i)
{
	if (isdigit(msg[0]))
	{
		if (isdigit(msg[1]) && isdigit(msg[2]) && msg[3] == ' ')
		{
			*i += 4;
			return true;
		}
		else
			return false;
	}

	int j = 0;
	for (; msg[j] != ' ' || msg[j] != '\r'; j++)
		if (!isalpha(msg[j]))
			return false;
	*i += j;
	
	return true;
}

bool	nospcrlfcl(char c)
{
	if (c == NULL || c == '\r' || c == '\n' || c == ' ' || c == ':')
		return false;
	return true;
}

bool	is_space_middle(std::string msg, int *i)
{
	int j = 0;
	if (msg.at(j) != ' ')
		return false;
	j++;
	if (!nospcrlfcl(msg.at(j)))
		return false;
	j++;
	for (; 1; j++)
		if (!nospcrlfcl(msg.at(j)) && msg.at(j) != ':')
			return false;
	*i += j;
	return true;
}

bool	has_good_params(std::string msg, int *i)
{
	if (msg.at(i) == "\r" && msg.at(i + 1) != "\n")
		return true;

	int nb_space_middle = 0;
	for (; 1; nb_space_middle++)
		if (!is_space_middle(msg.substr(*i), i))
			break;
	
	if (nb_space_middle > 14)
		return false;
	if (msg.at(*i) != ' ')
		return false;
	*i++;
	if (nb_space_middle < 14 && msg.at(*i) != ':')
		return false;
	if (msg.at(*i) == ':')
		*i++;
	for (; 1; *i++)
		if (msg.at(*i) != ':' && msg.at(*i) != ' ' && !nospcrlfcl(msg.at(*i)))
			return false;

	return true;
}

/**
 * @brief Check if the message has a good parsing.
 *
 *	For all the function called in here, check rfc-editor.org/rfc/rfc2812 2.3.1
 *
 * @param msg The extracted message.
 * @return bool
 */
bool	is_good_message(std::string msg)
{
	size_t i = 0;
	if (msg.at(i) == ':')
	{
		if (!has_prefix(msg.substr(1), &i) || msg.at(i) != " ")
			return false;
		i++;
	}
	if (!is_good_command(msg.substr(i), &i))
		return false;
	if (!has_good_params(msg.substr(i), &i))
		return false;
	if (msg.at(i) != "\r" || msg.at(i + 1) != "\n")
		return false;
	return true;
}

#include <cctype>

bool	has_prefix(std::string msg, size_t *i)
{
	return true;
}

bool	is_good_command(std::string msg, int *i)
{
	if (isdigit(msg[0]))
		if (isdigit(msg[1]) && isdigit(msg[2]) && msg[3] == ' ')
		{
			*i += 4;
			return true;
		}
		else
			return false;
	int j = 0;
	for (; msg[j] != ' '; j++)
		if (!isalpha(msg[j]))
			return false;
	*i += j;
	
	return true;
}

bool	has_good_params(std::string msg, int *i)
{
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

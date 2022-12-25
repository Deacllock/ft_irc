#include <cctype>
#include <string>
#include <iostream>

bool	is_servername(std::string msg, int *i)
{
	int	j = 1;
	
	if (!isalpha(msg.at(*i)) && !isdigit(msg.at(*i)))
		return false;

	for (; msg.at(*i + j) != '.' && msg.at(*i + j) != ' '; j++)
		if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)) && msg.at(*i + j) != '-')
			return false;

	if (msg.at(*i + j - 1) == '-')
		return false;
	
	while (msg.at(*i + j) != ' ')
	{
		if (msg.at(*i + j) != '.')
			return false;

		j++;
		if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)))
			return false;

		j++;
		for (; msg.at(*i + j) != '.' && msg.at(*i + j) != ' '; j++)
			if (!isalpha(msg.at(*i + j)) && !isdigit(msg.at(*i + j)) && msg.at(*i + j) != '-')
				return false;

		if (msg.at(*i + j - 1) == '-')
			return false;
	}
	*i += j;

	return true;
}

bool	is_other_prefix(msg, i)
{
	//int	j = 0;
	(void) msg;
	(void) i;
	return true;
}

bool	has_prefix(std::string msg, int *i)
{
	// servername | (nickname [["!" user]"@"host])
	if (is_servername(msg, i) || is_other_prefix(msg, i))
		return true;

	return false;
}

bool	is_good_command(std::string msg, int *i)
{
	if (isdigit(msg[*i]))
	{
		if (isdigit(msg[*i + 1]) && isdigit(msg[*i + 2]) && msg[*i + 3] == ' ')
		{
			*i += 4;
			return true;
		}
		else
			return false;
	}

	int j = 0;
	for (; msg[*i + j] != ' ' && msg[*i + j] != '\r'; j++)
		if (!isalpha(msg[*i + j]))
			return false;
	*i += j;
	
	return true;
}

bool	nospcrlfcl(char c)
{
	if (c == 0 || c == '\r' || c == '\n' || c == ' ' || c == ':')
		return false;
	return true;
}

bool	is_trailing(std::string msg, int *i)
{
	for (; msg[*i] && msg.at(*i) != '\r'; (*i)++)
		if (msg.at(*i) != ':' && msg.at(*i) != ' ' && !nospcrlfcl(msg.at(*i)))
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
	int k = 0;
	for (; msg[j] && (msg.at(j + 1) == ':' || is_trailing(msg.substr(j + 1), &k)); j++)
		if (!nospcrlfcl(msg.at(j)) && msg.at(j) != ':')
			return false;
	*i += j + 1;
	return true;
}

bool	has_good_params(std::string msg, int *i)
{
	if (msg.at(*i) == '\r' && msg.at(*i + 1) != '\n')
		return true;

	int nb_space_middle = 0;
	int j = 0;
	for (; 1; nb_space_middle++, j++)
		if (!is_space_middle(msg.substr(*i + j), &j))
			break;
	*i += j;

	if (nb_space_middle > 14)
		return false;
	if (msg.at(*i) != ' ')
		return false;
	(*i)++;
	if (nb_space_middle < 14 && msg.at(*i) != ':')
		return false;
	if (msg.at(*i) == ':')
		(*i)++;
	if (!is_trailing(msg, i))
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
	int i = 0;
	if (msg.at(i) == ':')
	{
		i++;
		if (!has_prefix(msg, &i) || msg.at(i) != ' ')
			return false;
		i++;
	}
	if (!is_good_command(msg, &i))
		return false;
	if (!has_good_params(msg, &i))
		return false;
	if (msg.at(i) != '\r')
		return false;
	if (msg.at(i + 1) != '\n')
		return false;
	return true;
}

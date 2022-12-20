bool	has_prefix(std::string msg, size_t *i)
{
	return true;
}

bool	is_good_command(std::string msg, int *i)
{
	return true;
}

bool	has_good_params(std::string msg, int *i)
{
	return true;
}

/**
 * @brief Check if the message has a good parsing.
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

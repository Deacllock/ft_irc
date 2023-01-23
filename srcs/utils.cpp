#include "sstream"
#include "utils.hpp"

/**
 * @brief splitByComma splits a string with ',' delimiter.
 * 
 * @param input String to parse.
 * @return std::vector<std::string> Vector containing splitted string elements.
 */
std::vector<std::string>	splitByComma(std::string str)
{
	std::vector<std::string> vec;

	std::string elem;
	std::istringstream ss(str);
	while (getline(ss, elem, ','))
		vec.push_back(elem);
	
	return vec;
}


std::string		intToString(int nb)
{
	std::stringstream	ss;

	ss << nb;

	return ss.str();
}

unsigned long	stringToULong(std::string str)
{
	std::stringstream	ss;
	unsigned long		nb;

	ss << str;
	ss >> nb;
	
	return nb;
}

std::string	charToString(char c) { std::string str(1, c); return str; }

static bool	isChanstring(char c)
{
	if (c == 0 || c == '\a' || c == '\r' || c == '\n' || c == ' ' || c == ',' || c == ':')
		return false;
	return true;
}

bool	checkChannelName(std::string name)
{
	int	i = 1;
	if (name[0] != '#' && name[0] != '+' && name[0] != '&' && name[0] != '!')
		return false;
	if (name[0] == '!')
	{
		if (name[i] != '5')
			return false;
 		i++;
 		if (!isupper(name[i]) && !isdigit(name[i]))
 			return false;
 		i++;
	}
	if (!isChanstring(name[i]))
		return false;
	i++;
	if (name[i] == ':')
		if (!isChanstring(name[i + 1]))
			return false;
	return true;
}

void    sendAll( std::vector<User *> users, User *avoid, std::string msg )
{
	for (std::vector<User *>::iterator it = users.begin();
		it != users.end(); it++)
	{
		if (!avoid || (*it) != avoid)
			if (!(*it)->isDisconnected())
				(*it)->pushReply(msg);
	}
}
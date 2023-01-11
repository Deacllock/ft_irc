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


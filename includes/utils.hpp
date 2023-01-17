#ifndef UTILS
# define UTILS

#include <string>
#include <vector>
#include <User.hpp>

std::vector<std::string>	splitByComma(std::string str);

std::string					intToString(int nb);

unsigned long				stringToULong(std::string str);

std::string					charToString(char c);

bool						checkChannelName(std::string name);

template <class T>
void addElmToVector( std::vector<T *> &vect, T *u )
{
	if (std::find(vect.begin(), vect.end(), u) == vect.end())
		vect.push_back(u);
}

template <class T>
void removeElmFromVector( std::vector<T *> &vect, T *u )
{
	typename std::vector<T *>::iterator it = std::find(vect.begin(), vect.end(), u);

	if (it != vect.end())
		vect.erase(it);
}

void    sendAll( std::vector<User *> users, User *avoid, std::string msg );

#endif

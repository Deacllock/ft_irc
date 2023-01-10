#ifndef UTILS
# define UTILS

#include <string>
#include <vector>

std::vector<std::string>	splitByComma(std::string str);

template <class T>
void addElmToVector( std::vector<T *> vect, T *u )
{
	if (std::find(vect.begin(), vect.end(), u) == vect.end())
		vect.push_back(u);
}

template <class T>
void removeElmFromVector( std::vector<T *> vect, T *u )
{
	typename std::vector<T *>::iterator it = std::find(vect.begin(), vect.end(), u);

	if (it != vect.end())
		vect.erase(it);
}

#endif
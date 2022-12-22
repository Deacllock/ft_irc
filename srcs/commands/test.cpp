#include <iostream>
bool	is_good_message(std::string msg);

int main()
{
	std::cout << std::boolalpha;
	std::cout << is_good_message("test") << std::endl; //false
	std::cout << is_good_message("JOIN help : :\r\n") << std::endl; //true
}

# include "commands/Command.hpp"

int main(void)
{
	std::string s = "JOIN this test channel";
	std::string s2 = "     JOIN        this test channel    ";
	Command c(s);
	Command c1(s2);
	return 0;
}

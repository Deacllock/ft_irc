#include "NumericReplies.hpp"
#include "commandHandlers.hpp"

void	pass(Command &cmd)
{
	// if (params.size() < 1)
	// 	return ERR_NEEDMOREPARAMS(cmd.getUser().getUsername(), "PASS");
	// if (params[0] != server->getPassword) //compare hashes?
	// 	return ERR_PASSWDMISMATCH(user->getUsername());
	// if (user->getIsConnected())
	// 	return ERR_ALREADYREGISTERED(user->getUsername());
	// user->setIsConnected();
	// return "";
	(void)cmd;
}

//check order
//check ERROR message
//ignore when too many params?
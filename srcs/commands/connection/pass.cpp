#include "commandHandlers.hpp"

void	pass(Command &cmd)
{
	const char	*username = cmd.getUser()->getUsername().c_str();
	if (cmd.getParams().size() < 1)
		cmd.setOutput(ERR_NEEDMOREPARAMS(username, "PASS"));
	// else if (!Command::_server->checkPassword(cmd.getParams()[0]))
	// 	cmd.setOutput(ERR_PASSWDMISMATCH(cmd.getUser()->getUsername().c_str()));
	// else if (cmd.getUser()->getIsConnected())
	// 	cmd.setOutput(ERR_ALREADYREGISTERED(cmd.getUser()->getUsername().c_str()));
	// else
	// 	 cmd.getUser()->setIsConnected();
}

//check order
//check ERROR message
//ignore when too many params?
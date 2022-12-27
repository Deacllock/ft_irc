#include "commandHandlers.hpp"

void	pass(Command &cmd)
{
	if (cmd.getParams().size() < 1)
		cmd.setOutput(ERR_NEEDMOREPARAMS(cmd.getUser().getUsername(), "PASS"));
	else if (!Command::_server->checkPassword(cmd.getParams()[0]))
		cmd.setOutput(ERR_PASSWDMISMATCH(cmd.getUser()->getUsername()));
	else if (cmd.getUser()->getIsConnected())
		cmd.setOutput(ERR_ALREADYREGISTERED(cmd.getUser()->getUsername()));
	else
		 cmd.getUser()->setIsConnected();
}

//check order
//check ERROR message
//ignore when too many params?
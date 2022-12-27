#include "NumericReplies.hpp"
#include "commandHandlers.hpp"

void	pass(Command &cmd)
{
	if (cmd->getParams().size() < 1)
		cmd->setOutput(ERR_NEEDMOREPARAMS(cmd.getUser().getUsername(), "PASS"));
	if (pcmd->getParams()[0] != Command::_server->getPassword()) //compare hashes?
		cmd->setOutput(ERR_PASSWDMISMATCH(user->getUsername()));
	if (user->getIsConnected())
		cmd->setOutput(ERR_ALREADYREGISTERED(user->getUsername()));
	user->setIsConnected();
	cmd->setOutput("");
}

//check order
//check ERROR message
//ignore when too many params?
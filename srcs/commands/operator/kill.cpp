#include "commandHandlers.hpp"

/**
 * @brief  The KILL command is used to cause a client-server connection to be closed by the server.
 * 
 * @param cmd Command class containing parameters, usr and connection state to use.
 */
void	kill(Command &cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();

	if (!usr->isOperator())
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noprivileges(usr->getNickname()));
	
	if (params.size() < 2)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "KILL"));
	
	if (params[0].compare(cmd.server->getName()) == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_cantkillserver(usr->getNickname()));
	
	User *toKill = cmd.server->getUserByName(params[0]);
	if (toKill == NULL)
		usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchnick(usr->getNickname(), params[0]));
	toKill->setStatus(DISCONNECTED);

	//send message?
}
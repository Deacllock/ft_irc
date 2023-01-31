#include "commandHandlers.hpp"

/**
 * @brief  The KILL command is used to cause a client-server connection to be closed by the server.
 * 
 * Parameters: <nickname> <comment>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	kill(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User	*usr = cmd.getUser();

	if (!usr->isOperator())
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noprivileges(usr->getNickname()));
	
	if (params.size() < 2 || params[0] == "" || params[1] == "")
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "KILL"));
	
	if (params[0] == cmd.server->getName())
		return usr->pushReply(":" + cmd.server->getName() + " " + err_cantkillserver(usr->getNickname()));
	
	User *toKill = cmd.server->getUserByName(params[0]);
	if (toKill == NULL)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nosuchnick(usr->getNickname(), params[0]));
	
	toKill->setStatus(DISCONNECTED);

	std::string reason = " :" + params[1];

	toKill->pushReply(":" + usr->getFullName() + " KILL " + toKill->getNickname());
	toKill->pushReply(":" + cmd.server->getName() + " " + error("Closing Link: " + cmd.server->getName() + " Killed " + usr->getFullName() + reason));
	
	std::string msg = ":" + toKill->getFullName() + " QUIT Killed " + usr->getFullName() + reason;

	toKill->sendAllChannels(msg);
	if (!usr->getReplies().size() || usr->getReplies().back() != (msg + "\r\n"))
		usr->pushReply(msg);
}

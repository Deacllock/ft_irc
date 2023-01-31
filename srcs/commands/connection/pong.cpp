#include "commandHandlers.hpp"

/**
 * @brief PONG message is a reply to ping message.
 * 
 * Parameters: <server>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	pong(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noorigin(usr->getNickname()));

	if (params[0] == cmd.server->getPingValue())
		usr->subPing();
}
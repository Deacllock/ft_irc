#include "commandHandlers.hpp"

/**
 * @brief The PING command is used to test the presence of an active client or server at the other end of the connection.
 * 
 * Parameters: <server1>
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	ping(Command cmd)
{
	std::vector<std::string> params = cmd.getParams();
	User *usr = cmd.getUser();

	if (params.size() == 0)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_noorigin(usr->getNickname()));

	usr->pushReply("PONG " + params[0]);
}
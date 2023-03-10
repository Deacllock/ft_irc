#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief Check if c is a special char.
 * 
 * special =  %x5B-60 / %x7B-7D; "[", "]", "\", "`", "_", "^", "{", "|", "}"
 * 
 * @param c Character to check
 * @return bool true if c is special, false otherwise
 */
static bool isspecial(int c) { return (c == '[' || c == ']' || c == '\\' || c == '`' || c == '_' || c == '^' || c == '{' || c == '}' || c == '|'); }

/**
 * @brief Check if Nickname matches the appropriate BNF.
 * 
 * nickname   =  ( letter / special ) *8( letter / digit / special / "-" )
 * letter     =  %x41-5A / %x61-7A       ; A-Z / a-z
 * digit      =  %x30-39                 ; 0-9
 * special    =  %x5B-60 / %x7B-7D; "[", "]", "\", "`", "_", "^", "{", "|", "}"
 * 
 * @param nick Nickname to check.
 * @return bool true if nickname is valid, false otherwise.
 */
static bool isNicknameValid( std::string nick )
{
	if (nick.length() == 0 || nick.length() > 9)
		return false;
	if (!isspecial(nick[0]) && !isalpha(nick[0]))
		return false;
	for (size_t i = 1; i < nick.length(); i++)
		if (!isalnum(nick[i]) && !isspecial(nick[i]) && nick[i] != '-')
			return false;
	return true;
}

/**
 * @brief Check if username is already in use.
 * 
 * @param users User list to search for nickname.
 * @param usr User to avoid.
 * @param nickname Nickname to search.
 * @return true if found, false otherwise
 */
static bool isNicknameInUse( std::vector<User *> users, User *usr, std::string nickname)
{
	for (size_t i = 0; i < users.size(); i++)
		if (users[i] != usr && users[i]->getNickname() == nickname)
			return true;
	return false;
}

/**
 * @brief NICK command is used to give user a nickname or change the existing one.
 * 
 * Parameters: <nickname>
 * 
 * @param cmd Contains command, parameters, user and server infos. */

void	nick(Command cmd)
{
	User *usr = cmd.getUser();
	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_nonicknamegiven(usr->getNickname()));

	std::string nickname = cmd.getParams()[0];
	
	if (difftime(time(0),usr->getLastNickChange()) <= NICK_DELAY )
		usr->pushReply(":" + cmd.server->getName() + " " + err_unavailableresource(usr->getNickname(), nickname));

	else if (!isNicknameValid(nickname))
		usr->pushReply(":" + cmd.server->getName() + " " + err_erroneusnickname(usr->getNickname(), nickname));
	
	else if (isNicknameInUse(cmd.server->getUsers(), usr, nickname))
		usr->pushReply(":" + cmd.server->getName() + " " + err_nicknameinuse(usr->getNickname(), nickname));

	else
	{
		sendAll(cmd.server->getUsers(), NULL, ":" + usr->getFullName() + " NICK " + cmd.getParams()[0]);
		usr->setNickname(cmd.getParams()[0]);
		greetNewComer(cmd);
	}
}

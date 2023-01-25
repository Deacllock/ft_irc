#include "commandHandlers.hpp"
#include "utils.hpp"

/**
 * @brief The JOIN command is used by a user to request to start listening to the specific channel.
 *
 * Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
 * 				| "0"
 * 
 * @param cmd Contains command, parameters, user and server infos.
 */
void	join(Command cmd)
{
	User	*usr = cmd.getUser();

	if (cmd.getParams().size() < 1)
		return usr->pushReply(":" + cmd.server->getName() + " " + err_needmoreparams(usr->getNickname(), "JOIN"));
	
	if (cmd.getParams()[0] == "0")
		return part(Command(usr, "PART " + usr->listAllChans()));

	std::vector<std::string> channels = splitByComma(cmd.getParams()[0]);
	std::vector<std::string> keys;
	if (cmd.getParams().size() > 1)
		keys = splitByComma(cmd.getParams()[1]);

	std::vector<std::string>::iterator it_k = keys.begin();
	std::vector<std::string>::iterator it_k_end = keys.end();
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		// CHECK NAME IS VALID
		if (!checkChannelName(*it))
			usr->pushReply(":" + cmd.server->getName() + " " + err_badnamechannel(usr->getNickname(), *it));

		// CREATE CHAN
		else
		{
			Channel	*chan = Command::server->getChannelByName(*it);

			if (!chan)
			{
				Command::server->createChan(*it);
				Command::server->getChannelByName(*it)->addOperator(usr);
			}

			if (chan->getKey() != "" && (it_k > it_k_end || *(it_k++) != chan->getKey()))
				usr->pushReply(":" + cmd.server->getName() + " " + err_badchannelkey(usr->getNickname(), chan->getName()));

			else if (chan->isBannedUser(usr))
				usr->pushReply(":" + cmd.server->getName() + " " + err_bannedfromchan(usr->getNickname(), chan->getName()));

			else if (chan->isInviteOnly() && !chan->isInvitedUser(usr))
				usr->pushReply(":" + cmd.server->getName() + " " + err_inviteonlychan(usr->getNickname(), chan->getName()));
			
			else if (usr->tooManyChanJoined())
				return usr->pushReply(":" + cmd.server->getName() + " " + err_toomanychannels(usr->getNickname(), chan->getName()));
			
			else if (chan->isChannelFull())
				usr->pushReply(":" + cmd.server->getName() + " " + err_channelisfull(usr->getNickname(), chan->getName()));

			// JOIN
			else
			{
				chan->addUser(usr);
				usr->addJoinedChan(chan);
				chan->removeInvited(usr);

				sendAll(chan->getUsers(), NULL, ":" + usr->getFullName() + " JOIN " + chan->getName());
				topic(Command (usr, "TOPIC " + chan->getName()));
				names(Command (usr, "NAMES " + chan->getName()));
			}
		}
	}
}

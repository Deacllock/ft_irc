#include "numericReplies.hpp"

/* The server sends Replies 001 to 004 to a user upon successful registration */
//001
std::string	rpl_welcome( std::string nick, std::string user, std::string host ) { return "001 * Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host; }
//002
std::string	rpl_yourhost( std::string servername, std::string version ) { return "002 * Your host is " + servername + ", running version " + version; }
//003
std::string rpl_created( std::string date ) { return "This server was created " + date; }
//004
std::string rpl_myinfo( std::string servername, std::string version, std::string user_modes, std::string channel_modes ) { return "004 * " + servername + " " + version + " " + user_modes + " " + channel_modes; }

//301
std::string	rpl_away( std::string nick, std::string awayMess ) { return nick + " :" + awayMess; }
//322
std::string	rpl_list( std::string channel, std::string visible, std::string topic ) { return channel + " " + visible + " :" + topic; }
//323
std::string	rpl_listend() { return ":End of LIST"; }
//331
std::string	rpl_notopic( std::string channel ) { return channel + " :No topic is set"; };
//332
std::string	rpl_topic( std::string channel, std::string topic ) { return channel + " :" + topic; };
//341
std::string	rpl_inviting( std::string channel, std::string nick ) { return channel + " " + nick; }
//353
std::string	rpl_namreply( std::string channel, std::vector<std::string> nick )
{
	std::string ret = channel + " :";
	std::vector<std::string>::iterator it = nick.begin();
	std::vector<std::string>::iterator it_end = nick.end();
	for (; it < it_end; it++)
	{
		ret += *it;
		if (it + 1 < it_end)
			ret += " ";
	}
	return ret;
}
//366
std::string	rpl_endofnames( std::string channel ) { return channel + " :End of NAMES list"; }

//401
std::string	err_nosuchnick( std::string nickname ) { return "401 * " + nickname + " :No such nick/channel"; }
//403
std::string err_nosuchchannel( std::string channel ) { return "403 * " + channel + " :No such channel"; }
//404
std::string	err_cannotsendtochan( std::string cahnnel ) { return "404 * " + channel + " :Cannot send to channel"; }
//405
std::string err_toomanychannels( std::string channel ) { return "405 * " + channel + " :You have joined too many channels"; }
//407
std::string	err_toomanytargets( std::string target, std::string error_code, std::string abort_mess ) { return "407 * " + target + " :" + error_code + " recipients. " + abort_mess; }
//411
std::string	err_norecipient( std::string command ) { return "411 * :No recipient given (" + command + ")"; }
//412
std::string	err_notexttosend() { return "412 * :No text to send"; }
//413
std::string	err_notoplevel( std::string mask ) { return "413 * :" + mask + " :No toplevel domain specified"; }
//414
std::string	err_wildtoplevel( std::string mask ) { return "414 * :" + mask + "Wildcard in toplevel domain"; }
//431
std::string err_nonicknamegiven() { return "431 * :No nickname given"; }
//432
std::string err_erroneusnickname( std::string nick ) { return "432 *" + nick + " :Erroneous nickname"; }
//433
std::string err_nicknameinuse( std::string nick ) { return "433 * " + nick + " :Nickname is already in use"; }
//437
std::string err_unavailableresource( std::string name ) { return "437 * " + name + " :Nick/channel is temporarily unavailable"; }
//442
std::string	err_notonchannel( std::string channel ) { return "442 * " + channel + " :You're not on that channel"; }
//443
std::string	err_useronchannel( std::string user, std::string channel ) { return "443 * " + user + " " + channel + " :is already on channel"; }
//461
std::string	err_needmoreparams( std::string client, std::string command ) { return "461 * " + client + " " + command + ": Not enough parameters"; }
//462
std::string	err_alreadyregistered( std::string client ) { return "462 * " + client + " :You may not reregister"; }
//471
std::string err_channelisfull(std::string channel) { return "471 * " + channel + " :Cannot join channel (+l)"; }
//473
std::string err_inviteonlychan(std::string channel) { return "473 * " + channel + " :Cannot join channel (+i)"; } // what is +i
//474
std::string err_bannedfromchan(std::string channel) { return "474 * " + channel + " :Cannot join channel (+b)"; }
//475
std::string err_badchannelkey( std::string channel ) { return "475 * " + channel + " :Cannot join channel (+k)"; }
//476
std::string err_badchanmask( std::string channel ) { return "476 * " + channel + " :Bad Channel Mask"; }
//482
std::string err_chanoprivsneeded( std::string channel ) { return "482 * " + channel + " :You're not channel operator"; }
//484
std::string err_restricted() { return "484 * :Your connection is restricted!"; }


std::string error( std::string data ) { return  "Error: " + data; }


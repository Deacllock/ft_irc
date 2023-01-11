#include "numericReplies.hpp"

/* The server sends Replies 001 to 004 to a user upon successful registration */
//001
std::string	rpl_welcome( std::string nick, std::string user, std::string host ) { return "001 * Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host; }
//221
std::string rpl_umodeis( std::string user_mode ) {return "221 * " + user_mode; }
//301
std::string	rpl_away( std::string nick, std::string awayMess ) { return "301 * " + nick + " :" + awayMess; }
//322
std::string	rpl_list( std::string channel, std::string visible, std::string topic ) { return "322 * " + channel + " " + visible + " :" + topic; }
//323
std::string	rpl_listend() { return "323 * :End of LIST"; }
//331
std::string	rpl_notopic( std::string channel ) { return "331 * " + channel + " :No topic is set"; }
//332
std::string	rpl_topic( std::string channel, std::string topic ) { return "332 * " + channel + " :" + topic; }
//341
std::string	rpl_inviting( std::string channel, std::string nick ) { return "341 * " + channel + " " + nick; }
//353
std::string	rpl_namreply( std::string channel, std::vector<std::string> nick )
{
	std::string ret = "353 * " + channel + " :";
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
std::string	rpl_endofnames( std::string channel ) { return "366 * " + channel + " :End of NAMES list"; }
//381
std::string rpl_youreoper() { return "381 * :You are now an IRC operator"; }
//401
std::string	err_nosuchnick( std::string nickname ) { return "401 * " + nickname + " :No such nick/channel"; }
//402
std::string err_nosuchserver( std::string server ) {return "402 * " + server + " :No such server";}
//403
std::string err_nosuchchannel( std::string channel ) { return "403 * " + channel + " :No such channel"; }
//405
std::string err_toomanychannels( std::string channel ) { return "405 * " + channel + " :You have joined too many channels"; }
//407
std::string	err_toomanytargets( std::string target, std::string error_code, std::string abort_mess ) { return "407 * " + target + " :" + error_code + " recipients. " + abort_mess; }
//409
std::string err_noorigin() { return "409 * : No origin specified"; }
//431
std::string err_nonicknamegiven() { return "431 * :No nickname given"; }
//432
std::string err_erroneusnickname( std::string nick ) { return "432 *" + nick + " :Erroneous nickname"; }
//433
std::string err_nicknameinuse( std::string nick ) { return "433 * " + nick + " :Nickname is already in use"; }
//437
std::string err_unavailableresource( std::string name ) { return "437 * " + name + " :Nick/channel is temporarily unavailable"; }
//451
std::string err_notregistered() { return "451 * :You have not registered"; }
//441
std::string err_usernotinchannel(std::string nick, std::string channel) { return "441 * " + nick + " " + channel + " :They aren't on that channel"; }
//442
std::string	err_notonchannel( std::string channel ) { return "442 * " + channel + " :You're not on that channel"; }
//443
std::string	err_useronchannel( std::string user, std::string channel ) { return "443 * " + user + " " + channel + " :is already on channel"; }
//461
std::string	err_needmoreparams( std::string client, std::string command ) { return "461 * " + client + " " + command + ": Not enough parameters"; }
//462
std::string	err_alreadyregistered( std::string client ) { return "462 * " + client + " :You may not reregister"; }
//464
std::string err_passwordmismatch() { return "464 * :Password incorrect"; }
//467
std::string	err_keyset(std::string channel) { return "467 * " + channel + " :Channel key already set"; }
//474
std::string err_bannedformchan(std::string channel) { return "474 * " + channel + " :Cannot join channel (+b)"; }
//471
std::string err_channelisfull(std::string channel) { return "471 * " + channel + " :Cannot join channel (+l)"; }
//472
std::string	err_unknownmode( char c, std::string channel )
{
	std::string s(1, c);
	return "472 * " + s + " :is unknown mode char to me for " + channel;
}
//473
std::string err_inviteonlychan(std::string channel) { return "473 * " + channel + " :Cannot join channel (+i)"; } // what is +i
//474
std::string err_bannedfromchan(std::string channel) { return "474 * " + channel + " :Cannot join channel (+b)"; }
//475
std::string err_badchannelkey( std::string channel ) { return "475 * " + channel + " :Cannot join channel (+k)"; }
//476
std::string err_badchanmask( std::string channel ) { return "476 * " + channel + " :Bad Channel Mask"; }
//477
std::string	err_nochanmodes( std::string channel ) { return "477 * " + channel + " Channel doesn't support modes"; }
//481
std::string err_noprivileges() { return "481 * :Permission Denied- You're not an IRC operator"; }
//482
std::string err_chanoprivsneeded( std::string channel ) { return "482 * " + channel + " :You're not channel operator"; }
//483
std::string err_cantkillserver() { return "483 :You can't kill a server!"; }
//484
std::string err_restricted() { return "484 * :Your connection is restricted!"; }
//501
std::string err_umodeunknownflag() { return "501 * :Unknown MODE flag"; }
//502
std::string err_usersdontmatch() { return "502 * :Cannot change mode for other users"; }

std::string error( std::string data ) { return  "Error: " + data; }

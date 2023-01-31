#include "numericReplies.hpp"

// The server sends Replies 001 to 004 to a user upon successful registration " + nick + "/
//001
std::string	rpl_welcome( std::string nick, std::string host ) { return "001 " + nick + " Welcome to " + host; }
//221
std::string rpl_umodeis( std::string nick, std::string user_mode ) {return "221 " + nick + " " + user_mode; }
//301
std::string	rpl_away( std::string nick, std::string awayMess ) { return "301 " + nick + " :" + awayMess; }
//311
std::string	rpl_whoisuser( std::string nick, std::string user, std::string host, std::string realname ) { return "311 " + nick + " " + user + " " + host + " * :" + realname; }
//312
std::string	rpl_whoisserver( std::string nick, std::string server, std::string serverinfo ) { return "312 " + nick + " " + server + " :" + serverinfo; }
//313
std::string	rpl_whoisoperator( std::string nick ) { return "313 " + nick + " :is an IRC operator"; }
//318
std::string	rpl_endofwhois( std::string nick ) { return "318 " + nick + " :End of WHOIS list"; }
//319
std::string	rpl_whoischannels( std::string nick, std::string channels ) { return "319 " + nick + " :" + channels; }
//322
std::string	rpl_list( std::string nick, std::string channel, std::string visible, std::string topic ) { return "322 " + nick + " " + channel + " " + visible + " :" + topic; }
//323
std::string	rpl_listend( std::string nick ) { return "323 " + nick + " :End of LIST"; }
//324
std::string	rpl_channelmodeis( std::string nick, std::string channel, std::string mode, std::string modeParams ) { return "324 " + nick + " " + channel + " " + mode + " " + modeParams; }
//331
std::string	rpl_notopic( std::string nick, std::string channel ) { return "331 " + nick + " " + channel + " :No topic is set"; }
//332
std::string	rpl_topic( std::string nick, std::string channel, std::string topic ) { return "332 " + nick + " " + channel + " :" + topic; }
//341
std::string	rpl_inviting( std::string nick, std::string channel, std::string nickname ) { return "341 " + nick + " " + channel  + " " + nickname  ; }
//353
std::string	rpl_namreply( std::string nick, std::string channel, std::vector<std::string> nickname )
{
	std::string ret = "353 " + nick + " = " + channel + " :";
	std::vector<std::string>::iterator it = nickname.begin();
	std::vector<std::string>::iterator it_end = nickname.end();

	for (; it < it_end; it++)
	{
		ret += *it;
		if (it + 1 < it_end)
			ret += " ";
	}
	return ret;
}
//366
std::string	rpl_endofnames( std::string nick, std::string channel ) { return "366 " + nick + " " + channel + " :End of NAMES list"; }
//367
std::string	rpl_banlist( std::string nick, std::string channel, std::string ban ) { return "367 " + nick + " " + channel + " " + ban; }
//368
std::string	rpl_banlistend( std::string nick, std::string channel ) { return "368 " + nick + " " + channel + " :End of channel ban list"; }
//381
std::string rpl_youreoper( std::string nick ) { return "381 " + nick + " :You are now an IRC operator"; }
//401
std::string	err_nosuchnick( std::string nick, std::string nickname ) { return "401 " + nick + " " + nickname + " :No such nick/channel"; }
//402
std::string err_nosuchserver( std::string nick, std::string server ) {return "402 " + nick + " " + server + " :No such server";}
//403
std::string err_nosuchchannel( std::string nick, std::string channel ) { return "403 " + nick + " " + channel + " :No such channel"; }
//404
std::string	err_cannotsendtochan( std::string nick, std::string channel ) { return "404 " + nick + " " + channel + " :Cannot send to channel"; }
//405
std::string err_toomanychannels( std::string nick, std::string channel ) { return "405 " + nick + " " + channel + " :You have joined too many channels"; }
//407
std::string	err_toomanytargets( std::string nick, std::string target, std::string error_code, std::string abort_mess ) { return "407 " + nick + " " + target + " :" + error_code + " recipients. " + abort_mess; }
//409
std::string err_noorigin( std::string nick ) { return "409 " + nick + " : No origin specified"; }
//411
std::string	err_norecipient( std::string nick, std::string command ) { return "411 " + nick + " :No recipient given (" + command + ")"; }
//412
std::string	err_notexttosend( std::string nick ) { return "412 " + nick + " :No text to send"; }
//431
std::string err_nonicknamegiven( std::string nick ) { return "431 " + nick + " :No nickname given"; }
//432
std::string err_erroneusnickname( std::string nick, std::string nickname ) { return "432 " + nick + " " +  nickname + " :Erroneous nickname"; }
//433
std::string err_nicknameinuse( std::string nick, std::string nickname ) { return "433 " + nick + " " + nickname + " :Nickname is already in use"; }
//437
std::string err_unavailableresource( std::string nick, std::string name ) { return "437 " + nick + " " + name + " :Nick/channel is temporarily unavailable"; }
//451
std::string err_notregistered( std::string nick ) { return "451 " + nick + " :You have not registered"; }
//441
std::string err_usernotinchannel(std::string nick, std::string nickname, std::string channel) { return "441 " + nick + " " + nickname + " " +channel + " :They aren't on that channel"; }
//442
std::string	err_notonchannel( std::string nick, std::string channel ) { return "442 " + nick + " " + channel + " :You're not on that channel"; }
//443
std::string	err_useronchannel( std::string nick, std::string user, std::string channel ) { return "443 " + nick + " " + user + " " + channel + " :is already on channel"; }
//461
std::string	err_needmoreparams( std::string nick, std::string command ) { return "461 " + nick + " " + command + " :Not enough parameters"; }
//462
std::string	err_alreadyregistered( std::string nick, std::string client ) { return "462 " + nick + " " + client + " :You may not reregister"; }
//464
std::string err_passwordmismatch( std::string nick ) { return "464 " + nick + " :Password incorrect"; }
//467
std::string	err_keyset( std::string nick, std::string channel ) { return "467 " + nick + "  " + channel + " :Channel key already set"; }
//474
std::string err_bannedformchan( std::string nick, std::string channel ) { return "474 " + nick + " " + channel + " :Cannot join channel (+b)"; }
//471
std::string err_channelisfull( std::string nick, std::string channel ) { return "471 " + nick + " " + channel + " :Cannot join channel (+l)"; }
//472
std::string	err_unknownmode( std::string nick, std::string c, std::string channel ) { return "472 " + nick + "  " + c + " :is unknown mode char to me for " + channel; }
//473
std::string err_inviteonlychan( std::string nick, std::string channel ) { return "473 " + nick + " " + channel + " :Cannot join channel (+i)"; }
//474
std::string err_bannedfromchan( std::string nick, std::string channel) { return "474 " + nick + " " + channel + " :Cannot join channel (+b)"; }
//475
std::string err_badchannelkey( std::string nick, std::string channel ) { return "475 " + nick + " " + channel + " :Cannot join channel (+k)"; }
//476
std::string err_badchanmask( std::string nick, std::string channel ) { return "476 " + nick + " " + channel + " :Bad Channel Mask"; }
//477
std::string	err_nochanmodes( std::string nick, std::string channel ) { return "477 " + nick + "  " + channel + " Channel doesn't support modes"; }
//481
std::string err_noprivileges( std::string nick ) { return "481 " + nick + " :Permission Denied- You're not an IRC operator"; }
//482
std::string err_chanoprivsneeded( std::string channel ) { return "482 " + channel + " :You're not channel operator"; }
//483
std::string err_cantkillserver( std::string nick ) { return "483 " + nick + " :You can't kill a server!"; }
//484
std::string err_restricted( std::string nick ) { return "484 " + nick + " :Your connection is restricted!"; }
//501
std::string err_umodeunknownflag( std::string nick ) { return "501 " + nick + " :Unknown MODE flag"; }
//502
std::string err_usersdontmatch( std::string nick ) { return "502 " + nick + " :Cannot change mode for other users"; }

std::string	err_badnamechannel( std::string nick, std::string name ) { return nick + " " + name + " :Bad name channel"; }
std::string error( std::string data ) { return " ERROR :" + data; }

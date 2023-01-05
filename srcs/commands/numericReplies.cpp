
#include <string>

/* The server sends Replies 001 to 004 to a user upon successful registration */
std::string	rpl_welcome( std::string nick, std::string user, std::string host ) { return "001 * Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host; }
std::string	rpl_yourhost( std::string servername, std::string version ) { return "002 * Your host is " + servername + ", running version " + version; }
std::string rpl_created( std::string date ) { return "This server was created " + date; }
std::string rpl_myinfo( std::string servername, std::string version, std::string user_modes, std::string channel_modes ) { return "004 * " + servername + " " + version + " " + user_modes + " " + channel_modes; }

std::string rpl_umodeis( std::string user_mode ) {return "221 * " + user_mode; }
std::string	rpl_topic( std::string channel, std::string topic ) { return "332 * " + channel + " :" + topic; };

std::string rpl_youreoper() { return "381 * :You are now an IRC operator"; }

std::string err_nosuchserver( std::string server ) {return "402 * " + server + " :No such server";} //402
std::string err_nosuchchannel( std::string channel ) { return "403 * " + channel + " :No such channel"; }
std::string err_toomanychannels( std::string channel ) { return "405 * " + channel + " :You have joined too many channels"; }
std::string	err_toomanytargets( std::string target, std::string error_code, std::string abort_mess ) { return "407 * " + target + " :" + error_code + " recipients. " + abort_mess; }
std::string err_noorigin() { return "409 * : No origin specified"; }
std::string err_nonicknamegiven() { return "431 * :No nickname given"; }
std::string err_erroneusnickname( std::string nick ) { return "432 *" + nick + " :Erroneous nickname"; }
std::string err_nicknameinuse( std::string nick ) { return "433 * " + nick + " :Nickname is already in use"; }
std::string err_unavailableresource( std::string name ) { return "437 * " + name + " :Nick/channel is temporarily unavailable"; }
std::string err_notregistered() { return "451 * :You have not registered"; }
std::string	err_needmoreparams( std::string client, std::string command ) { return "461 * " + client + " " + command + ": Not enough parameters"; }
std::string	err_alreadyregistered( std::string client ) { return "462 * " + client + " :You may not reregister"; }
std::string err_passwordmismatch() { return "464 * :Password incorrect"; }
std::string err_channelisfull(std::string channel) { return "471 * " + channel + " :Cannot join channel (+l)"; }
std::string err_inviteonlychan(std::string channel) { return "473 * " + channel + " :Cannot join channel (+i)"; } // what is +i
std::string err_bannedformchan(std::string channel) { return "474 * " + channel + " :Cannot join channel (+b)"; }
std::string err_badchannelkey( std::string channel ) { return "475 * " + channel + " :Cannot join channel (+k)"; }
std::string err_bedchanmask( std::string channel ) { return "476 * " + channel + " :Bad Channel Mask"; }
std::string err_restricted() { return "484 * :Your connection is restricted!"; }
std::string err_umodeunknownflag() { return "501 * :Unknown MODE flag"; }
std::string err_usersdontmatch() { return "502 * :Cannot change mode for other users"; }

std::string error( std::string data ) { return  "Error: " + data; }


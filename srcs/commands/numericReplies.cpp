
#include <string>

/* The server sends Replies 001 to 004 to a user upon successful registration */
std::string	rpl_welcome( std::string nick, std::string user, std::string host ) { return "Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host; }
std::string	rpl_yourhost( std::string servername, std::string version ) { return "Your host is " + servername + ", running version " + version; }
std::string rpl_created( std::string date ) { return "This server was created " + date; }
std::string rpl_myinfo( std::string servername, std::string version, std::string user_modes, std::string channel_modes ) { return servername + " " + version + " " + user_modes + " " + channel_modes; }

std::string	err_needmoreparams( std::string client, std::string command ) { return client + " " + command + ": Not enough parameters"; }
std::string	err_alreadyregistered( std::string client ) { return client + " :You may not reregister"; }
std::string	err_passwdmismatch( std::string client ) { return client + " :Password incorrect"; }

std::string err_nonicknamegiven() { return ":No nickname given"; }
std::string err_erroneusnickname( std::string nick ) { return nick + " :Erroneous nickname"; }
std::string err_nicknameinuse( std::string nick ) { return nick + " :Nickname is already in use"; }
std::string err_unavailableresource( std::string name ) { return name + " :Nick/channel is temporarily unavailable"; }
std::string err_restricted() { return ":Your connection is restricted!"; }

std::string error( std::string data ) { return  "Error: " + data; }


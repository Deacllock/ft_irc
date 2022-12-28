#ifndef NUMERICREPLIES
# define NUMERICREPLIES

#include <string>

/* The server sends Replies 001 to 004 to a user upon successful registration */
std::string	rpl_welcome( std::string nick, std::string user, std::string host ); //001
std::string	rpl_yourhost( std::string servername, std::string version ); //002
std::string rpl_created( std::string date ); //003
std::string rpl_myinfo( std::string servername, std::string version, std::string user_modes, std::string channel_modes ); //004

std::string err_nonicknamegiven(); //431
std::string err_erroneusnickname( std::string nick ); //432
std::string err_nicknameinuse( std::string nick ); //433
std::string err_unavailableresource( std::string name ); //437
std::string	err_needmoreparams( std::string client, std::string command ); //461
std::string	err_alreadyregistered( std::string client ); //462
std::string err_restricted(); //484 

#endif
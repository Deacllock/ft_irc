#ifndef NUMERICREPLIES
# define NUMERICREPLIES

#include <string>

/* The server sends Replies 001 to 004 to a user upon successful registration */
std::string	rpl_welcome( std::string nick, std::string user, std::string host ); //001
std::string	rpl_yourhost( std::string servername, std::string version ); //002
std::string rpl_created( std::string date ); //003
std::string rpl_myinfo( std::string servername, std::string version, std::string user_modes, std::string channel_modes ); //004

std::string rpl_umodeis( std::string user_mode ); //221
std::string	rpl_topic( std::string channel, std::string topic ); //332
std::string	rpl_youreoper(); //381

std::string err_nosuchserver( std::string server ); //402
std::string err_nosuchchannel( std::string channel ); //403
std::string err_toomanychannels( std::string channel ); //405
std::string	err_toomanytargets( std::string target, std::string error_code, std::string abort_mess ); //407
std::string err_noorigin(); //409
std::string err_nonicknamegiven(); //431
std::string err_erroneusnickname( std::string nick ); //432
std::string err_nicknameinuse( std::string nick ); //433
std::string err_unavailableresource( std::string name ); //437
std::string err_notregistered(); //451
std::string	err_needmoreparams( std::string client, std::string command ); //461
std::string	err_alreadyregistered( std::string client ); //462
std::string err_passwordmismatch(); //464
std::string err_channelisfull( std::string channel ); // 471
std::string err_inviteonlychan( std::string channel ); //473
std::string err_bannedfromchan( std::string channel ); //474
std::string err_badchannelkey( std::string channel ); //475
std::string err_bedchanmask( std::string channel ); //476
std::string err_restricted(); //484 


std::string error( std::string data );
#endif

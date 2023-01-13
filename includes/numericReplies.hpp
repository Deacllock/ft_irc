#ifndef NUMERICREPLIES
# define NUMERICREPLIES

#include <string>
#include <vector>

std::string	rpl_welcome( std::string nick, std::string host ); //001
std::string rpl_umodeis( std::string nick, std::string user_mode ); //221
std::string	rpl_topic( std::string nick, std::string channel, std::string topic ); //332
std::string	rpl_youreoper( std::string nick ); //381
std::string	rpl_list( std::string nick, std::string channel, std::string visible, std::string topic ); //322
std::string	rpl_listend( std::string nick ); //323
std::string	rpl_channelmodeis( std::string nick, std::string channel, std::string mode, std::string params ); //324
std::string	rpl_notopic( std::string nick, std::string channel ); //331
std::string	rpl_topic( std::string nick, std::string channel, std::string topic ); //332
std::string	rpl_inviting( std::string nick, std::string channel, std::string nickname ); //341
std::string	rpl_namreply( std::string nick, std::string channel, std::vector<std::string> nicks ); //353 //VISIBILITY ????
std::string	rpl_endofnames( std::string nick, std::string channel ); //366
std::string	err_nosuchnick( std::string nick, std::string nickname ); //401
std::string err_nosuchserver( std::string nick, std::string server ); //402
std::string err_nosuchchannel( std::string nick, std::string channel ); //403
std::string err_toomanychannels( std::string nick, std::string channel ); //405
std::string	err_toomanytargets( std::string nick, std::string target, std::string error_code, std::string abort_mess ); //407
std::string err_noorigin( std::string nick ); //409
std::string err_nonicknamegiven( std::string nick ); //431
std::string err_erroneusnickname( std::string nick, std::string nickname ); //432
std::string err_nicknameinuse( std::string nick, std::string nickname ); //433
std::string err_unavailableresource( std::string nick, std::string name ); //437
std::string err_notregistered( std::string nick ); //451
std::string err_usernotinchannel( std::string nick, std::string nickname, std::string channel ); //441
std::string	err_notonchannel( std::string nick, std::string channel ); //442
std::string	err_useronchannel( std::string nick, std::string user, std::string channel ); //443
std::string	err_needmoreparams( std::string nick, std::string command ); //461
std::string	err_alreadyregistered( std::string nick, std::string client ); //462
std::string err_passwordmismatch( std::string nick ); //464
std::string err_keyset( std::string nick, std::string channel ); //467
std::string err_channelisfull( std::string nick, std::string channel ); // 471
std::string	err_unknownmode( std::string nick, std::string c, std::string channel ); //472
std::string err_inviteonlychan( std::string nick, std::string channel ); //473
std::string err_bannedfromchan( std::string nick, std::string channel ); //474
std::string err_badchannelkey( std::string nick, std::string channel ); //475
std::string err_badchanmask( std::string nick, std::string channel ); //476
std::string err_noprivileges( std::string nick ); // 481
std::string err_chanoprivsneeded( std::string channel ); //482
std::string err_cantkillserver( std::string nick ); //483
std::string err_restricted( std::string nick ); //484 
std::string err_umodeunknownflag( std::string nick ); //501
std::string err_usersdontmatch( std::string nick ); //502
std::string error( std::string nick, std::string data );

#endif

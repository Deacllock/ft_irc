#ifndef NUMERICREPLIES
# define NUMERICREPLIES

#include <string>
#include <vector>

std::string	rpl_welcome( std::string nick, std::string user, std::string host ); //001
std::string rpl_umodeis( std::string user_mode ); //221
std::string	rpl_topic( std::string channel, std::string topic ); //332
std::string	rpl_youreoper(); //381
std::string	rpl_list( std::string channel, std::string visible, std::string topic ); //322
std::string	rpl_listend(); //323
std::string	rpl_channelmodeis( std::string channel, char mode, std::string modeParams ); //324
std::string	rpl_uniqopis( std::string channel, std::string nickname ); //325
std::string	rpl_notopic( std::string channel ); //331
std::string	rpl_topic( std::string channel, std::string topic ); //332
std::string	rpl_inviting( std::string channel, std::string nick ); //341
std::string	rpl_namreply( std::string channel, std::vector<std::string> nick ); //353 //VISIBILITY ????
std::string	rpl_endofnames( std::string channel ); //366
std::string	err_nosuchnick( std::string nickname ); //401
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
std::string err_usernotinchannel(std::string nick, std::string channel); //441
std::string	err_notonchannel( std::string channel ); //442
std::string	err_useronchannel( std::string user, std::string channel ); //443
std::string	err_needmoreparams( std::string client, std::string command ); //461
std::string	err_alreadyregistered( std::string client ); //462
std::string err_passwordmismatch(); //464
std::string	err_keyset(std::string channel); //467
std::string err_channelisfull( std::string channel ); //471
std::string	err_unknownmode( char c, std::string channel ); //472
std::string err_inviteonlychan( std::string channel ); //473
std::string err_bannedfromchan( std::string channel ); //474
std::string err_badchannelkey( std::string channel ); //475
std::string err_badchanmask( std::string channel ); //476
std::string	err_nochanmodes( std::string channel ); //477
std::string err_noprivileges(); // 481
std::string err_chanoprivsneeded( std::string channel ); //482
std::string err_cantkillserver(); //483
std::string err_restricted(); //484 
std::string err_umodeunknownflag(); //501
std::string err_usersdontmatch(); //502
std::string error( std::string data );

#endif

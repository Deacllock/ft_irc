#ifndef COMMANDHANDLERS
# define COMMANDHANDLERS

# include "Command.hpp"
# include "numericReplies.hpp"
# include "utils.hpp"

/*---------------- Connection ----------------*/
void	pass( Command cmd );
void	greetNewComer( Command cmd );
void	nick( Command cmd );
void	user( Command cmd );
void	cap( Command cmd );
void	quit( Command cmd );
void	mode( Command cmd );
void	ping( Command cmd );
void	pong( Command cmd );
void	whois( Command cmd );

/*---------------- Channel ----------------*/
void	join( Command cmd );
void	part( Command cmd );
void	invite( Command cmd );
void	topic( Command cmd );
void	list( Command cmd );
void	names( Command cmd );

/*---------------- Operator ----------------*/
void	die( Command cmd );
void	kick( Command cmd );
void	kill( Command cmd );
void	oper( Command cmd );
void	user_mode( Command cmd );
 
/*---------------- Message ----------------*/
void	privmsg( Command cmd );
void	notice( Command cmd );

#endif

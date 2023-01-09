#ifndef COMMANDHANDLERS
# define COMMANDHANDLERS

# include "Command.hpp"
# include "numericReplies.hpp"

/*---------------- Connection ----------------*/
void	pass( Command &cmd );
void	greetNewComer( Command &cmd );
void	nick( Command &cmd );
void	user( Command &cmd );
void	cap(Command &cmd);
void	quit(Command &cmd);
void	mode(Command &cmd);

/*---------------- Channel ----------------*/
void	join(Command &cmd);
void	part(Command &cmd);
void	invite(Command &cmd);
void	topic(Command &cmd);
void	list(Command &cmd);
void	names(Command &cmd);

/*---------------- Operator ----------------*/
void	die(Command &cmd);
void	kill(Command &cmd);
void	oper(Command &cmd);


#endif

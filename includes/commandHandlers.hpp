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
void	oper(Command &cmd);
void	quit(Command &cmd);

/*---------------- Channel ----------------*/
void	join(Command &cmd);

#endif

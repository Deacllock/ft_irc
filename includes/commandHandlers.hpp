#ifndef COMMANDHANDLERS
# define COMMANDHANDLERS

# include "Command.hpp"
# include "numericReplies.hpp"

void	pass( Command &cmd );
void	greetNewComer( Command &cmd );
void	nick( Command &cmd );
void	user( Command &cmd );
void	cap(Command &cmd);
void	join(Command &cmd);

#endif

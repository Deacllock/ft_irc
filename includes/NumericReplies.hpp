#ifndef NUMERICREPLIES
# define NUMERICREPLIES

# define ERR_NEEDMOREPARAMS(client, command) #client  " "  #command  ": Not enough parameters"
# define _461(client, command) ERR_NEEDMOREPARAMS(client, command)

# define ERR_ALREADYREGISTERED(client) #client ": You may not reregister"
# define _462(client) ERR_ALREADYREGISTERED(client)

# define ERR_PASSWDMISMATCH(client) #client ": Password incorrect"
# define _464(client) ERR_PASSWDMISMATCH(client)

# define ERROR(data) "Error: " data

#endif
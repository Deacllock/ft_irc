#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
int main(void)
{
	int protocol_id = getprotobyname("TCP")->p_proto; //Shall I intercept NULL for static value?
	int socket_fd = socket(AF_INET | AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, protocol_id);
	if ( socket_fd == -1)
	{
		std::cerr << "oh oh " << std::endl;
		return 1;
	}
	return 0;
}
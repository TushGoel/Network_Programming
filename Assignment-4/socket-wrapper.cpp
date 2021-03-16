/*
Author: Tushar Goel
*/

// Adding the include guards
#include <socket-wrapper.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <vector>

// Implementation of the Overloading operator<< for SocketWrapper, to print to a 
// std::ostream object.
std::ostream& operator<<(std::ostream &out, const SocketWrapper &soc)
{
	soc.print(out);
	return out;
};


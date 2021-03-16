/*
Author: Tushar Goel
*/

// Defining socket-wrapper header file
#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

// Adding the include guards
#include <vector>
#include <string>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>


// Declaration and implementation of an abstract class SocketWrapper, with the required/suggested 
// public methods (as virtual/pure virtual)
class SocketWrapper
{

public:

  virtual ~SocketWrapper(){};

  virtual int recvData(char* buf) = 0;

  virtual int sendData(const char* buf, size_t size_to_tx) = 0;

  virtual void runServer() = 0;

// Declaration of the Overloading operator<< for SocketWrapper, to print to a 
// std::ostream object and declared as friend of SocketWrapper
  friend std::ostream& operator<<(std::ostream& out, const SocketWrapper& soc);

protected:
	virtual void print(std::ostream& out) const = 0;

};

#endif
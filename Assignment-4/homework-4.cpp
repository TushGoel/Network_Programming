/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Kumar Nithyakumar 
*/

#include <iostream>
#include <chrono>
#include <tcp-wrapper.h>
#include <signal.h>
#include <string.h>
#include <socket-wrapper.h>

int
main(int argc, char const *argv[])
{

  struct sigaction act;// structure that contains the handler
  memset(&act, '\0', sizeof(act));
  act.sa_handler = SIG_IGN; // handler that ignores the signal
  if (sigaction(SIGPIPE, &act, NULL) < 0) { // set the handler to
  // SIGPIPE
    std::cerr << "SIGPIPE" << std::endl; //
  }

  TcpWrapper tcp_server {55555};


// Declaration of SocketWrapper* ptr_tcp and initialization it with a pointer to tcp_server. 
  SocketWrapper* ptr_tcp = &tcp_server;

// Printing to the terminal using the << operator. 
  std::cout << *ptr_tcp << std:: endl;

// Call to the runServer using ptr_tcp.  
  ptr_tcp->runServer();

  return 0;
}

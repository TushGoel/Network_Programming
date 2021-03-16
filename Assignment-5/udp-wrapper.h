/*
Created and modified by Tushar Goel
*/

#ifndef UDP_WRAPPER_H
#define UDP_WRAPPER_H

#include <string>
#include <socket-wrapper.h>
#include <netinet/in.h>

/**
 * Class UdpWrapper
 */
class UdpWrapper : public SocketWrapper
{
private:
  int m_port; /* listen socket port number */
  struct sockaddr_in m_last_recv_ip; /*IP of the last host that sent data */
  bool m_exit; /* true if run should end */
  int m_sock_fd; /* socket file descriptor */

public:
/*
   * Class constructor.
   * @param port_num integer with the port number
*/
  UdpWrapper(int port_num);

  /**
   * Class destructor.
   */
  ~UdpWrapper();

 /**
   * Receives data from remote host.
   * @param buf buffer where the received data is stored
   * @return number of bytes received (-1 if error occurred)
   */
  int recvData(char* buf) override;

  /**
   * Send data to remote host.
   * @param buf pointer to the buffer where the data to be sent is stored
   * @param size_to_tx size to transmit
   * @return number of bytes sent (-1 if error occurred)
   */
  int sendData(const char* buf, size_t size_to_tx) override;

  /**
   * Function executed in a thread dispatched by the constructor 
   * to start the server listener
   */
  void runServer() override;

  /**
   * Print something about the socket
   * @param out an ostream to print to
   * @return an ostream
   */
  void print(std::ostream& out) const override;

  /*
  returns a string with the IP of the last client from which 
  data was received (this method can be used, for example, 
  by the print method).
  */
  std::string getLastIp() const;


};

#endif /* UDP_WRAPPER */

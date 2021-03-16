/*
Created and modified by Tushar Goel
*/

#include <udp-wrapper.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

UdpWrapper::UdpWrapper(int port_num)
:
m_port{port_num},
m_last_recv_ip {},
m_exit{false},
m_sock_fd{-1}
{
// open the m_sock_fd socket of type SOCK_DGRAM
  m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  // check if the socket creation was successful
  if (m_sock_fd < 0)
  {
  	std::cout << "ERROR: UDP SOCKET OPEN" << std::endl;
    return;
  }

 // UDP Socket setting
  int option(1);
  int res = setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&option, sizeof(option));
	// res = 0 means success

  // Check if Socket setting was successful
	if(res < 0)
	{
		std::cout << "ERROR: UDP SOCKET SETTING FAILED" << std::endl;
		// here we close just m_sock_fd 
		if(m_sock_fd >= 0)
		{
			close(m_sock_fd);
		}		
		return;
	}

	// UDP socket binding
	struct sockaddr_in my_addr = {0};
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(m_port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Check if Socket binding was successful
	if(bind(m_sock_fd, (struct sockaddr*) &my_addr, sizeof(my_addr)) < 0)
	{
		std::cout << "ERROR: UDP SOCKET BINDING FAILED" << std::endl;
		// here we close just m_sock_fd 
		if(m_sock_fd >= 0)
		{
			close(m_sock_fd);
		}
		return;
	}
}


UdpWrapper::~UdpWrapper()
{
	// here we close just m_sock_fd 
	if(m_sock_fd >= 0)
	{
		close(m_sock_fd);
		m_sock_fd = -1;
	}
	m_exit = true;
}


int 
UdpWrapper::recvData(char* buf)  
{
  if(m_sock_fd < 0) 
  {
  	std::cout << "ERROR: UDP RECEIVED FAILED!" << std::endl;
    return -1;
  }

  // call the recv API
  socklen_t addrlen = sizeof(m_last_recv_ip);
  int recv_size = ::recvfrom(m_sock_fd, buf, C_MTU, 0, (struct sockaddr *) &m_last_recv_ip, &addrlen);
  
  // check if the recv size is ok or not
  if(recv_size < 0) 
  {
    std::cout << "ERROR: UDP RECV FUNCTION FAILED " << std::endl;

    // here we close just m_sock_fd 
    if(m_sock_fd >= 0) 
    {
      close(m_sock_fd);
      m_sock_fd = -1;
    }
    // if error close the socket and exit
    return -1;
  }
  return recv_size;
}


int
UdpWrapper::sendData(const char* buf, size_t size_to_tx) 
{
  if(m_sock_fd<0) 
  {
  	std::cout << "ERROR: UDP SEND FAILED!" << std::endl;
    return -1;
  }

  // send the data through sckfd
  int sent_size = ::sendto(m_sock_fd, buf, size_to_tx, 0, (struct sockaddr*) &m_last_recv_ip, sizeof(m_last_recv_ip)); 
  // the send returns a size of -1 in case of errors
  if(sent_size < 0) 
  {
    std::cout << "ERROR: UDP SENDTO FUNCTION FAILED" << std::endl;
    // here we close just m_sock_fd 
    if(m_sock_fd >= 0) 
    {
      close(m_sock_fd);
      m_sock_fd = -1;
    } 
    // if error close the socket and exit
    return -2;
  }
  return sent_size;
}


void 
UdpWrapper::runServer() 
{
  // create a char buffer called buf, of size C_MTU
  char buf[C_MTU];

  // start a while loop to receive data and send application ACKs to this client
  // the loop ends when m_exit is true
  while(!m_exit) 
  {
    // call recvData, passing buf, to receive data
    // save the return value of recvData in a data_size variable
    int data_size = recvData(buf);

    // check if the data_size is smaller than 0
    // if yes, set m_exit to true and break the loop
    if (data_size < 0) 
    {
      std::cout << "TERMINATE: UDP SOCKET RECV ERROR" << std::endl;
      m_exit = true;
      break;
    } 
    // check if the data_size is equal to 0
    // if yes, set m_exit to true and break the loop
    else if (data_size == 0) 
    {
      std::cout << "TERMINATE: UDP SOCKET RECV ERROR - the other endpoint has closed the socket" << std::endl;
      m_exit = true;
      break;
    } 

    // print the buf to the terminal
    std::cout << buf <<std::endl;

    // reset the buffer for a new read using memset
    memset(buf, 0, C_MTU); // this cleans the buffer for a new read

    // send an application ACK to the other endpoint
    std::string to_tx = "Packet ACK\n";
    if(sendData(to_tx.c_str(), to_tx.length()) >= 0) 
    {
      std::cout << "UDP SOCKET TX Successful" << std::endl;
    } 
    else 
    {
      // if the transmission was not successful, set m_exit to true and break the loop
      std::cout << "UDP SOCKET TX NOT Successful" << std::endl;
      m_exit = true;
      break;
    }
  }
}

void 
UdpWrapper::print(std::ostream& out) const
{
  out << "UDP socket on port: " << m_port;
  out << getLastIp();
}

std::string UdpWrapper::getLastIp() const
{
	return std::string(inet_ntoa(m_last_recv_ip.sin_addr));
}
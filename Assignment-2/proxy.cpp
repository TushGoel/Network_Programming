/*
 * [2020] Northeastern University - Network Programming
 * All Rights Reserved.
 * 
 * Author Michele Polese and Pragadeesh Nithyakumar
*/

/* Homework Assignment - 2 By Tushar Goel */

// Exercise 0: add the relevant includes
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

int main(int argc, char** argv) {

  // READ from argv, the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./proxy has argc = 1 and no command line arguments
  //   ./proxy 55555 has argc = 2 and the tcp_server port as argument
  //   ./proxy 55555 55556 has argc = 3 and the tcp_server port and udp_client port as argument
  
  // Exercise 1a: declare a variable listen_port of type const int, which is
  // 55555 if no argument is provided, or the argument otherwise
	const int listen_port = (argc == 1) ? 55555 : atoi(argv[1]);

  // Exercise 1b: declare a variable udp_port of type const int, which is
  // 55556 if no argument is provided, or the argument otherwise
	const int udp_port = (argc == 3) ? 55556 : atoi(argv[2]);

  const char* udp_ip = "127.0.0.1";  //Local IP address
  
  // Open UDP client
  // Exercise 2: open a SOCK_DGRAM (UDP) socket and save the file descriptor
  // in an int variable called sockfd_udp
  // Check if the operation is successful, if not, print an error, close the socket and return
  	int sockfd_udp = socket(AF_INET, SOCK_DGRAM, 0);

	if(sockfd_udp < 0)
	{
		std::cout << " Opening of udp socket failed " << std::endl;
		close(sockfd_udp);
		return -1;
	}  
  
  struct sockaddr_in servaddr_udp = {0};     
  // Fill UDP server information 
  servaddr_udp.sin_family = AF_INET; 
  servaddr_udp.sin_port = htons(udp_port); 

  // Exercise 3: use inet_pton to convert udp_ip into the sin_addr field of servaddr_udp
  // Check if the operation is successful, if not, print an error, close the socket and return
	if(inet_pton(AF_INET, udp_ip, &servaddr_udp.sin_addr) <= 0)
	{
		std::cout << " Conversion of the udp_ip to sin_addr failed " << std::endl;
		close(sockfd_udp);
		return -2;
	}

  // Open a SOCK_STREAM (TCP) socket called scklist
  // Exercise 4: open a SOCK_STREAM (TCP) socket and save the file descriptor
  // in an int variable called scklist
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
	int scklist = socket(AF_INET, SOCK_STREAM, 0);

	if(scklist < 0)
	{
		std::cout << " Opening of the tcp socket failed " << std::endl;
		close(sockfd_udp);
		close(scklist);
		return -3;
	}


  // Set socket options to release the socket address immediately after, on both sockets 
  // the socket is closed
  int option(1);
  setsockopt(scklist, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  setsockopt(sockfd_udp, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));

  // At this point your code MUST compile correctly

  // Exercise 5: declare and set to 0 a struct called my_addr and of type struct sockaddr_in 
  // then set the field sin_family of my_addr to AF_INET, the sin_port to listen_port
  // and the sin_addr.s_addr to INADDR_ANY
  struct sockaddr_in my_addr = {0};
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(listen_port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Exercise 6: bind the socket to my_addr using the bind API
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
	if(bind(scklist, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0)
	{
		std::cout << " Binding of the socket in tcp sever failed " << std::endl;
		close(sockfd_udp);
		close(scklist);
		return -4;
	}

  // Exercise 7: set scklist in a listening state, using the listen API (with at most 1 client)
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
	if(listen(scklist, 1) < 0)
	{
		std::cout << " tcp server setting to the listening state failed " << std::endl;
		close(sockfd_udp);
		close(scklist);
		return -5;
	}

  // Create a sockaddr_in for clientaddr_tcp
  struct sockaddr_in clientaddr_tcp;
  socklen_t addr_l = sizeof(clientaddr_tcp);

  // Exercise 8: perform these 3 operations using the accept API on scklist:
  // 1) accept the connection of a new client.
  // 2) create a new socket (called sockfd) used to perform the actual data transmission 
  //    between TCP client and TCP server.
  // 3) save into clientaddr_tcp the address of the client connected, so you 
  //    can know who is sending what.
  // Check if the operation is successful, if not, print an error, close the socket(s) and return
  int sockfd = accept(scklist, (struct sockaddr*) &clientaddr_tcp, &addr_l);

	if(sockfd < 0)
	{
		std::cout << " tcp connection from the client failed " << std::endl;
		close(scklist);
		close(sockfd_udp);
		return -6;
	}

  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(clientaddr_tcp.sin_addr) << std::endl; 

  // Prepare the receive buffer, with at most 512 bytes
  const size_t max_size = 512;
  char buf[max_size] = {0};

  // Create a while(true) loop
  while(true) {
    // Exercise 9: set the buf content to 0
	memset(buf, 0, max_size);

    // Exercise 10: receive with recv on sockfd, and save the received amount of bytes in rcv_size
    // Check if the recv is successful, if not, print an error, close the socket(s) and return
    // If the recv is successful but rcv_size is 0, this means that the socket was closed 
    // by the other endpoint of the TCP connection. You need to handle this case as well, 
    // close the sockets and return 0
    // The two cases must be handled separately, e.g., 
    // if (error condition) {...} else if (close condition) {...}
    int rcv_size = recv(sockfd, buf, max_size, 0);
	
	if(rcv_size <= 0)
	{
		std::cout << "Byte recieved is 0. Either receiving failed or socket from the other end point was closed " << std::endl;
		close(scklist);
		close(sockfd_udp);
		return -7;
	}

    // Exercise 11: print buf and the received size
    std::cout << "Received: " << buf << std::endl;
	std::cout << "Received size is: " << rcv_size << std::endl;

    // Exercise 12: send buf on sockfd_udp using sendto, to the address in servaddr_udp
    // Check if the send is successful, if not, print an error, close the socket(s) and return
    if(sendto(sockfd_udp, buf, max_size, 0, (struct sockaddr*) &servaddr_udp, sizeof(servaddr_udp)) < 0)
    {
		std::cout << " udp send is failed " << std::endl;
		close(scklist);
		close(sockfd_udp);
		return -8;
	}

    std::cout << "Message sent to udp server" << std::endl; 
  }

  // Exercise 13: close the sockets
  close(scklist);
  close(sockfd_udp);
}


# Problem Description:
This homework has only one exercise. The goal here is to make you familiar with socket programming basics with respect to TCP and UDP protocols.

proxy.cpp:
☐ proxy.cpp has a skeleton that has already been written. The original code has step by step instructions on what you are supposed to do. Your task is to edit, compile and run the code without any errors.

☐ The goal of this exercise is to build a proxy server that has the capability to receive from a TCP client and forward the data to an UDP server.

☐ So, you would be integrating a TCP server (to catch the TCP data) and an UDP client (to send the data to the UDP server) in the same program. Write your program by following the directions in the comments in the code, edit the code, run the installer without any errors and finally run the program to check if everything is working proper.

You can check if the program works proper by following these steps:
☐ Open 3 terminals and do the following in the same order.

☐ Open a netcat UDP server on one of the terminals using: nc -u -l <port_number> 
The default UDP port_number of the proxy is 55556

☐ Open the proxy_example executable you just compiled on another terminal.

☐ On the third terminal, open a netcat TCP client by using: nc <ip_address> <port_number>
The default IP is 127.0.0.1 and the default port number is 55555

☐ Now type something in the TCP client window. The proxy should receive the data and pass it on to
the UDP server and print it out in the UDP server window.
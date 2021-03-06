# Problem Description:

// Notice that the implementation of TcpWrapper has slightly changed from 
// the solution of homework 3. The difference is that the method runServer()
// (formerly run()) is not called inside the constructor of TcpWrapper, but
// needs to be called as a method on an object TcpWrapper.

// Exercise 1: create the files socket-wrapper.h and socket-wrapper.cpp. The socket-wrapper.cpp must #include the header file, and must be added to the homework_4_exec_SOURCES in Makefile.am

// Exercise 2: add the include guards to socket-wrapper.h

// Exercise 3: in socket-wrapper.h and socket-wrapper.cpp, declare and implement 
// an abstract class SocketWrapper, with the following 
// public methods (properly mark them as virtual/pure virtual):
// - ~SocketWrapper
// - int recvData(char* buf)
// - int sendData(const char* buf, size_t size_to_tx)
// - void runServer()
// and protected method 
// (properly mark them as virtual/pure virtual):
// - void print(std::ostream& out) const

// Exercise 4: make TcpWrapper a public subclass of SocketWrapper, and mark the 
// methods that override the pure virtual function. Add the declaration and 
// implementation of print, which should print to the ostream object 
// relevant information on the TcpWrapper instance

// Exercise 5: overload the operator<< for SocketWrapper, to print to a 
// std::ostream object. The implementation should work with subclasses 
// of SocketWrapper that override void print(std::ostream& out) const
// This operator should be declared as friend of SocketWrapper

// Exercise 6: in homework-4.cpp, declare SocketWrapper* ptr_tcp and initialize it with
// a pointer to tcp_server. Then print to the terminal relevant information on the 
// object using the << operator. Finally, call runServer using ptr_tcp.
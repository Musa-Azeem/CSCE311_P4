/*
Written by Musa Azeem
Unix Domain Socket Class Header
This file defines a class UnixDomainSocket, 
  which acts as base class for the text-server and text-client classes
Class variables: 
  socker_addr:  struct containing type and address of socket
  socket_path_: path to socket file
*/

#ifndef UNIXDOMAINSOCKET
#define UNIXDOMAINSOCKET

#define SOCKET_BUFFER_SIZE 1024

#include <sys/un.h>
#include <string>
#include <tuple>

class UnixDomainSocket{
  public:
    explicit UnixDomainSocket(const char *socket_path);
    ssize_t write(std::string msg);
    std::tuple<ssize_t, std::string> read();
  private:
    ::sockaddr_un sock_addr_;
    std::string socket_path_;
};

#endif
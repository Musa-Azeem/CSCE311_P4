/*
Written by Musa Azeem
Unix Domain Socket Class source code
This file defines the constructor for UnixDomainSocket class
Functions:
    UnixDomainSocket Constructor:
        initializes socket_path with given socket path
        initializes sock_addr with 
            sun_family set to AF_UNIX
            sun_path set to given socket path
*/

#include "../inc/Unix-Domain-Socket.h"
#include <sys/socket.h>     //using socket
#include <sys/un.h>         //using struct sockaddr_un
#include <cstring>          //using strncpy
#include <string>

UnixDomainSocket::UnixDomainSocket(const char *socket_path){
    socket_path_ = std::string(socket_path);
    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;
    strncpy(sock_addr_.sun_path + 1, socket_path, sizeof(sock_addr_.sun_path) - 2);
}
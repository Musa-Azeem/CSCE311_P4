#ifndef UNIXDOMAINSOCKET
#define UNIXDOMAINSOCKET

#define SOCKET_BUFFER_SIZE 1024

#include <sys/un.h>
#include <string>
#include <tuple>

class UnixDomainSocket{
    public:
        explicit UnixDomainSocket(const char *socket_path);
        int open_socket();
        int bind_socket();
        int connect_socket();
    private:
        ::sockaddr_un sock_addr_;
        std::string socket_path_;
        int sock_fd;
};

#endif
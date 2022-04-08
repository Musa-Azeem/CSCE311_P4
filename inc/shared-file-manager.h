#ifndef SHARED_FILE_MANAGER_H
#define SHARED_FILE_MANAGER_H

#include <string>
#include <sys/un.h>
#include <semaphore.h>

#define SOCKET_BUFFER_SIZE 1024

class SharedFileManager{
    public:
        SharedFileManager(const std::string sock_name, const std::string sem_name);
    protected:
        ::sockaddr_un sock_addr_;
        // std::string socket_path_;
        int sock_fd;
        char buffer[SOCKET_BUFFER_SIZE];
        const std::string kSemName;
        int handle_error(std::string msg);
        sem_t *sem;
};

#endif
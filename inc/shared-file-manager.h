/*
Written by Musa Azeem
*/
#ifndef SHARED_FILE_MANAGER_H
#define SHARED_FILE_MANAGER_H

#include <string>
#include <sys/un.h>
#include <semaphore.h>

#define SOCKET_BUFFER_SIZE 1024
#define INV "_INVALID_FILE_"

class SharedFileManager{
    public:
        SharedFileManager(const std::string sock_name, const std::string sem_name);
    protected:
        ::sockaddr_un sock_addr_;
        char buffer[SOCKET_BUFFER_SIZE];
        int sock_fd;
        const std::string kSrvBarrierName;
        sem_t *srv_barrier;
        char *file_addr;
        int fd;
        off_t file_size;
        int handle_error(std::string msg);
        int open_and_map_file(const std::string file_path);
};

#endif
#include "../inc/shared-file-manager.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fcntl.h>


SharedFileManager::SharedFileManager(const std::string sock_name, 
                                     const std::string sem_name)
    : kSrvBarrierName(sem_name) {
    // socket_path_ = std::string(sock_name);
    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;
    strncpy(sock_addr_.sun_path + 1, 
            &sock_name[0], 
            sizeof(sock_addr_.sun_path) - 2);
}

int SharedFileManager::handle_error(std::string msg){
    std::cerr << "Error Source: " << msg << std::endl;
    std::cerr << "\t" << strerror(errno) << std::endl;
    exit(errno);
}

int SharedFileManager::open_and_map_file(
        const std::string file_path){
    struct stat f_stats;

    // Open File
    fd = open(&file_path[0], O_RDWR);
    if(fd < 0){
        return -1;
    }

    // Get file size
    if( fstat(fd, &f_stats) < 0 )
        handle_error("Getting file size");
    file_size = f_stats.st_size;

    // Map file to shared memory
    file_addr = static_cast<char *>(
        mmap(nullptr, 
             file_size, 
             PROT_READ | PROT_WRITE,
             MAP_SHARED,
             fd,
             0));
    if(file_addr == MAP_FAILED)
        handle_error("Mapping file to Shared Memory");
    return 1;
}


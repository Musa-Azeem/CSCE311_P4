#include "../inc/shared-file-manager.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <semaphore.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fcntl.h>

SharedFileManager::SharedFileManager(const std::string sock_name, 
                                     const std::string sem_name)
    : kSrvBarrierName(sem_name+"_srv"), kCliBarrierName(sem_name+"_cli") {
    // socket_path_ = std::string(sock_name);
    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;
    strncpy(sock_addr_.sun_path + 1, 
            &sock_name[0], 
            sizeof(sock_addr_.sun_path) - 2);
}

int SharedFileManager::handle_error(std::string msg){
    std::cerr << "Source: " << msg << std::endl;
    std::cerr << "\t" << strerror(errno) << std::endl;
    exit(errno);
}

sem_t *SharedFileManager::setup_named_sem(const std::string sem_name, int flags){
    sem_unlink(&sem_name[0]);
    return sem_open(&sem_name[0],
                    flags,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
                    0);
}

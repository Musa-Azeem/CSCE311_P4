#include "../inc/shared-file-manager.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <cstring>
#include <string>

SharedFileManager::SharedFileManager(const std::string sock_name, const std::string sem_name)
    : kSemName(sem_name) {
    socket_path_ = std::string(sock_name);
    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;
    strncpy(sock_addr_.sun_path + 1, &sock_name[0], sizeof(sock_addr_.sun_path) - 2);
}
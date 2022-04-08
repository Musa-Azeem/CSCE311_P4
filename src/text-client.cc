#include "../inc/text-client.h"
#include <string>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

TextClient::TextClient(const std::string sock_name,
                       const std::string sem_name, 
                       const std::string file_path)
    : SharedFileManager(sock_name, sem_name), kFilePath(file_path) {}

int TextClient::runClient(){
    int success;

    // Open Semaphore
    sem = sem_open(&kSemName[0], 0);
    if(sem == SEM_FAILED)
        return handle_error("Opening semaphore");
    
    // Open Socket
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0)
        return handle_error("Opening Socket");
    
    success = connect(sock_fd,
                      reinterpret_cast<const sockaddr*>(&sock_addr_),
                      sizeof(sock_addr_));
    if(success < 0)
        return handle_error("Connecting to socket");

    // Step 1: Pass filename to server using the socket
    sem_post(sem);
    success = write(sock_fd, &kFilePath[0], kFilePath.size()+1);
    if(success < 0)
        return handle_error("Writing to socket");
    
    // Wait for server to share file to memory
    sem_wait(sem);

    // Step 2: Process file with threads
}
#include "../inc/text-server.h"
#include <string.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <cerrno>
#include <unistd.h>

TextServer::TextServer(const std::string sock_name, 
                       const std::string sem_name)
    : SharedFileManager(sock_name, sem_name) {}

int TextServer::runServer(){
    int success;
    int cli_sock_fd;
    int fd;

    // Step 1: Start Server
    std::cout << "SERVER STARTED" << std::endl;

    // Create semaphore
    sem_unlink(&kSemName[0]);
    sem = sem_open(&kSemName[0], 
                   O_CREAT | O_EXCL, 
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 
                   0);
    if(sem == SEM_FAILED)
        return handle_error("Creating Semaphore");

    // Create and Open Unix Domain Socket to get path
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0)
        return handle_error("Opening socket");
    success = bind(sock_fd, 
                       reinterpret_cast<const sockaddr*>(&sock_addr_),
                       sizeof(sock_addr_));
    if(success < 0){
        return handle_error("Binding Socket");
    }

    // Listen for clients to write to socket
    success = listen(sock_fd, 1);
    if(success < 0)
        return handle_error("Listening for client");

    // Loop waiting for clients
    while(true){
        std::cout << "looped" << std::endl;
        // Step 2: Recieve path from client
        // Wait for client connections
        cli_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(cli_sock_fd < 0)
            return handle_error("Accepting Client Connection");
        
        // Wait for client to write to socket
        sem_wait(sem);

        // Step 2.a: Read path from client
        success = read(cli_sock_fd, buffer, SOCKET_BUFFER_SIZE);
        if(success < 0)
            return handle_error("Reading from Client");
        file_path = buffer;

        std::cout << "CLIENT REQUEST RECEIVED" << std::endl;

        // Step 2.b: Open file and map to shared memory
        std::cout << "\tOpening: " << file_path << std::endl;
        fd = open(&file_path[0], O_RDWR);
        if(fd < 0){
            // Indicate to client that file open failed
            success = write(cli_sock_fd, INV, sizeof(INV));
            if(success < 0)
                return handle_error("Writng to Client");
            sem_post(sem);
            continue;
        }
        std::cout << "not inv" << std::endl;
        sem_post(sem);
    }
}
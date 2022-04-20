/*
Written by Musa Azeem
This file defines the functions of the TextServer class
Functions:
    Constructor         calls parent constructor for sock_name and sem_name
    runServer           runs the server - recieves a file name from client and opens file
    start_socket        creates and binds to a Unix Domain Socket, and starts listening for clients
    setup_named_sem     creates a named semaphore
*/
#include "../inc/text-server.h"
#include <iostream>
#include <string.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

TextServer::TextServer(const std::string sock_name, 
                       const std::string sem_name)
    : SharedFileManager(sock_name, sem_name) {}

int TextServer::runServer(){
    int success;
    int cli_sock_fd;

    // Step 1: Start Server
    std::cout << "SERVER STARTED" << std::endl;

    // Create semaphore
    srv_barrier = setup_named_sem(kSrvBarrierName, O_CREAT | O_EXCL);

    // Create and Open Unix Domain Socket to get path
    sock_fd = start_socket();

    // Loop waiting for clients
    while(true){
        // Step 2: Recieve path from client
        // Wait for client connections
        cli_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(cli_sock_fd < 0)
            handle_error("Accepting Client Connection");
        
        // Step 2.a: Read path from client
        // Wait for client to write
        if( read(cli_sock_fd, buffer, SOCKET_BUFFER_SIZE) < 0)
            handle_error("Reading from Client");
        file_path = buffer;

        std::clog << "CLIENT REQUEST RECEIVED" << std::endl;

        // Step 2.b: Open file and map to shared memory
        std::clog << "\tOPENING: " << file_path << std::endl;

        if( open_and_map_file(file_path) < 0){
            // Indicate to client that file open failed (unblock)
            if( write(cli_sock_fd, INV, sizeof(INV)) < 0 )
                handle_error("Writing INV to Client");
            continue;
        }
        std::clog << "\tFILE MAPPED TO SHARED MEMORY" << std::endl;

        // Unblock client by writing to socket if file open succeeded
        if( write(cli_sock_fd, "\004", sizeof(char)) < 0 )
            handle_error("Writing to Client");

        // Wait for client to finish processing before closing and unmapping
        sem_wait(srv_barrier);

        // Unmap
        if (munmap(file_addr, file_size) < 0)
            handle_error("Unmapping File");

        // Close file
        if (close(fd) < 0)
            handle_error("Closing File");
        std::clog << "\tFILE CLOSED" << std::endl;

    }   // Step 3: Loop again waiting for clients
} // runServer

int TextServer::start_socket(){
    int ret_fd;
    int success;
    ret_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(ret_fd < 0)
        handle_error("Opening Socket");
    success = bind(ret_fd, 
                   reinterpret_cast<const sockaddr*>(&sock_addr_),
                   sizeof(sock_addr_));
    if(success < 0)
        handle_error("Binding Socket");
    if ( listen(ret_fd, 1) < 0 )
        handle_error("Listening for Client");
    return ret_fd;
}

sem_t *TextServer::setup_named_sem(const std::string sem_name, 
                                          const int flags){
    sem_unlink(&sem_name[0]);
    sem_t *ret = sem_open(&sem_name[0],
                          flags,
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
                          0);
    if(ret == SEM_FAILED)
        handle_error("Creating Semaphore");
    return ret;
}
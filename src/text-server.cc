#include "../inc/text-server.h"
#include <string.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <cerrno>
#include <unistd.h>

using std::cout;
using std::endl;

TextServer::TextServer(const std::string sock_name, 
                       const std::string sem_name)
    : SharedFileManager(sock_name, sem_name) {}

int TextServer::runServer(){
    int success;
    int cli_sock_fd;
    int fd;
    off_t file_size;
    // struct stat file_stats;
    char *file_addr;

    // Step 1: Start Server
    std::cout << "SERVER STARTED" << std::endl;

    // Create semaphore
    cli_barrier = setup_named_sem(kCliBarrierName, O_CREAT | O_EXCL);
    if(cli_barrier == SEM_FAILED)
        handle_error("Creating Semaphore");

    // Create and Open Unix Domain Socket to get path
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0)
        handle_error("Opening socket");
    success = bind(sock_fd, 
                       reinterpret_cast<const sockaddr*>(&sock_addr_),
                       sizeof(sock_addr_));
    if(success < 0){
        handle_error("Binding Socket");
    }

    // Listen for clients to write to socket
    if( listen(sock_fd, 1) < 0)
        handle_error("Listening for client");

    // Loop waiting for clients
    while(true){
        // Step 2: Recieve path from client
        // Wait for client connections
        cli_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(cli_sock_fd < 0)
            handle_error("Accepting Client Connection");
        
        // Step 2.a: Read path from client
        if( read(cli_sock_fd, buffer, SOCKET_BUFFER_SIZE) < 0)
            handle_error("Reading from Client");
        file_path = buffer;

        std::clog << "CLIENT REQUEST RECEIVED" << std::endl;

        // Step 2.b: Open file and map to shared memory
        std::clog << "\tOpening: " << file_path << std::endl;
        std::tie(fd, file_size, file_addr) = open_and_map_file(file_path);
        if(fd < 0){
            // Indicate to client that file open failed
            if( write(cli_sock_fd, INV, sizeof(INV)) < 0 )
                handle_error("Writing INV to Client");
            continue;
        }
        std::clog << "\tFILE MAPPED TO SHARED MEMORY" << std::endl;

        // Indicate to client that file open succeeded
        if( write(cli_sock_fd, "\004", sizeof(char)) < 0 )
            handle_error("Writing to Client");

        // Wait for client to finish processing before closing and unmapping
        
        // Unmap

        // Close file
        if (close(fd) < 0)
            handle_error("Closing File");
        std::clog << "\tFILE CLOSED" << std::endl;

        // Unblock Client
        sem_post(cli_barrier);

    }   // Step 3: Loop again waiting for clients
}
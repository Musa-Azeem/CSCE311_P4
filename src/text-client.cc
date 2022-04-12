#include "../inc/text-client.h"
#include <string>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

using std::cout;
using std::endl;

TextClient::TextClient(const std::string sock_name,
                       const std::string sem_name, 
                       const std::string file_path)
    : SharedFileManager(sock_name, sem_name), kFilePath(file_path) {}

int TextClient::runClient(){
    int success;
    int fd;
    std::string check_inv;
    struct stat file_stats;

    // Open Semaphore
    cli_barrier = sem_open(&kCliBarrierName[0], 0);
    if(cli_barrier == SEM_FAILED)
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
    if( write(sock_fd, &kFilePath[0], kFilePath.size()+1) < 0)
        return handle_error("Writing to socket");
    
    // Step 3: Check if sever was unable to open file
    // Read socket to check if invalid file
    if( read(sock_fd, buffer, SOCKET_BUFFER_SIZE) < 0)
        return handle_error("Reading from Server");
    check_inv = buffer;
    if(check_inv.find(INV) != std::string::npos){
        std::cerr << "INVALID FILE" << std::endl;
        return -1;
    }

    // Wait for server to share file to memory
    sem_wait(cli_barrier);
    // Step 2: Process file with threads
    // Open file
    // fd = open(&kFilePath[0], O_RDWR);
    // if (fd < 0)
        // return handle_error("Opening file");
    // Step 4: Return 1 to prompt main to return 0
    return 1;
}
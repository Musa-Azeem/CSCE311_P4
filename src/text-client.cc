/*
Written by Musa Azeem
This file defines the functions for the TextClient Class
Functions:
    Constructor         initializes kFilePath and calls parent constructor for sock_name and sem_name
    runClient           runs the client - passes server a filename, waits for server, and then processes file
    file_to_upper       prepares and calls threads to each process a portion of the file
    threaded_to_upper   function run by threads to convert a section of a file to uppercase
    connect_socket      opens and connects client to an existing Unix Domain Socket
*/
#include "../inc/text-client.h"
#include "../inc/thread-args.h"
#include <iostream>
#include <string>
#include <semaphore.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <vector>

TextClient::TextClient(const std::string sock_name,
                       const std::string sem_name, 
                       const std::string file_path)
    : SharedFileManager(sock_name, sem_name), kFilePath(file_path) {}

int TextClient::runClient(){
    int success;
    std::string check_inv;

    // Open Semaphore
    srv_barrier = sem_open(&kSrvBarrierName[0], 0);
    if(srv_barrier == SEM_FAILED)
        return handle_error("Opening Server semaphore");

    // Open Socket
    sock_fd = connect_socket();

    // Step 1: Pass filename to server using a socket
    // Unblock server by writing
    if( write(sock_fd, &kFilePath[0], kFilePath.size()+1) < 0 )
        return handle_error("Writing to socket");
    
    // Wait for server to write to socket
    if( read(sock_fd, buffer, SOCKET_BUFFER_SIZE) < 0 )
        return handle_error("Reading from Server");
    
    // Step 3: Check if sever was unable to open file
    check_inv = buffer;
    if(check_inv.find(INV) != std::string::npos){
        std::cerr << INV_MSG << std::endl;
        return -1;
    }

    // Step 2: Process file with threads
    // Open file
    if( open_and_map_file(kFilePath) < 0)
        handle_error("Opening File");

    // create and run threads
    file_to_upper();

    // Unmap
    if (munmap(file_addr, file_size) < 0)
        handle_error("Unmapping File");
    // Close file
    if (close(fd) < 0)
        handle_error("Closing File");

    // Unblock Server
    sem_post(srv_barrier);

    // Step 4: Return 1 to prompt main to return 0
    return 1;
}// runClient

int TextClient::file_to_upper(){
    std::vector<pthread_t> threads(N_THREADS);
    std::vector<ThreadArgs> args(N_THREADS);
    off_t start_idx;
    off_t stop_idx;
    for(int i=0; i<threads.size(); i++){
        start_idx = i * (file_size/N_THREADS);
        stop_idx = start_idx + file_size/N_THREADS;
        if(i==N_THREADS-1)
            // if last thread, go until end of file to get last few lines
            stop_idx = file_size;
        args[i] = {this, start_idx, stop_idx};
        int success = pthread_create(&threads[i], 
                                     nullptr, 
                                     threaded_to_upper, 
                                     static_cast<void *>(&args[i]));
        if(success < 0){
            handle_error("Creating Thread "+i);
        }
    }
    for(auto thread : threads){
        if (pthread_join(thread, nullptr) < 0)
            handle_error("Thread joining");
    }
    return 1;
}//file_to_upper

void *TextClient::threaded_to_upper(void *thread_args){
    ThreadArgs args = *static_cast<ThreadArgs*>(thread_args);
    for(int i=args.start_idx; i<args.stop_idx; i++)
        // Use toupper to convert each character in file to uppercase
        args.cli->file_addr[i] = toupper(args.cli->file_addr[i]);
    return nullptr;
}

int TextClient::connect_socket(){
    int ret_fd;
    int success;
    ret_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(ret_fd < 0)
        handle_error("Opening Socket");
    success = connect(ret_fd,
                      reinterpret_cast<const sockaddr*>(&sock_addr_),
                      sizeof(sock_addr_));
    if(success < 0)
        return handle_error("Connecting to socket");
    return ret_fd;
}
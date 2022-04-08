#include "../inc/text-server.h"
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <iostream>
#include <cerrno>

TextServer::TextServer(const std::string sock_name, 
                       const std::string sem_name)
    : SharedFileManager(sock_name, sem_name) {}

int TextServer::runServer(){
    // Create semaphores
    sem_unlink(&kSemName[0]);
    sem = sem_open(&kSemName[0], 
                   O_CREAT | O_EXCL, 
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 
                   0);
    if(sem == SEM_FAILED){
        return handle_error("Creating Semaphore");
    }
    // Create and Open Unix Domain Socket to get path

    //set up sock
}
#include "../inc/text-server.h"
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <iostream>
#include <cerrno>

TextServer::TextServer(std::string sem_name)
    : kSemName(sem_name) 
    {}

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

    // wait for client
    sem_wait(sem);
}

int TextServer::handle_error(std::string msg){
    std::cerr << "Source:" << msg << std::endl;
    std::cerr << "\t" << ::strerror(errno) << std::endl;
    return(errno);
}
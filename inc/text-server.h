/*
Written by Musa Azeem
This file defines the TextServer class, which inherits form SharedFileManager
Class Variables:
    file_path       file name and path to open
*/
#ifndef TEXT_SERVER_H
#define TEXT_SERVER_H

#include "../inc/shared-file-manager.h"
#include <string>
#include <semaphore.h>

class TextServer: SharedFileManager{
    public:
        TextServer(const std::string sock_name, 
                   const std::string sem_name);
        int runServer();
    private:
        std::string file_path;
        int start_socket();
        sem_t *setup_named_sem(const std::string sem_name, const int flags);
};

#endif
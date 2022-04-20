/*
Written by Musa Azeem
This file defines the TextClient class, which inherites the SharedFileManager class
Class Variables:
    kFilePath       file name and path to process
*/
#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include "../inc/shared-file-manager.h"
#include <string>

#define N_THREADS 4
#define INV_MSG "INVALID FILE"

class TextClient: SharedFileManager{
    public:
        TextClient(const std::string sock_name, 
                   const std::string sem_name, 
                   const std::string file_path);
        int runClient();
    private:
        const std::string kFilePath;
        static void *threaded_to_upper(void *thread_args);
        int file_to_upper();
        int connect_socket();
};

#endif
#ifndef TEXT_SERVER_H
#define TEXT_SERVER_H

#include "../inc/shared-file-manager.h"
#include <string>

class TextServer: SharedFileManager{
    public:
        TextServer(const std::string sock_name, 
                   const std::string sem_name);
        int runServer();
    private:
        const std::string kSemName;
};

#endif
#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include "../inc/shared-file-manager.h"
#include <string>

class TextClient: SharedFileManager{
    public:
        TextClient(const std::string sock_name, std::string sem_name, std::string file_path);
        int runClient();
    private:
        const std::string kFilePath;
};

#endif
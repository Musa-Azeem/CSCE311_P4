#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include <string>

class TextClient{
    public:
        TextClient(std::string shm_name, std::string sem_name, std::string file_path);
        int runClient();
    private:
        const std::string kSemName;
        const std::string kShmName;
        const std::string kFilePath;
};

#endif
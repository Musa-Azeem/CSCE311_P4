#ifndef TEXT_CLIENT_H
#define TEXT_CLIENT_H

#include <string>

class TextClient{
    public:
        TextClient(std::string sem_name, std::string file_path);
        int runClient();
    private:
        const std::string kFilePath;
        const std::string kSemName;

};

#endif
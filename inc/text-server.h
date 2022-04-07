#ifndef TEXT_SERVER_H
#define TEXT_SERVER_H

#include <string>

class TextServer{
    public:
        TextServer(std::string sem_name);
        int runServer();
    private:
        const std::string kSemName;
        sem_t *sem;
        int handle_error(std::string msg);
};

#endif
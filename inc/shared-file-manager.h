#ifndef SHARED_FILE_MANAGER_H
#define SHARED_FILE_MANAGER_H

#include <string>

class SharedFileManager{
    public:
        SharedFileManager(std::string sem_name): sem_name(sem_name);
    protected:
        const std::string sem_name;
}

#endif
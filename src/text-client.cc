#include "../inc/text-client.h"
#include <string>
#include <semaphore.h>


TextClient::TextClient(std::string sem_name, std::string file_path)
    : kSemName(sem_name), kFilePath(file_path)
    {}

int TextClient::runClient(){
    
}
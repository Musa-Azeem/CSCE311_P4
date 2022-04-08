#include "../inc/text-client.h"
#include <string>
#include <semaphore.h>


TextClient::TextClient(const std::string sock_name,
                       const std::string sem_name, 
                       const std::string file_path)
    : SharedFileManager(sock_name, sem_name), kFilePath(file_path) {}

int TextClient::runClient(){
    // set up sem and sock
}
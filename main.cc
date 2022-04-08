#include <iostream>
#include <string.h>
#include "inc/text-client.h"
#include "inc/text-server.h"
#include "inc/ipc-names.h"

#define SERVER_EXE "./text-server"
#define CLIENT_EXE "./text-client"

namespace main_srv{
    int main(int argc, char **argv){
        if(argc != 1){
            std::cout << "usage: ./text-server" << std::endl; 
            exit(1);
        }
        TextServer srv(SOCK_NAME, SEM_NAME);
        srv.runServer();
        return 0;
    }
}
namespace main_cli{
    int main(int argc, char **argv){
        if(argc != 2){
            std::cout << "usage: ./text-client [file-path]" << std::endl; 
            exit(1);
        }
        TextClient cli(SOCK_NAME, SEM_NAME, argv[1]);
        cli.runClient();
        return 0;
    }
}

int main(int argc, char **argv){
    if(strcmp(argv[0], SERVER_EXE) == 0)
        return main_srv::main(argc, argv);
    if(strcmp(argv[0], CLIENT_EXE) == 0)
        return main_cli::main(argc, argv);
}

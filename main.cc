#include <iostream>
#include <string.h>
#include "inc/text-client.h"
#include "inc/text-server.h"
#include "inc/ipc-names.h"

#define SRV_EXE "./text-server"
#define CLI_EXE "./text-client"

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
        if (cli.runClient() > 0)
            return 0;
        else
            return 1;
    }
}

int main(int argc, char **argv){
    if(strcmp(argv[0], SRV_EXE) == 0)
        return main_srv::main(argc, argv);
    if(strcmp(argv[0], CLI_EXE) == 0)
        return main_cli::main(argc, argv);
}

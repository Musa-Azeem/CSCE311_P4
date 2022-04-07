#include <iostream>
#include <string.h>

#define SERVER_EXE "./text-server"
#define CLIENT_EXE "./text-client"

using std::cout;
using std::endl;

namespace main_srv{
    int main(int argc, char **argv){
        if(argc != 1){
            cout << "usage: ./text-server" << endl; 
            exit(1);
        }
        // TODO server
        return 0;
    }
}
namespace main_cli{
    int main(int argc, char **argv){
        if(argc != 2){
            cout << "usage: ./text-client [file-path]" << endl; 
            exit(1);
        }
        // TODO client
        return 0;
    }
}

int main(int argc, char **argv){
    if(strcmp(argv[0], SERVER_EXE) == 0)
        return main_srv::main(argc, argv);
    if(strcmp(argv[0], CLIENT_EXE) == 0)
        return main_cli::main(argc, argv);
}

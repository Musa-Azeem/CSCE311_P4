# CSCE311 Project 4

## Directory Structure
```
├── makefile
├── README.md
├── main.cc
├── inc
│   ├── shared-file-manager.h
│   ├── text-server.h
│   ├── text-client.h
│   ├── thread-args.h
│   └── ipc-names.h
└── src
    ├── shared-file-manager.cc
    ├── text-server.cc
    └── text-client.cc
```

## The following objects are defined in this directory:

    SharedFileManager
    ThreadArgs
    TextClient
    TextServer

The `inc` folder contains all headers for the classes

The `src` folder contains all source codes

## Objects

### SharedFileManager
- This class serves as the parent class for TextServer and TextClient, defining the attribtues and functions shared by both.
- This class is defined in the files `inc/shared-file-manager.h` and `src/shared-file-manager.cc`
- This class is included in `text-server.h` and `text-client.h`

### TextServer
- This class defines a Shared File server
- Clients connect to this server, providing a file path
- The server then opens the file, pulling it into the page cache, and signals the client when completed
- This class is defined in the files `inc/text-server.h` and `src/text-server.cc`
- This class is included in `main.cc`

### TextClient
- This class defines a Shared File client
- Clients send the server a file path for the server to open, opens the file itself, and uses threads to convert all characters in the file to uppercase
- This class is defined in the files `inc/text-client.h` and `src/text-client.cc`
- This class is included in `main.cc`

### ThreadArgs
- This struct is used to pass the necessary arguments to the threaded function of TextClient
- This struct is defined in the file `inc/thread-args.h`
- This struct is included in `src/text-client.cc`

## Main Method
- The main method is defined in the file `main.cc`
- It runs either the server or the client, based on the name of the executable

#### Server Main Method
- This main method creates and runs a Shared File server using the `TextServer` class
- It is defined in the file `src/main.cc` in the `main_srv` namespace

#### Client Main Method
- This main method creates and runs a Shared Memory client using the `TextClient` class
- It is given a file path as a command line argument
- It is defined in the file `src/main.cc` in the `main_cli` namespace

## Other files
- `inc/ipcnames.h` defines a name for a Unix Domain Socket and named semaphore locations that are included in `main.cc`
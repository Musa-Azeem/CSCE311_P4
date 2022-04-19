/*
Written by Musa Azeem
This file defines ipc locations shared between the text-client and text-server
Definitions:
    SEM_NAME    location for first named semaphore used in TextClient and TextServer classes
    SOCK_NAME   location for unix domain socket used in TextClient and TextServer classes
*/
#ifndef IPC_NAMES_H
#define IPC_NAMES_H

#define SEM_NAME "/csce311_p4_semaphore"
#define SOCK_NAME "/csce311_p4_socket"

#endif

/*
Written by Musa Azeem
This file defines the struct ThreadArgs, which contains the arguments passed to threads
Variables:
    cli         an instance of a TextClient
    start_idx   index at which to start file processing
    stop_idx    index at which to stop file processing
*/
#ifndef THREAD_ARGS_H
#define THREAD_ARGS_H

#include "text-client.h"

struct ThreadArgs{
    TextClient *cli;
    off_t start_idx;
    off_t stop_idx;
};
#endif
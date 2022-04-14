#ifndef THREAD_ARGS_H
#define THREAD_ARGS_H

#include "text-client.h"

struct ThreadArgs{
    TextClient *cli;
    off_t start_idx;
    off_t stop_idx;
};
#endif
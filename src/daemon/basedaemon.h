#ifndef __BASEDAEMON__H
#define __BASEDAEMON__H

#include <exception>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string>
// Open
#include <fcntl.h>
//ofstream
#include <fstream>
//remove
#include <cstdlib>
#include "logger/logger.h"

class BaseDaemon {
protected:
    bool is_daemon;
    void (*signal_handler_ptr)(int);
    char * name;
public:
    BaseDaemon(){signal_handler_ptr = BaseDaemon::signal_handler;};
    BaseDaemon(char * name){};
    ~BaseDaemon(){};
    int daemonize();
    static void signal_handler(int signal);
    void finish_daemon();
    int run(){return 0;};
};

#endif
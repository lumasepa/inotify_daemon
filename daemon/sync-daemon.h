#ifndef __SYNC_DAEMON__H
#define __SYNC_DAEMON__H

#include <string>

#include "logger.h"
#include "basedaemon.h"
#include "inotify-cxx.h"

class SyncDaemon : public BaseDaemon
{
private:
    std::string * watch_dir;
public:
    SyncDaemon(char * name, char * dir);
    ~SyncDaemon(){ this->finish_daemon(); }
    int run();
    static void signal_handler(int signal);
    void * file_changed(void *);
};

#endif
#ifndef __SYNC_DAEMON__H
#define __SYNC_DAEMON__H

#include <string>

#include "logger/logger.h"
#include "basedaemon.h"
#include "inotify/inotify-cxx.h"

class SyncDaemon : public BaseDaemon
{
private:
    std::string * watch_dir;
    static constexpr char * daemon_name = const_cast<char *>("inotify_daemon");
public:
    SyncDaemon(char * dir);
    ~SyncDaemon(){ this->finish_daemon(); }
    int run();
    static void signal_handler(int signal);
    void * file_changed(void *);
};

#endif
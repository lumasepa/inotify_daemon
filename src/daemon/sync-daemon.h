#ifndef __SYNC_DAEMON__H
#define __SYNC_DAEMON__H

#include <string>

#include "logger/logger.h"
#include "basedaemon.h"
#include "inotify/inotify-cxx.h"
#include <ftw.h>
#include <vector>


class SyncDaemon : public BaseDaemon
{
private:
    std::string * watch_dir;
    static constexpr char * daemon_name = const_cast<char *>("inotify_daemon");
    std::vector<std::string> * directories_to_watch;
public:
    SyncDaemon(char * dir);
    ~SyncDaemon(){ this->finish_daemon(); }
    int run();
    static void signal_handler(int signal);
    void * file_changed(void *);
    int get_all_sub_directories();
};

#endif
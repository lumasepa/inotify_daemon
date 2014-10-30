#include <iostream>

using namespace std;

#include <vector>
#include <fstream>

#include "daemon/sync-daemon.h"
#include "daemon/options/options.h"
#include "daemon/logger/logger.h"
#include <unistd.h>


int main(int argc, char ** argv)
{
    SyncDaemon * syncDaemon = NULL;

    Options options = Options();
    options.log_file = std::string("/var/log/") + std::string("inotify_daemon") + ".log";
    options.daemon = false;
    options.watch_path = "";
    options.log_level = DEBUG;
    options.parseopts(argc, argv);

    if (getuid() != 0)
    {
        std::cout << "inotify_daemon should run as root" << std::endl;
        exit(10);
    }

    std::ofstream * log = new std::ofstream();

    log->open(options.log_file, std::ofstream::out | std::ofstream::app);

    if (! log->is_open() || log->bad()){
        std::cout << "Error opening log " << options.log_file << std::endl;
        exit(24);
    } else {
        std::cout << "Opened log " << options.log_file << std::endl;
    }

    logger.set_stream(log);
    logger.set_level(INFO);


    syncDaemon = new SyncDaemon(const_cast<char*>(options.watch_path.c_str()));
    if (options.daemon) {
        std::cout << "Daemonizing ... " << std::endl;
        syncDaemon->daemonize();
    }
    int ret = syncDaemon->run();

    return ret;

}



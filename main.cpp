#include <iostream>

using namespace std;

#include <string.h>
#include <vector>
#include <fstream>

#include "daemon/sync-daemon.h"
#include "daemon/logger.h"


int main(int argc, char ** argv)
{
    std::ofstream * log = new std::ofstream();
    log->open(std::string("/home/luma/") + std::string("inotify_daemon") + ".log",  std::ofstream::out | std::ofstream::app);
    if (! log->is_open() || log->bad()){
        std::cout << "Error opening log " << std::string("/var/log/") + std::string("inotify_daemon") + ".log" << std::endl;
    }
    logger.set_stream(log);


    bool daemon = false;
    std::string watch_path;
    SyncDaemon * syncDaemon = NULL;

    if(argc >= 2)
    {
        for(int i = 1; i < argc; ++i)
        {
            if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-?") == 0)
            {
                std::cout << argv[0] << std::endl;
                std::cout << "inotify daemonized" << std::endl;
                std::cout << "[-p | --path] path to watch inotify" << std::endl;
                std::cout << "[-d | --daemon] start as daemon" << std::endl;
                std::cout << "[-h | --help | -?] shows the help" << std::endl;
                exit(0);
            }
            else if( strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--daemon") == 0)
            {
                daemon = true;
            }
            else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--path") == 0)
            {
                watch_path = std::string(argv[++i]);
            }
            else
            {
                std::cout << "Parameter " << argv[i] << " incorrect" << std::endl;
                std::cout << argv[0] << " [-h | --help | -?] for see the help" << std::endl;
                exit(0);
            }
        }
    }
    syncDaemon = new SyncDaemon(const_cast<char*>("inotify_daemon"), const_cast<char*>(watch_path.c_str()));
    if (daemon) {
        std::cout << "Daemonizing ... " << std::endl;
        syncDaemon->daemonize();
    }
    int ret = syncDaemon->run();

    return ret;

}



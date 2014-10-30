#include "options.h"
#include <string.h>
#include <iostream>
#include "../logger/logger.h"



void Options::parseopts(int argc, char ** argv){

    for(int i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-?") == 0) {
            std::cout << argv[0] << std::endl;
            std::cout << "inotify daemonized" << std::endl;
            std::cout << "[[-p | --path] path] set the path to watch inotify" << std::endl;
            std::cout << "[-d | --daemon] start as daemon" << std::endl;
            std::cout << "[[-lf | --log_file] file ] set log file" << std::endl;
            std::cout << "[[-l | --log_level] [debug | info | warning | error]] set log level" << std::endl;
            std::cout << "[-h | --help | -?] shows the help" << std::endl;
            exit(10);
        }
        else if( strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--daemon") == 0) {
            this->daemon = true;
        }
        else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--path") == 0) {
            this->watch_path = std::string(argv[++i]);
        }
        else if(strcmp(argv[i], "-lf") == 0 || strcmp(argv[i], "--log_file") == 0) {
            this->log_file = std::string(argv[++i]);
        }
        else if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log_level") == 0) {
            char * log_level = argv[++i];
            if(strcmp(log_level, "debug") == 0){
                this->log_level = DEBUG;
            } else if(strcmp(log_level, "info") == 0){
                this->log_level = INFO;
            } else if(strcmp(log_level, "warning") == 0){
                this->log_level = WARNING;
            } else if(strcmp(log_level, "error") == 0){
                this->log_level = ERROR;
            } else {
                std::cout << "log level " << argv[++i] << " erroneo" << std::endl;
                std::cout << "log levels : debug, info, warning, error" << std::endl;
                std::cout << "[-h | --help | -?] for see the help" << std::endl;
                exit(10);
            }
        }
        else
        {
            std::cout << "Parameter " << argv[i] << " incorrect" << std::endl;
            std::cout << argv[0] << " [-h | --help | -?] for see the help" << std::endl;
            exit(10);
        }
    }
    if (this->watch_path == ""){
        std::cout << "Error : Watch path not set" << std::endl;
        std::cout << argv[0] << " [-h | --help | -?] for see the help" << std::endl;
    }
}
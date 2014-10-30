#ifndef __OPTIONS__H
#define __OPTIONS__H

#include <string>

class Options{
public:
    bool daemon;
    std::string watch_path;
    std::string log_file;
    int log_level;

public:
    Options() : log_file(std::string("")), log_level(0), daemon(false), watch_path(std::string("")) {}
    void parseopts(int argc, char **argv);
};

#endif
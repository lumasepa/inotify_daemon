#ifndef __LOGGER__H
#define __LOGGER__H

#include <syslog.h>
#include <ostream>
#include <iostream>
#include <ctime>

#define logger (*Logger::getInstance())
#define lend std::endl

#define DEBUG 1
#define INFO 2
#define WARNING 3
#define ERROR 4


class Logger
{
private:
    static Logger * instance;
    std::ostream * stream;
    std::ostream * null_stream;
    int log_level;

protected:
    Logger();
    Logger(Logger const&);
    Logger& operator=(Logger const&);

    char * formated_time();

public:
    static Logger* getInstance()
    {
        static Logger *instance = new Logger();
        return instance;
    }
    virtual ~Logger(){};
    void set_level(int level);
    std::ostream& set_stream(std::ostream * ostream);
    std::ostream& debug();
    std::ostream& info();
    std::ostream& warning();
    std::ostream& error();

};

#endif
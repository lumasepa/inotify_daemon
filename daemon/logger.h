#ifndef __LOGGER__H
#define __LOGGER__H

#include <syslog.h>
#include <ostream>
#include <iostream>
#include <ctime>

#define logger (*Logger::getInstance())
#define lend std::endl

class Logger
{
private:
    static Logger * instance;
    std::ostream * stream;

protected:
    Logger() { stream = &std::cout; std::cout << "Creating logger" << std::endl; };
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

    std::ostream& set_stream(std::ostream * ostream);
    std::ostream& debug();
    std::ostream& info();
    std::ostream& warning();
    std::ostream& error();

};

#endif
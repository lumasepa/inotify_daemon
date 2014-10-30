#include <signal.h>
#include <string.h>
#include "basedaemon.h"


int BaseDaemon::daemonize()
{
    is_daemon = true;
    pid_t pid;
    logger.debug() << "Forking the process ..." << lend;
    pid = fork();

    if (pid < 0) // Error forking
    {
        std::cerr << strerror(errno) << lend;
        exit(10);
    }else if (pid > 0) // Father
    {
        exit(0);
    }

    logger.debug() << "Creating session ..." << lend;
    if (setsid() < 0) {
        logger.error() << "It was't possible create a new session" << lend;
        exit(11);
    }

    logger.debug() << "Changing directory to / ..." << lend;
    if ((chdir("/")) < 0) {
        logger.error() << "It was't possible change directory to /" << lend;
        exit(12);
    }

    logger.debug() << "Clossing standar file descriptors ..." << lend;
    close(STDIN_FILENO); // fd 0
    close(STDOUT_FILENO); // fd 1
    close(STDERR_FILENO); // fd 2

    logger.debug() << "Opening standar file descriptors to /dev/null ..." << lend;
    int fd0 = open("/dev/null", O_RDONLY); // fd0 == 0
    int fd1 = open("/dev/null", O_WRONLY); // fd1 == 1
    int fd2 = open("/dev/null", O_WRONLY); // fd2 == 2

    logger.debug() << "Changing umask ..." << lend;
    umask(0);

    logger.debug() << "Catching signals ..." << lend;
    for(int i = 1; i <= 31;++i){
        signal(i,*signal_handler_ptr);
    }

    logger.debug() << "Daemon initialized suscefuly" << lend;

    return 0;
}

void BaseDaemon::signal_handler(int signal){
    logger.error() << "Signal catched in BaseDaemon !!!!!" << lend;
}

void BaseDaemon::finish_daemon(){
    if (this->is_daemon) {
        logger.debug() << "Deleting file " << std::string("/var/run/") + this->name + ".pid" << "..." << lend;
        remove((std::string("/var/run/") + this->name + ".pid").c_str());
    }
}

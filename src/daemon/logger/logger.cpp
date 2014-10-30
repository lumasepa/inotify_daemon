#include "logger.h"
#include <fstream>

char * Logger::formated_time() {
    time_t rawtime;
    time (&rawtime);
    std::string time(asctime(localtime(&rawtime)));
    return const_cast<char*>(time.substr(0, time.length()-6).c_str());
}

std::ostream& Logger::set_stream(std::ostream * ostream) {
    this->stream = ostream;
    return (*ostream);
}

std::ostream& Logger::debug(){
    if (this->log_level == DEBUG) {
        return (*stream) << "[" << this->formated_time() << "] [DEBUG] : ";
    } else {
        return (*null_stream);
    }
}

std::ostream& Logger::info(){
    if (this->log_level <= INFO) {
        return (*stream) << "[" << this->formated_time() << "] [INFO] : ";
    } else {
        return (*null_stream);
    }
}

std::ostream& Logger::warning(){
    if (this->log_level <= WARNING) {
        return (*stream) << "[" << this->formated_time() << "] [WARNING] : ";
    } else {
        return (*null_stream);
    }
}

std::ostream& Logger::error(){
    if (this->log_level <= ERROR) {
        return (*stream) << "[" << this->formated_time() << "] [ERROR] : ";
    } else {
        return (*null_stream);
    }
}

void Logger::set_level(int level) {
    this->log_level = level;
}

Logger::Logger() {
    stream = &std::cout;
    null_stream = new std::ofstream("/dev/null", std::ofstream::out | std::ofstream::app);
    std::cout << "Creating logger" << std::endl;
}

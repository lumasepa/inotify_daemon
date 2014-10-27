#include "logger.h"

char * Logger::formated_time() {
    time_t rawtime;
    time (&rawtime);
    std::string time(asctime(localtime(&rawtime)));
    return const_cast<char*>(time.substr(0, time.length()-6).c_str());
}

std::ostream& Logger::set_stream(std::ostream * ostream) {
    this->stream = ostream;
}

std::ostream& Logger::debug(){
    return (*stream) << "[" << this->formated_time() << "] [DEBUG] : ";
}

std::ostream& Logger::info(){
    return (*stream) << "[" << this->formated_time() << "] [INFO] : ";
}

std::ostream& Logger::warning(){
    return (*stream) << "[" << this->formated_time() << "] [WARNING] : ";
}

std::ostream& Logger::error(){
    return (*stream) << "[" << this->formated_time() << "] [ERROR] : ";
}

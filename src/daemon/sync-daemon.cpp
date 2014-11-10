#include "sync-daemon.h"
#include <sys/signal.h>


// This is the unique way to access to the vector in the callback function
std::vector<std::string> * global_directories_to_watch;

SyncDaemon::SyncDaemon(char *dir) {
    watch_dir = new std::string(dir);
    is_daemon = true;
    signal_handler_ptr = SyncDaemon::signal_handler;
    name = const_cast<char*>(SyncDaemon::daemon_name);
    directories_to_watch = new std::vector<std::string>();
}


int SyncDaemon::run() {
    try {
        Inotify notify;

        this->get_all_sub_directories();

        for (auto item : *(directories_to_watch)) {
            InotifyWatch watch(item.c_str(), IN_ALL_EVENTS);
            notify.Add(watch);
            logger.info() << "Watching directory " << item << lend;
        }


        for (;;) {
            notify.WaitForEvents();

            for (size_t i = notify.GetEventCount(); i > 0; --i) {
                InotifyEvent * event = new InotifyEvent();
                bool got_event = notify.GetEvent(event);

                if (got_event) {
                    this->file_changed(event);
                }
            }
        }
    } catch (InotifyException &e) {
        logger.error() << "Inotify exception occured: " << e.GetMessage() << lend;
    } catch (std::exception &e) {
        logger.error() << "STL exception occured: " << e.what() << lend;
    } catch (...) {
        logger.error() << "Unknown exception occured" << lend;
    }

    return 0;
}

void * SyncDaemon::file_changed(void * file_event) {
    InotifyEvent * event = reinterpret_cast<InotifyEvent*>(file_event);
    std::string mask_str;
    event->DumpTypes(mask_str);

    std::string filename = event->GetName();

    logger.info() << "event mask: \"" << mask_str << "\"" << lend;
    logger.info() << "filename: \"" << filename << "\"" << lend;
}

void SyncDaemon::signal_handler(int signal) {
    switch(signal) {
        case SIGHUP:
            logger.info() << "hangup signal catched" << lend;
            break;
        case SIGTERM:
            logger.info() << "terminate signal catched" << lend;
            logger.debug() << "Deleting file " << std::string("/var/run/") + SyncDaemon::daemon_name + ".pid" << " ..." << lend;
            remove((std::string("/var/run/") + SyncDaemon::daemon_name + ".pid").c_str());
            exit(0);
            break;
        default:
            logger.info() << "signal " << signal << " catched" << lend;
            logger.debug() << "Deleting file " << std::string("/var/run/") + SyncDaemon::daemon_name + ".pid" << " ..." << lend;
            remove((std::string("/var/run/") + SyncDaemon::daemon_name + ".pid").c_str());
            exit(0);
            break;
    }
}


int add_subdirectory(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_D){
        global_directories_to_watch->push_back(std::string(fpath));
    }
    return 0;
}

int SyncDaemon::get_all_sub_directories() {
    global_directories_to_watch = directories_to_watch;
    ftw(watch_dir->c_str(),add_subdirectory,1);
    global_directories_to_watch = NULL;
}
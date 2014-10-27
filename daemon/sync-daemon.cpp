#include "sync-daemon.h"
#include <sys/signal.h>

SyncDaemon::SyncDaemon(char *name, char *dir) {
    watch_dir = new std::string(dir);
    daemon_name = name;
    is_daemon = true;
    signal_handler_ptr = SyncDaemon::signal_handler;
}


int SyncDaemon::run() {
    try {
        Inotify notify;

        InotifyWatch watch(*watch_dir, IN_ALL_EVENTS);
        notify.Add(watch);

        logger.info() << "Watching directory " << *watch_dir << lend;
        for (;;) {
            notify.WaitForEvents();

            size_t count = notify.GetEventCount();
            while (count > 0) {
                InotifyEvent * event = new InotifyEvent();
                bool got_event = notify.GetEvent(event);

                if (got_event) {
                    this->file_changed(event);
                }

                count--;
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
            exit(0);
            break;
        default:
            logger.info() << "signal " << signal << " catched" << lend;
            break;
    }
}

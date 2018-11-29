// Copyright 2018 Nathan Klapstein

/**
 * monitor_thread.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "monitor_thread.h"
#include "thread_manager.h"

/**
 * Prints the status of all tasks (i.e. {@code TaskThread}s.
 *
 * Note: tasks can only have three possible states:
 * - ``WAIT``
 * - ``RUN``
 * - ``IDLE``
 */
void MonitorThread::monitorPrint() {
    // TODO: fill in
//    printf("INFO: monitor: [WAIT] %s\n"
//           "\t[RUN] %s\n"
//           "\t[IDLE] %s\n");
//    for( auto const& [key, val] : threadManager->getTaskThreadMap() )
//    {
//        printf("TEST: %s\n", key.getTaskIDString().c_str());
//    }
}

MonitorThread::MonitorThread(ThreadManager *threadManager)
        : ManagedThread(), threadManager(threadManager) {
    printf("TEST: %u\n", threadManager->getNIter());
}

void MonitorThread::ThreadMain() {
    printf("TEST: started monitor thread\n");
    monitorPrint();
//    Stop();
}

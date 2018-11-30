// Copyright 2018 Nathan Klapstein

/**
 * monitor_thread.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "monitor_thread.h"

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
}

MonitorThread::MonitorThread() : ManagedThread() {

}

void MonitorThread::ThreadMain() {
    printf("TEST: started monitor thread\n");
    monitorPrint();
}

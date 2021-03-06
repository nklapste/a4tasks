// Copyright 2018 Nathan Klapstein

/**
 * monitor.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "monitor.h"
#include "common.h"
#include "simulator.h"

// EXTERNAL GLOBALS in simu.h
extern std::map<std::string, int> resourceMap;
extern std::vector<TASK> taskList;

extern pthread_mutex_t threadMutex;
extern pthread_mutex_t iterationMutex;
extern pthread_mutex_t monitorMutex;
extern pthread_t TID[NTASKS];

/**
 * Prints the current status of all tasks within the simulator.
 */
void printMonitor()
{
    std::string waitString;
    std::string runString;
    std::string idleString;

    for (auto &task : taskList) {
        if (task.status == WAIT) {
            waitString.append(task.name);
            waitString.append(" ");
        } else if(task.status == RUN) {
            runString.append(task.name);
            runString.append(" ");
        } else {
            idleString.append(task.name);
            idleString.append(" ");
        }
    }

    printf("INFO: Monitor: [WAIT] %s\n\t [RUN] %s\n\t [IDLE] %s\n\n", waitString.c_str(),
           runString.c_str(), idleString.c_str());
}

/**
 * Monitor thread that prints out details periodically.
 *
 * @param arg {@code long}
 */
void *monitorThread(void *arg)
{
    long monitorTime = (long) arg;
    while (true)
    {
        delay(monitorTime);
        mutex_lock(&monitorMutex);
        printMonitor();
        // monitor mutex locks the tasks
        mutex_unlock(&monitorMutex);
    }
}
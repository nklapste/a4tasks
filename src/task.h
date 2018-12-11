// Copyright 2018 Nathan Klapstein

/**
 * task.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_TASK_H
#define A4TASKS_TASK_H

#include <vector>
#include <string>

/**
 * Task status.
 */
typedef enum {WAIT, RUN, IDLE} STATUS;

/**
 * A task to be run within the simulation.
 *
 * Contains the details of a particular task (e.g. name, busy time, idle time, required resources)
 */
typedef struct {
    bool assigned;
    int busyTime;
    int idleTime;
    int timesExecuted;
    STATUS status;
    long totalBusyTime;
    long totalIdleTime;
    long totalWaitTime;
    char name[100];
    std::vector<std::string> reqResources;
} TASK;

#endif //A4TASKS_TASK_H

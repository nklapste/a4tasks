// Copyright 2018 Nathan Klapstein

/**
 * task_manager.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_TASK_MANAGER_H
#define A4TASKS_TASK_MANAGER_H

#include <string>
#include <chrono>

using std::string;
using std::chrono::milliseconds;

class TaskManager {
public:
    uint getNIter() const;

    milliseconds getMonitorTime();

    void start();

private:
    string inputFile;
    milliseconds monitorTime;
    uint nIter;
};


#endif  //A4TASKS_TASK_MANAGER_H

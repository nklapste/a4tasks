// Copyright 2018 Nathan Klapstein

/**
 * task_manager.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_TASK_MANAGER_H
#define A4TASKS_TASK_MANAGER_H

#include <fstream>
#include <string>
#include <chrono>

using std::string;
using std::chrono::milliseconds;
using std::ifstream;

class TaskManager {
public:
    TaskManager(const string &inputFile, const milliseconds &monitorTime,
                const uint &nIter);

    milliseconds getMonitorTime();

    uint getNIter() const;

    void start();

private:
    string inputFile;

    milliseconds monitorTime;

    uint nIter;

    ifstream inputFileStream;

    void checkInputFile(ifstream &trafficFileStream);

};


#endif  //A4TASKS_TASK_MANAGER_H

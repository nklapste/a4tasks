// Copyright 2018 Nathan Klapstein

/**
 * thread_manager.h
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

class ThreadManager {
public:
    ThreadManager(const string &inputFile, const milliseconds &monitorTime,
                  const uint &nIter);

    milliseconds getMonitorTime();

    uint getNIter() const;

    void start();

    void terminationPrint();

    void listResources();

    void listTasks();

private:
    /**
     * Path to the input file to parse and use.
     */
    string inputFile;

    /**
     * Number of {@code std::chrono::milliseconds} that has to pass before a
     * instance of a {@code MonitorThread} will start and run.
     */
    milliseconds monitorTime;

    /**
     * Integer noting the amount of iterations that each {@code TaskThread}
     * must execute before the {@code ThreadManager} finishes.
     */
    uint nIter;

    ifstream inputFileStream;

    void checkInputFileLine(ifstream &trafficFileStream);
};


#endif  //A4TASKS_TASK_MANAGER_H

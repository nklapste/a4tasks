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
#include <vector>
#include <map>

#include "monitor_thread.h"
#include "task_thread.h"

using std::string;
using std::chrono::milliseconds;
using std::ifstream;
using std::vector;

typedef std::map<TaskID, TaskThread> TaskThreadMap;

class ThreadManager {
public:
    ThreadManager(const string &inputFile, const milliseconds &monitorTime,
                  const uint &nIter);

    uint getNIter() const;

    void start();

    void terminationPrint();

    void listResources();

    void listTasks();

    void listElapsedTime();

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

    milliseconds startTime;

    /**
     * Integer noting the amount of iterations that each {@code TaskThread}
     * must execute before the {@code ThreadManager} finishes.
     */
    uint nIter;

    ifstream inputFileStream;

    TaskThreadMap taskThreads;

    void checkInputFileLine(ifstream &inputFileStream);

    void parseInputFileLine(const string &line);

    // montor thread timing control
    MonitorThread monitorThread;

    milliseconds monitorThreadEndTime = std::chrono::duration_cast<milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );;

    void checkMonitorThread();

    bool monitorThreadDelayPassed();

    void setMonitorThreadDelay(milliseconds interval);
};


#endif  //A4TASKS_TASK_MANAGER_H

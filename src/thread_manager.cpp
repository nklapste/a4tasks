// Copyright 2018 Nathan Klapstein

/**
 * thread_manager.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <chrono>

#include "thread_manager.h"
#include "input_file.h"
#include "task_thread.h"
#include "monitor_thread.h"

using std::get;


/**
 * Getter for a {@code ThreadManager}'s {@code nIter}.
 *
 * @return {@code uint}
 */
uint ThreadManager::getNIter() const {
    return nIter;
}

/**
 * Start the {@code ThreadManager}.
 */
void ThreadManager::start() {
    // note the start time for later printing the elapsed time
    startTime = std::chrono::duration_cast<milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch());
    printf("INFO: staring ThreadManager startTime: %li\n", startTime.count());

    // TODO: implement
    for (;;) {
        checkInputFileLine(inputFileStream);
        checkMonitorThread();
    }
}

/**
 * Construct a {@code ThreadManager}.
 *
 * @param inputFile {@code std::string}
 * @param monitorTime {@code milliseconds}
 * @param nIter {@code uint}
 */
ThreadManager::ThreadManager(const string &inputFile,
                             const milliseconds &monitorTime,
                             const uint &nIter) :
        inputFile(inputFile),
        monitorTime(monitorTime),
        nIter(nIter),
        inputFileStream(ifstream(inputFile)),
        monitorThread(MonitorThread(this)) {
}

/**
 * Read a line from the input file.
 *
 * @param inputFileStream {@code trafficFileStream}
 */
void ThreadManager::checkInputFileLine(ifstream &inputFileStream) {
    string line;
    if (inputFileStream.is_open()) {
        if (getline(inputFileStream, line)) {
            parseInputFileLine(line);  // TODO: expand
        } else {
            inputFileStream.close();
            printf("DEBUG: finished reading input file\n");
        }
    }
}

/**
 * Parse a line within the input file.
 *
 * @param line {@code std::string}
 * @return {@code std::string}
 */
void ThreadManager::parseInputFileLine(const string &line) {
    int inputLineType = getInputFileType(line);

    if (inputLineType == INVALID_LINE) {
        printf("WARNING: skipping invalid line: %s\n", line.c_str());
    } else if (inputLineType == COMMENT_LINE) {
        printf("DEBUG: skipping comment line: %s\n", line.c_str());
    } else if (inputLineType == RESOURCE_LINE) {
        ResourcesLine resourcesLine = parseResourcesLine(line);
    } else if (inputLineType == TASK_LINE) {
        TaskLine taskLine = parseTaskLine(line);
        taskThreads.insert(std::make_pair(get<1>(taskLine),
                                          TaskThread(get<1>(taskLine),
                                                     getNIter())));
    }
    // TODO: act on parsed input line
}

/**
 * After all other threads finish the main thread prints the information
 * on the system resource usage and task started/used.
 */
void ThreadManager::terminationPrint() {
    listResources();
    listTasks();
}

/**
 * Prints information on the system resource usage.
 */
void ThreadManager::listResources() {
    printf("INFO: System Resoureces:\n");
    // TODO: for loop over system resources
    //    printf("%s: (maxAvail=%4u, held=%4d)\n", )
}

/**
 * Print information on the system tasks usages, and status.
 */
void ThreadManager::listTasks() {
    printf("INFO: System Tasks:\n");
    // TODO: for loop over all tasks
//    printf("[%u] %s (%s, runTiume= %li msec, idleTime= %li msec):\n", )
//    printf("\t(tid= %lu)\n")
    // TODO: print resources used
//    printf("\t%s: (needed=%4u, held=%4u)\n");
    // TODO: print task run stats
//    printf("RUN: %u times, WAIT: %li msec\n", );
}

/**
 * Print the total elapsed running time of the simulator (i.e. {@code ThreadManager}.
 */
void ThreadManager::listElapsedTime() {
    printf("INFO: Running time= %li msec\n",
           (std::chrono::duration_cast<milliseconds>(
                   std::chrono::steady_clock::now().time_since_epoch()) -
            startTime).count());
}

/**
 * Check if the current clock time is greater than or equal to the current delay's {@code endTime}.
 *
 * @return {@code bool}
 */
bool ThreadManager::monitorThreadDelayPassed() {
    milliseconds curTime = std::chrono::duration_cast<milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return curTime >= monitorThreadEndTime;
}

/**
 * Set the current delay's {@code endTime}. If a delay is already inplace and is still active
 * (i.e delayPassed returns {@code false}) add onto the delay's {@code endtime}.
 *  Otherwise set the delay's {@code endTime} to the given interval plus the current clock time.
 *
 * @param interval {@code clock_t}
 */
void ThreadManager::setMonitorThreadDelay(milliseconds interval) {
    printf("DEBUG: adding monitorThread delay interval: %li\n",
           interval.count());
    milliseconds currentTime = std::chrono::duration_cast<milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    if (!monitorThreadDelayPassed()) {
        monitorThreadEndTime = interval + monitorThreadEndTime;
    } else {
        monitorThreadEndTime = interval + currentTime;
    }
    printf("DEBUG: setting monitorThread delay interval: currentTime: %lims monitorThreadEndTime: %lims\n",
           currentTime.count(), monitorThreadEndTime.count());
}

void ThreadManager::checkMonitorThread() {
    if (monitorThreadDelayPassed()) {
        printf("DEBUG: monitor thread delay passed\n");
        setMonitorThreadDelay(monitorTime);
        // TODO: spawn monitor thread
    }
}


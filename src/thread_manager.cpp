// Copyright 2018 Nathan Klapstein

/**
 * thread_manager.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "thread_manager.h"
#include "input_file.h"
#include "task_thread.h"

using std::get;

/**
 * Getter for a {@code ThreadManager}'s {@code milliseconds}.
 *
 * @return {@code milliseconds}
 */
milliseconds ThreadManager::getMonitorTime() {
    return monitorTime;
}

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
    printf("INFO: staring ThreadManager\n");
    // TODO: implement
    for (;;) {
        checkInputFileLine(inputFileStream);
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
        inputFileStream(ifstream(inputFile)) {
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
        TaskThread taskThread = TaskThread(get<1>(taskLine));
        taskThread.Start();
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

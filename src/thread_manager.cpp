// Copyright 2018 Nathan Klapstein

/**
 * thread_manager.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "thread_manager.h"
#include "input_file.h"

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
 * @param trafficFileStream {@code trafficFileStream}
 */
void ThreadManager::checkInputFileLine(ifstream &trafficFileStream) {
    string line;
    if (trafficFileStream.is_open()) {
        if (getline(trafficFileStream, line)) {
            parseInputFileLine(line);  // TODO: expand
        } else {
            trafficFileStream.close();
            printf("DEBUG: finished reading traffic file\n");
        }
    }
}

// Copyright 2018 Nathan Klapstein

/**
 * task_manager.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "task_manager.h"
#include "input_file.h"

/**
 * Getter for a {@code TaskManager}'s {@code milliseconds}.
 *
 * @return {@code milliseconds}
 */
milliseconds TaskManager::getMonitorTime() {
    return monitorTime;
}

/**
 * Getter for a {@code TaskManager}'s {@code nIter}.
 *
 * @return {@code uint}
 */
uint TaskManager::getNIter() const {
    return nIter;
}

/**
 * Start the {@code TaskManager}.
 */
void TaskManager::start() {
    printf("INFO: staring TaskManager\n");
    // TODO: implement
    for (;;) {
        checkInputFile(inputFileStream);
    }
}

/**
 * Construct a {@code TaskManager}.
 *
 * @param inputFile {@code std::string}
 * @param monitorTime {@code milliseconds}
 * @param nIter {@code uint}
 */
TaskManager::TaskManager(const string &inputFile,
                         const milliseconds &monitorTime,
                         const uint &nIter) :
        inputFile(inputFile),
        monitorTime(monitorTime),
        nIter(nIter),
        inputFileStream(ifstream(inputFile)) {
}

/**
 * Read a section from the input file.
 *
 * @param trafficFileStream {@code trafficFileStream}
 */
void TaskManager::checkInputFile(ifstream &trafficFileStream) {
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

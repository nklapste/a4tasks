// Copyright 2018 Nathan Klapstein

/**
 * task_manager.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "task_manager.h"

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
    // TODO: implement
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
        nIter(nIter) {

}

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

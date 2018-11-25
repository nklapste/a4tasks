// Copyright 2018 Nathan Klapstein

/**
 * task_id.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "task_id.h"

using std::to_string;

TaskID::TaskID(uint taskIdNum) :
        taskIDNum(taskIdNum), taskIDString(to_string(taskIdNum)) {
}

/**
 * Getter for a {@code TaskID}'s ID number as a {@code uint}.
 *
 * @return {@code uint}
 */
uint TaskID::getTaskIDNum() const {
    return taskIDNum;
}

/**
 * Getter for a {@code TaskID}'s ID number as a {@code std::string}.
 *
 * @return {@code std::string}
 */
string TaskID::getTaskIDString() const {
    return taskIDString;
}

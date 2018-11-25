// Copyright 2018 Nathan Klapstein

/**
 * task_id.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "task_id.h"

using std::to_string;

TaskId::TaskId(uint taskIdNum) :
        taskIDNum(taskIdNum), taskIDString(to_string(taskIdNum)) {
}

uint TaskId::getTaskIDNum() const {
    return taskIDNum;
}

string TaskId::getTaskIDString() const {
    return taskIDString;
}

// Copyright 2018 Nathan Klapstein

/**
 * task_thread.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "task_thread.h"

/**
 * Constructor for a {@code TaskThread}.
 *
 * @param taskID {@code TaskID}
 */
TaskThread::TaskThread(TaskID taskID) : ManagedThread(), taskID(taskID) {

}

/**
 * Getter the a {@code TaskThread}'s {@code TaskID}.
 *
 * @return {@code TaskID}
 */
TaskID TaskThread::getTaskID() const {
    return taskID;
}

/**
 * Getter the a {@code TaskThread}'s ID number.
 *
 * @return {@code pthread_t}
 */
pthread_t TaskThread::getTID() {
    return tid;
}

/**
 * Getter the a {@code TaskThread}'s iteration number.
 *
 * @return {@code uint}
 */
uint TaskThread::getIterNum() {
    return iterNum;
}

/**
 * Getter the a {@code TaskThread}'s time.
 *
 * @return {@code std::chrono::milliseconds}
 */
milliseconds TaskThread::getTime() {
    return time;
}

/**
 * After a successful iteration a {@code TaskThread} is required to print
 * the following message.
 */
void TaskThread::completePrint() {
    printf("INFO: task: %s (tid= %lu, iter= %u, time=%limsec\n",
           getTaskID().getTaskIDString().c_str(),
           getTID(),
           getIterNum(),
           getTime().count());
}

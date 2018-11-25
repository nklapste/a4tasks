// Copyright 2018 Nathan Klapstein

/**
 * task_thread.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_TASK_THREAD_H
#define A4TASKS_TASK_THREAD_H

#include <chrono>

#include "managed_thread.h"
#include "task_id.h"


using std::chrono::milliseconds;

class TaskThread : public ManagedThread {
public:
    TaskID getTaskID();

    pthread_t getTID();

    uint getIterNum();

    milliseconds getTime();

    void completePrint();

private:
    TaskID taskID;

    /**
     * A unsigned long integer (in the lab environ) noting the threads ID.
     */
    pthread_t tid;

    /**
     * The iteration number the thread has just completed.
     */
    uint iterNum;

    /**
     * The time in milliseconds relative to the start time of the a4tasks
     * program.
     */
    milliseconds time;
};


#endif  //A4TASKS_TASK_THREAD_H
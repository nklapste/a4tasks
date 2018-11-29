// Copyright 2018 Nathan Klapstein

/**
 * monitor_thread.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_MONITOR_THREAD_H
#define A4TASKS_MONITOR_THREAD_H

#include "managed_thread.h"

class ThreadManager;

class MonitorThread : public ManagedThread {
public:
    explicit MonitorThread(ThreadManager *threadManager);

    void monitorPrint();

protected:
    void ThreadMain() override;

private:
    ThreadManager *threadManager;

};


#endif  //A4TASKS_MONITOR_THREAD_H

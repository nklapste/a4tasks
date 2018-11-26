// Copyright 2018 Nathan Klapstein

/**
 * managed_thread.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_THREAD_H
#define A4TASKS_THREAD_H

#include <thread>
#include <chrono>
#include <sstream>

class ManagedThread {
public:
    /* Explicitly using the default constructor to
     * underline the fact that it does get called */
    explicit ManagedThread() : the_thread() {}
    ~ManagedThread() {
        stop_thread = true;
        if (the_thread.joinable()) the_thread.join();
    }

    void Start() {
        // This will start the thread. Notice move semantics!
        the_thread = std::thread(&ManagedThread::ThreadMain, this);
        std::stringstream ss;
        ss << the_thread.get_id();
        printf("DEBUG: starting thread: %s\n", ss.str().c_str());
    }

    void Stop() {
        std::stringstream ss;
        ss << the_thread.get_id();
        printf("DEBUG: stopping thread: %s\n", ss.str().c_str());
        stop_thread = true;
    }

private:
    bool stop_thread = false; // Super simple thread stopping.

    std::thread the_thread;

    void ThreadMain() {
        while (!stop_thread) {
            // Do something useful, e.g:
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};


#endif  //A4TASKS_THREAD_H

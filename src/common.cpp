// Copyright 2018 Nathan Klapstein

/**
 * common.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <time.h>
#include <zconf.h>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include "common.h"

/**
 * Wait for a specified amount of milliseconds.
 *
 * @param milliseconds {@code int}
 */
void delay(int milliseconds)
{
    struct timespec interval{};
    interval.tv_sec = (long) milliseconds / 1000;
    interval.tv_nsec = (long) ((milliseconds % 1000) * 1000000);
    if (nanosleep(&interval, nullptr) < 0) {
        printf("WARNING: delay: %s\n", strerror(errno));
    }
}


void mutex_init(pthread_mutex_t* mutex)
{
    int rval = pthread_mutex_init(mutex, nullptr);
    if (rval) {
        fprintf(stderr, "ERROR: mutex_init: %s\n", strerror(rval));
        exit(1);
    }
}

void mutex_lock(pthread_mutex_t* mutex)
{
    int rval = pthread_mutex_lock(mutex);
    if (rval) {
        fprintf(stderr, "ERROR: mutex_lock: %s\n", strerror(rval));
        exit(1);
    }
}

void mutex_unlock(pthread_mutex_t* mutex)
{
    int rval = pthread_mutex_unlock(mutex);
    if (rval) {
        fprintf(stderr, "ERROR: mutex_unlock: %s\n", strerror(rval));
        exit(1);
    }
}

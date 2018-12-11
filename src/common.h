// Copyright 2018 Nathan Klapstein

/**
 * common.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_COMMON_H
#define A4TASKS_COMMON_H

#include <zconf.h>

void delay(int milliseconds);

void mutex_init(pthread_mutex_t* mutex);

void mutex_lock(pthread_mutex_t* mutex);

void mutex_unlock(pthread_mutex_t* mutex);

#endif //A4TASKS_COMMON_H

// Copyright 2018 Nathan Klapstein

/**
 * simulator.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_SIMU_H
#define A4TASKS_SIMU_H

#include <vector>
#include <string>
#include <map>

#include "task.h"

#define NTASKS 25
#define NRES_TYPES 10

void start(std::string inputFile, long monitorTime, int iterations);

#endif //A4TASKS_SIMU_H

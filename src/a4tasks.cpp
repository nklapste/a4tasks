// Copyright 2018 Nathan Klapstein

/**
 * a4tasks.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <string>
#include <iostream>

#include "simulator.h"

using std::string;

/**
 * Main entry point for a4tasks.
 *
 * Parse entry point arguments and startup main task functionality.
 *
 * Command format:
 *      ``./a4tasks inputFile monitorTime NITER``
 *
 * @param argc {@code int}
 * @param argv {@code char **}
 * @return {@code int}
 */
int main(int argc, char **argv) {
    if (argc != 4) {
        printf("ERROR: invalid argument format:\n"
               "\tPlease follow: 'a4tasks inputFile monitorTime NITER'\n");
        exit(EINVAL);
    }

    string inputFile = argv[1];
    long monitorTime = static_cast<long>(atoi(argv[2]));
    uint nIter = static_cast<uint>(atoi(argv[3]));

    // start the simulation
    start(inputFile, monitorTime, nIter);

    return 0;
}

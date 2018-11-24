// Copyright 2018 Nathan Klapstein

/**
 * a4tasks.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <iostream>

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
    if (argc < 3 || argc > 4) {
        printf("ERROR: invalid argument format:\n"
               "\tPlease follow: 'a4tasks inputFile monitorTime NITER'\n");
        exit(EINVAL);
    }

    return 0;
}

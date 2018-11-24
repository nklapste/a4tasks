// Copyright 2018 Nathan Klapstein

/**
 * input_file.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <sstream>
#include <iterator>

#include "input_file.h"

using std::istringstream;
using std::istream_iterator;

/**
 * Attempt to get the line type for a input file.
 *
 * @param line {@code std::string}
 * @return {@code int} integer representing the type of the traffic file line.
 */
int getInputFileType(string &line) {
    if (line.length() < 1) {
        printf("WARNING: found invalid line: %s\n", line.c_str());
        return INVALID_LINE;
    }
    if (line.substr(0, 1) == "#") {
        printf("DEBUG: found comment line: %s\n", line.c_str());
        return INVALID_LINE;
    }

    istringstream iss(line);
    vector<string> trafficFileItems((istream_iterator<string>(iss)), istream_iterator<string>());

    if (trafficFileItems.size() < 2) {
        printf("WARNING: found invalid line: %s\n", line.c_str());
        return INVALID_LINE;
    }
    if (trafficFileItems.at(1) == RESOURCE_FLAG) { // check if delay line
        printf("DEBUG: found RESOURCE line: %s\n", line.c_str());
        return RESOURCE_LINE;
    } else {
        printf("DEBUG: found TASK line: %s\n", line.c_str());
        return TASK_LINE;
    }
}

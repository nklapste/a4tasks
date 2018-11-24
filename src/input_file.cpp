// Copyright 2018 Nathan Klapstein

/**
 * input_file.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <string>
#include <sstream>
#include <iterator>

#include "input_file.h"

using std::istringstream;
using std::istream_iterator;

/**
 * Attempt to get the line type for a input file.
 *
 * @param line {@code std::string}
 * @return {@code int} integer representing the type of the input file line.
 */
int getInputFileType(const string &line) {
    if (line.length() < 1) {
        printf("WARNING: found invalid line: %s\n", line.c_str());
        return INVALID_LINE;
    }
    if (line.substr(0, 1) == "#") {
        printf("DEBUG: found comment line: %s\n", line.c_str());
        return INVALID_LINE;
    }

    istringstream iss(line);
    vector<string> trafficFileItems((istream_iterator<string>(iss)),
                                    istream_iterator<string>());

    if (trafficFileItems.size() < 2) {
        printf("WARNING: found invalid line: %s\n", line.c_str());
        return INVALID_LINE;
    }
    if (trafficFileItems.at(1) == RESOURCE_FLAG) {
        printf("DEBUG: found ResourcesLine: %s\n", line.c_str());
        return RESOURCE_LINE;
    } else {
        printf("DEBUG: found TaskLine: %s\n", line.c_str());
        return TASK_LINE;
    }
}

/**
 * Parse a {@code std::string} representing a {@code ResourceArg}.
 * @param arg {@code std::string}
 * @return {@code ResourceArg}
 */
ResourceArg parseResourceArg(const string &arg) {
    std::string delimiter = ":";
    std::string name = arg.substr(0, arg.find(delimiter));
    uint value = static_cast<uint>(stoi(
            arg.substr(arg.find(delimiter) + 1, arg.length())));
    return ResourceArg(name, value);
}

/**
 * Parse a line within the input file line representing a {@code ResourcesLine}.
 *
 * @param line {@code std::string}
 * @return {@code ResourcesLine}
 */
ResourcesLine parseResourcesLine(const string &line) {
    istringstream iss(line);
    vector<string> resourceLineArgs((istream_iterator<string>(iss)),
                                    istream_iterator<string>());
    if (resourceLineArgs.size() < 2 ||
        resourceLineArgs.at(0) != RESOURCE_FLAG) {
        printf("ERROR: invalid ResourcesLine: %s\n", line.c_str());
        exit(EINVAL);
    }
    string lineFlag = resourceLineArgs.at(0);

    vector<ResourceArg> resourceArgs;
    for (auto it = resourceLineArgs.begin() + 1;
         it != resourceLineArgs.end(); ++it) {
        resourceArgs.emplace_back(parseResourceArg(*it));
    }

    printf("DEBUG: parsed ResourcesLine\n");  // TODO: improve log

    return ResourcesLine(lineFlag, resourceArgs);
}

/**
 * Parse a line within the input file line representing a {@code TaskLine}.
 *
 * task taskName busyTime idleTime name1:value1 name2:value2 ...
 *
 * @param line {@code std::string}
 * @return {@code TaskLine}
 */
TaskLine parseTaskLine(const string &line) {
    istringstream iss(line);
    vector<string> taskLineArgs((istream_iterator<string>(iss)),
                                istream_iterator<string>());
    if (taskLineArgs.size() < 5 || taskLineArgs.at(0) != TASK_FLAG) {
        printf("ERROR: invalid TaskLine: %s\n", line.c_str());
        exit(EINVAL);
    }
    string lineFlag = taskLineArgs.at(0);
    string taskName = taskLineArgs.at(1);
    milliseconds busyTime = static_cast<milliseconds>(stoi(taskLineArgs.at(2)));
    milliseconds idleTime = static_cast<milliseconds>(stoi(taskLineArgs.at(4)));

    vector<ResourceArg> resourceArgs;
    for (auto it = taskLineArgs.begin() + 5; it != taskLineArgs.end(); ++it) {
        resourceArgs.emplace_back(parseResourceArg(*it));
    }

    printf("DEBUG: parsed TaskLine\n");  // TODO: improve log

    return TaskLine(lineFlag, taskName, busyTime, idleTime, resourceArgs);
}

// Copyright 2018 Nathan Klapstein

/**
 * input_file.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_INPUT_FILE_H
#define A4TASKS_INPUT_FILE_H

#include <tuple>
#include <chrono>
#include <vector>

#define RESOURCE_FLAG "resources"
#define TASK_FLAG "task"
#define COMMENT_FLAG "#"

#define INVALID_LINE -1
#define COMMENT_LINE 0
#define RESOURCE_LINE 1
#define TASK_LINE 1

using std::string;
using std::vector;
using std::tuple;
using std::chrono::milliseconds;

typedef tuple<string, int> ResourceArg;
typedef tuple<string, vector<ResourceArg>> ResourcesLine;
typedef tuple<string, string, milliseconds, milliseconds, vector<ResourceArg>> TaskLine;

int getInputFileType(string &line);

ResourceArg parseResourceArg(string &arg);

ResourcesLine parseResourcesLine(string &line);

#endif //A4TASKS_INPUT_FILE_H

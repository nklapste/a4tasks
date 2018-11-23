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

using namespace std;
using namespace chrono;

typedef tuple<string, int> ResourceArg;
typedef tuple<string, vector<ResourceArg>> ResourcesLine;
typedef tuple<string, string, milliseconds, milliseconds, vector<ResourceArg>> TaskLine;

#endif //A4TASKS_INPUT_FILE_H

// Copyright 2018 Nathan Klapstein

/**
 * task_id.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include <regex>
#include "task_id.h"

using std::to_string;

/**
 * Parse the {@code TaskID} specified by a {@code std::string}.
 *
 * @param taskIDString {@code std::string}
 * @return {@code uint}
 */
uint TaskID::parseTaskID(const string &taskIDString) {
    std::regex rgx("(t)([1-9]+[0-9]*)");
    std::match_results<string::const_iterator> matches;

    std::regex_match(taskIDString, matches, rgx);
    for (std::size_t index = 1; index < matches.size(); ++index) {
    }

    if (std::regex_search(taskIDString, matches, rgx)) {
        uint taskIDNum = static_cast<uint>(std::stoi(matches[2], nullptr, 10));
        return taskIDNum;
    } else {
        printf("ERROR: invalid taskIDString argument: %s\n",
               taskIDString.c_str());
        exit(EINVAL);
    }
}

/**
 * Init a {@code TaskID} from a {@code uint}.
 *
 * @param taskIDNum {@code uint}
 */
TaskID::TaskID(uint taskIDNum) :
        taskIDNum(taskIDNum), taskIDString("t" + to_string(taskIDNum)) {
}

/**
 * Init a {@code TaskID} from a {@code std::string}.
 *
 * @param taskIDString {@code std::string}
 */
TaskID::TaskID(const string &taskIDString) : taskIDString(taskIDString) {
    taskIDNum = parseTaskID(taskIDString);
}

/**
 * Getter for a {@code TaskID}'s ID number as a {@code uint}.
 *
 * @return {@code uint}
 */
uint TaskID::getTaskIDNum() const {
    return taskIDNum;
}

/**
 * Getter for a {@code TaskID}'s ID number as a {@code std::string}.
 *
 * @return {@code std::string}
 */
string TaskID::getTaskIDString() const {
    return taskIDString;
}

// Copyright 2018 Nathan Klapstein

/**
 * task_id.h
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#ifndef A4TASKS_TASK_ID_H
#define A4TASKS_TASK_ID_H

#include <string>

using std::string;

class TaskID {
public:
    explicit TaskID(uint taskIDNum);

    explicit TaskID(const string &taskIDString);

    uint getTaskIDNum() const;

    string getTaskIDString() const;

private:
    uint taskIDNum;

    string taskIDString;

    uint parseTaskID(const string &taskIDString);
};


#endif  //A4TASKS_TASK_ID_H

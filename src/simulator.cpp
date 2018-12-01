// Created by nklap on 2018-11-30.

/**
 * simulator.cpp
 *
 * @author Nathan Klapstein (nklapste)
 * @version 0.0.0
 */

#include "simulator.h"

#include <stdio.h>
#include<iostream>
#include<sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include<vector>

#include<string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <pthread.h>
#include <fstream>
#include <errno.h>
#include <time.h>
#include <map>
#include <sys/times.h>

#include "task.h"
#include "monitor.h"
#include "common.h"

#define COMMENT_FLAG "#"
#define RESOURCES_FLAG "resources"
#define TASK_FLAG "task"

#define RUN_FLAG "RUN"
#define IDLE_FLAG "IDLE"
#define WAIT_FLAG "WAIT"

using namespace std;

//GLOBAL VARIABLES
std::map<std::string, int> resourceMap; //contain the resources from the file
std::vector<TASK> taskList; //contains all the tasks from the file
pthread_mutex_t threadMutex;
pthread_mutex_t iterationMutex;
pthread_mutex_t monitorMutex; // used for monitor to prevent states from switching
pthread_t TID[NTASKS];
int ITERATIONS;
clock_t START, END;
struct tms tmsstart, tmsend;
static long clktck = 0;

/**
 * Parse a resource pair "name:value" and add it to the {@code resourceMap}.
 *
 * @param nameCountPair {@code char*}
 */
void addResources(char* nameCountPair)
{
    char tempPair[40];
    strcpy(tempPair, nameCountPair);
    int tempCount;
    string tempName(strtok(tempPair, ":"));
    tempCount = atoi(strtok(nullptr, ":"));
    //add to map https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
    //resourceMap.insert(pair<char*, int>(tempName, tempCount));
    resourceMap[tempName] = tempCount;
}

void defineResources(char* resourceLine)
{
    //we have one line and need to tokenize each resource and map it.
    char* temp;
    char line[100];
    vector<char*> resourceStrings;

    strcpy(line, resourceLine);
    temp = strtok(line, " "); //temp is keyword RESOURCES
    temp = strtok(nullptr, " "); //move it to first name:count pair
    while (temp != nullptr)
    {
        resourceStrings.push_back(temp);
        temp = strtok(nullptr, " ");
    }

    for (auto &resourceString : resourceStrings) {
        //add the resources to the map
        addResources(resourceString);
    }
}

void readTaskFile(char* fileName)
{
    string line; //line read from file

    ifstream file(fileName);
    if (file.fail()) {
        printf("ERROR: FILE DOES NOT EXIST\n");
        exit(1);
    } //check if file exists

    if (file.good())
    {
        while (getline(file, line))
        {
            //ignore any comments or white lines
            if (line[0] == '#' || line[0] == '\r' || line[0] == '\n') {
                continue;
            }

            char cline[100];
            char* flag;
            strcpy(cline, line.c_str());

            //determine what the leading keyword is (i.e. the input file line flag)
            flag = strtok(cline, " ");
            if (!(strcmp(flag, RESOURCES_FLAG) == 0 || strcmp(flag, TASK_FLAG) == 0)) {
                printf("ERROR: UNKNOWN KEYWORD FROM FILE: %s\n", flag);
                exit(EINVAL);
            }

            if (strcmp(flag, RESOURCES_FLAG) == 0) {
                // we need to define the resources that will be used
                strcpy(cline, line.c_str());
                defineResources(cline);
            } else {	//if it is not a resource, it is a task. initialize new task and add it to task list
                TASK newTask;
                flag = strtok(nullptr, " ");
                strcpy(newTask.name, flag);
                flag = strtok(nullptr, " ");
                newTask.busyTime = atoi(flag);
                flag = strtok(nullptr, " ");
                newTask.idleTime = atoi(flag);
                flag = strtok(nullptr, " ");
                newTask.assigned = false;
                newTask.status = IDLE;
                newTask.totalIdleTime = 0;
                newTask.totalBusyTime = 0;
                newTask.totalWaitTime = 0;
                newTask.timesExecuted = 0;
                //add resource strings to list
                while (flag != nullptr)
                {
                    string str(flag);
                    newTask.reqResources.push_back(str);
                    flag = strtok(nullptr, " ");
                }

                //add to task list
                taskList.push_back(newTask);
            }
        }
    }
}

bool checkResources(TASK* task)
{	//this function is called by a thread when it is going to check available resources
    //We need to check if resources are available to grab, if not then unlock and go back to waiting
    for (auto &reqResource : task->reqResources) {
        char resource[50];
        strcpy(resource, reqResource.c_str());
        char* resName = strtok(resource, ":");
        int resCount = atoi(strtok(nullptr, ":"));

        if (resourceMap[resName] >= resCount) {
            // there are enough resources for this thread
            continue;
        }
        return false;
    }
    // there are enough of the required resources
    return true;
}

/**
 * Sets a task to procure and use a resource.
 *
 * Decrements the appropriate resources when called.
 *
 * @param task {@code TASK*}
 */
void procureResources(TASK* task)
{
    for (auto &reqResource : task->reqResources) {
        char resource[50];
        strcpy(resource, reqResource.c_str());
        char* resName = strtok(resource, ":");
        int resCount = atoi(strtok(nullptr, ":"));
        int currentValue = resourceMap[resName];
        int newValue = currentValue - resCount;
        resourceMap[resName] = newValue;
    }
}

void returnResources(TASK* task)
{	//this function will return the appropriate resources when called
    for (auto &reqResource : task->reqResources) {
        char resource[50];
        strcpy(resource, reqResource.c_str());
        char* resName = strtok(resource, ":");
        int resCount = atoi(strtok(nullptr, ":"));
        int currentValue = resourceMap[resName];
        int newValue = currentValue + resCount;
        resourceMap[resName] = newValue;
    }
}

/**
 * Get the time since the start of the main program execution
 *
 * @return {@code float}
 */
float getTime()
{
    END = times(&tmsend);
    clock_t time = END - START;
    return time/(double) clktck * 1000;
}

void runIterations(TASK* task)
{ /*After a thread is created, it will come to this function to execute its
  main loop. We use another mutex to handle race conditions with other threads*/
    int iterationCounter = 0;
    bool enoughResources;
    clock_t waitStart, waitFinish; //used to determine how long a task will wait
    struct tms tmswaitstart, tmswaitend;

    mutex_lock(&monitorMutex); //make sure cannot change state if monitor is printing
    task->status = WAIT;
    mutex_unlock(&monitorMutex);

    waitStart = times(&tmswaitstart);
    while (true)
    {
        mutex_lock(&iterationMutex);

        //We need to check if resources are available to grab, if not then unlock and go back to waiting
        enoughResources = checkResources(task);
        if (!enoughResources)
        {	//release mutex and go back to waiting
            mutex_unlock(&iterationMutex);
            delay(20);
            continue;
        }

        procureResources(task); //will actually grab the resources from the shared resource pool
        waitFinish = times(&tmswaitend);
        task->totalWaitTime += (waitFinish - waitStart) / (double)clktck * 1000; //update wait time
        mutex_unlock(&iterationMutex);

        //after resources are taken, simulate the execution of the process
        mutex_lock(&monitorMutex); //cant switch states if monitor is printing
        task->status = RUN;
        mutex_unlock(&monitorMutex);
        delay(task->busyTime);
        task->totalBusyTime += task->busyTime;

        //after running the busytime then return the resources back to the pool
        mutex_lock(&iterationMutex);
        returnResources(task);
        mutex_unlock(&iterationMutex);

        //now we wait for idle time and increment iteration counter
        mutex_lock(&monitorMutex); // cant switch states if monitor printing
        task->status = IDLE;
        mutex_unlock(&monitorMutex);

        delay(task->idleTime);
        task->totalIdleTime += task->idleTime;
        iterationCounter += 1;
        task->timesExecuted += 1;
        //print out iteration info
        printf("INFO: Task: %s (tid= %lu, iter= %d, time= %.0fms) \n", task->name, pthread_self(), iterationCounter, getTime());
        if (iterationCounter == ITERATIONS) {
            return;
        }

        mutex_lock(&monitorMutex); //cant switch states if monitor printing
        task->status = WAIT;
        mutex_unlock(&monitorMutex);
        waitStart = times(&tmswaitstart);
    }

}

/**
 * Starting method for when a new task thread is created.
 *
 * @param arg {@code long}
 */
void *threadExecute(void *arg)
{	/* This is the starting routine when a new thread is created*/
    //first iterate through the task list and assign an unassigned task to this thread
    TID[(long)arg] = pthread_self();
    for (auto &task : taskList) {
        if (task.assigned) {
            continue;
        }
        task.assigned = true; //use this task for the main loop
        mutex_unlock(&threadMutex); //release mutex for next thread and jump to main loop
        runIterations(&task);
        break;
    }
    pthread_exit(nullptr);
}

/**
 * Print information about the simulator. (e.g. resource info, task info, total runtime).
 *
 * Should be invoked before termination of the simulator.
 */
void printTerminationInfo()
{
    map<string, int>::iterator itr;
    printf("INFO: System Resources:\n");
    for (itr = resourceMap.begin(); itr != resourceMap.end(); itr++)
    {
        printf("\t\t%s: ", (itr->first).c_str());
        printf("(maxAvail=\t%d, held=\t0)\n", resourceMap[itr->first]);
    }

    printf("INFO: System Tasks:\n");
    for (int i = 0; i < taskList.size(); i++)
    {
        char status[20];
        if (taskList.at(i).status == IDLE) {
            strcpy(status, IDLE_FLAG);
        } else if (taskList.at(i).status == WAIT) {
            strcpy(status, WAIT_FLAG);
        } else {
            strcpy(status, RUN_FLAG);
        }
        printf("[%d] %s (%s, runTime= %lu msec, idleTime= %lu msec):\n", i, taskList.at(i).name, status,
               taskList.at(i).totalBusyTime, taskList.at(i).totalIdleTime);
        printf("\t (tid= %lu\n", TID[i]);
        // print the required resources
        for (auto &reqResource : taskList.at(i).reqResources) {
            char* resourceName;
            int resourcesNeeded;
            char resourceString[50];
            strcpy(resourceString, reqResource.c_str());
            resourceName = strtok(resourceString, ":");
            resourcesNeeded = atoi(strtok(nullptr, ":"));

            printf("\t %s: (needed=\t%d, held= 0)\n", resourceName, resourcesNeeded );
        }
        printf("\t (RUN: %d times, WAIT: %lu msec\n\n", taskList.at(i).timesExecuted, taskList.at(i).totalWaitTime);
    }
    printf("INFO: Total Running Time: %.0f msec\n\n", getTime());
}

/**
 * Start the simulation.
 *
 * @param inputFile {@code std::string}
 * @param monitorTime {@code long}
 * @param iterations {@code int}
 */
void start(string inputFile, long monitorTime, int iterations)
{
    int rval;
    char fileName[20];
    pthread_t ntid;

    strcpy(fileName, inputFile.c_str());
    ITERATIONS = iterations;

    mutex_init(&threadMutex);
    mutex_init(&iterationMutex);
    mutex_init(&monitorMutex);

    // get number of clock cycles per second. Used for timing functions
    if (clktck == 0)
    {
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
        {
            printf("ERROR: systemconf error\n"); exit(-1);
        }
    }

    START = times(&tmsstart);

    readTaskFile(fileName);

    //create monitor thread
    rval = pthread_create(&ntid, nullptr, monitorThread, (void*) monitorTime);
    if (rval) {
        fprintf(stderr, "ERROR: pthread_create: %s\n", strerror(rval));
        exit(1);
    }

    //for every task in the task list we need to execute a new thread
    for (long i = 0; i < taskList.size(); i++)
    {
        mutex_lock(&threadMutex);
        rval = pthread_create(&ntid, nullptr, threadExecute, (void *) i);
        if (rval) {
            fprintf(stderr, "ERROR: pthread_create: %s\n", strerror(rval));
            exit(1);
        }
    }
    delay(400);
    //wait for all other threads to complete before continuing
    for (long i = 0; i < taskList.size(); i++)
    {
        rval = pthread_join(TID[i], nullptr);
        if (rval) {
            fprintf(stderr, "ERROR: pthread_join: %s\n", strerror(rval));
            exit(1);
        }
    }

    printf("INFO: Threads Finished: Terminating\n");
    printTerminationInfo();
    exit(0);
}
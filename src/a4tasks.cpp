#include <array>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <iomanip>
#include <string_view>
#include <map>
#include <error.h>
std::mutex g_lockprint;
constexpr int task_no = 4;

struct resource {
    std::mutex mutex;
};

struct simulation {
    std::atomic<bool> ready{false};
    std::array<std::array<resource *, 4>, 2> resourcesPool;
};

struct task {
private:
    std::string const name;
    simulation const &simul;
    int r1;
    int r2;
    std::thread lifethread;
    std::mt19937 rng{std::random_device{}()};
public:
    task(std::string_view n, simulation const &t, int r1, int r2) :
            name(n), simul(t), r1(r1), r2(r2), lifethread(&task::dine, this) {
    }

    ~task() {
        lifethread.join();
    }

    void dine() {
        while (!simul.ready);

        do {
            idle();
            run();
        } while (simul.ready);
    }

    void print(std::string_view text) {
        std::lock_guard<std::mutex> cout_lock(g_lockprint);
        std::cout
                << std::left << std::setw(10) << std::setfill(' ')
                << name << text << std::endl;
    }

    void run() {
        print("task is waiting");
        try {
            if (r1 == 2) {
                std::lock(simul.resourcesPool.at(0).at(0)->mutex,
                          simul.resourcesPool.at(0).at(1)->mutex);
                perror("ereraserrno");
                std::lock_guard<std::mutex> lock1(
                        simul.resourcesPool.at(0).at(0)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock2(
                        simul.resourcesPool.at(0).at(1)->mutex,
                        std::adopt_lock);
            } else if (r1 == 3) {
                std::lock(simul.resourcesPool.at(0).at(0)->mutex,
                          simul.resourcesPool.at(0).at(1)->mutex,
                          simul.resourcesPool.at(0).at(2)->mutex);
                std::lock_guard<std::mutex> lock1(
                        simul.resourcesPool.at(0).at(0)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock2(
                        simul.resourcesPool.at(0).at(1)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock3(
                        simul.resourcesPool.at(0).at(2)->mutex,
                        std::adopt_lock);
            }
            if (r2 == 2) {
                std::lock(simul.resourcesPool.at(1).at(0)->mutex,
                          simul.resourcesPool.at(1).at(1)->mutex);
                std::lock_guard<std::mutex> lock1(
                        simul.resourcesPool.at(1).at(0)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock2(
                        simul.resourcesPool.at(1).at(1)->mutex,
                        std::adopt_lock);
            } else if (r2 == 3) {
                std::lock(simul.resourcesPool.at(1).at(0)->mutex,
                          simul.resourcesPool.at(1).at(1)->mutex,
                          simul.resourcesPool.at(1).at(2)->mutex);
                std::lock_guard<std::mutex> lock1(
                        simul.resourcesPool.at(1).at(0)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock2(
                        simul.resourcesPool.at(1).at(1)->mutex,
                        std::adopt_lock);
                std::lock_guard<std::mutex> lock3(
                        simul.resourcesPool.at(1).at(2)->mutex,
                        std::adopt_lock);
            }
        } catch (std::exception &e) {
            std::cout << "running task, with exception..." << e.what()
                      << std::endl;
            return;

        }


        print("task is running");

        static thread_local std::uniform_int_distribution<> dist(1, 6);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));

        print("task finished running");
    }

    void idle() {
        static thread_local std::uniform_int_distribution<> wait(1, 6);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));

        print("task is idle");
    }
};

void dine() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Dinner started!" << std::endl;

    {
        simulation table;
        std::array<task, task_no> tasks
                {
                        {
                                {"task1", table, 2, 1},
                                {"task2", table, 2, 1},
                                {"task3", table, 2, 1},
                                {"task4", table, 2, 1},
                        }
                };

        table.ready = true;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        table.ready = false;
    }

    std::cout << "Dinner done!" << std::endl;
}

int main() {
    dine();

    return 0;
}


//// Copyright 2018 Nathan Klapstein
//
///**
// * a4tasks.cpp
// *
// * @author Nathan Klapstein (nklapste)
// * @version 0.0.0
// */
//
//#include <string>
//#include <iostream>
//#include <chrono>
//#include "thread_manager.h"
//
//using std::string;
//using std::chrono::milliseconds;
//
///**
// * Main entry point for a4tasks.
// *
// * Parse entry point arguments and startup main task functionality.
// *
// * Command format:
// *      ``./a4tasks inputFile monitorTime NITER``
// *
// * @param argc {@code int}
// * @param argv {@code char **}
// * @return {@code int}
// */
//int main2(int argc, char **argv) {
//    if (argc != 4) {
//        printf("ERROR: invalid argument format:\n"
//               "\tPlease follow: 'a4tasks inputFile monitorTime NITER'\n");
//        exit(EINVAL);
//    }
//
//    string inputFile = argv[1];
//    milliseconds monitorTime = static_cast<milliseconds>(atoi(argv[2]));
//    uint nIter = static_cast<uint>(atoi(argv[3]));
//
//    ThreadManager taskManager = ThreadManager(inputFile, monitorTime, nIter);
//    taskManager.start();
//
//    return 0;
//}

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

std::mutex g_lockprint;
constexpr int task_no = 2;

struct resource {
    std::mutex mutex;
};

struct simulation {
    std::atomic<bool> ready{false};
    std::array<std::array<resource, 2>, 2> resourcesPool;
};

struct task {
private:
    std::string const name;
    simulation const &simul;
    resource &left_fork;
    resource &right_fork;
    std::thread lifethread;
    std::mt19937 rng{std::random_device{}()};
public:
    task(std::string_view n, simulation const &t, resource &l, resource &r) :
            name(n), simul(t), left_fork(l), right_fork(r),
            lifethread(&task::dine, this) {
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

        std::lock(left_fork.mutex, right_fork.mutex);

        std::lock_guard<std::mutex> left_lock(left_fork.mutex, std::adopt_lock);
        std::lock_guard<std::mutex> right_lock(right_fork.mutex,
                                               std::adopt_lock);

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
                                {"task1", table, table.resourcesPool[0][0], table.resourcesPool[0][1]},
                                {"task2", table, table.resourcesPool[0][0], table.resourcesPool[1][0],},
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

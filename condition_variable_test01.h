#ifndef TEST02_CONDITION_VARIABLE_TEST01_H
#define TEST02_CONDITION_VARIABLE_TEST01_H

// condition_variable example
#include <condition_variable> // std::condition_variable
#include <iostream>           // std::cout
#include <mutex>              // std::mutex, std::unique_lock
#include <thread>             // std::thread

std::mutex              mtx;
std::condition_variable cv;
bool                    ready = false;

void print_id(int id)
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready)
        cv.wait(lck);
    // ...
    std::cout << "thread " << id << '\n';
}

void go()
{
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

void condition_variable_test01()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_id, i);

    std::cout << "10 threads ready to race...\n";
    go(); // go!

    for (auto& th : threads)
        th.join();

    return;
}
#endif //TEST02_CONDITION_VARIABLE_TEST01_H

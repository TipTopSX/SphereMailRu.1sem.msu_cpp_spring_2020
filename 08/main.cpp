#include <iostream>
#include <chrono>
#include <thread>
#include "threadpool.hpp"

struct A
{
};

void foo(const A &)
{}

int bar(unsigned int ms)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);

    std::vector<typeof(pool.exec(bar, 0))> tasks;

    // Все работает, проверим что в несколько потоков спится быстрее
    auto start = std::chrono::high_resolution_clock::now();
    int sum = 0;
    for (int i = 8; i < 16; ++i)
        tasks.emplace_back(pool.exec(bar, i * 500));
    for (auto &task: tasks)
        sum += task.get();
    auto end = std::chrono::high_resolution_clock::now();
    assert(sum > std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() * 6);

    std::cout << "OK" << std::endl;
    return 0;
}

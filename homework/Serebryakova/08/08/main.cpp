#include <iostream>
#include <thread>
#include "ThreadPool.h"



struct A {};

void foo(const A &) {}


void test1() {
    ThreadPool pool(8);
    int s = 12;
    auto task1 = pool.exec([s]() { return s; });
    assert(task1.get() == 12);
}

void test2() {
    ThreadPool pool(8);
    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
}

void test3() {
    ThreadPool pool(8);
    auto task0 = pool.exec(foo, A());
    int s = 1;
    auto task1 = pool.exec([s]() { return s; });
    assert(task1.get() == 1);

    auto task2 = pool.exec([s]() { return s + 1; });
    assert(task2.get() == 2);

    auto task3 = pool.exec([s]() { return s + 2; });
    assert(task3.get() == 3);
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}

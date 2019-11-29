#include <iostream>
#include "vector.h"
#include <sstream>

void test1() {
    Vector<int> v(2);
    std::stringstream s;
    for (auto &x :v) {
        s << x;
    }
    assert(s.str() == "00");
}

void test2() {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::stringstream s;
    for(auto &x: v) {
        s << x;
    }
    assert(s.str() == "12345");
    v.clear();
    assert(v.size() == 0);
}

void test3() {
    Vector<int> v(5);
    v.resize(7);
    assert(v.size() == 7);
}

void test4() {
    Vector<int> v(5);
    std::stringstream s;
    for (auto it = v.begin(); it != v.end(); ++it) {
        s << *it;
    }
    assert(s.str() == "00000");
}
int main() {
    test1();
    test2();
    test3();
    test4();
}

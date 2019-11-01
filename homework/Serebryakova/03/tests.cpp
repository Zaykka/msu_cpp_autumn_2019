#include <iostream>
#include "header.h"


void test1() {
    Matrix m(4, 6);
    assert(m.getRows() == 4);
    assert(m.getColumns() == 6);
}

void test2() {
    Matrix m(4, 6);
    try {
        m[1][1] = 5;
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void test3() {
    Matrix m(3, 4);
    Matrix m1(2, 4);
    Matrix m2(3, 3);
    assert(m != m1);
    assert(m != m2);
    assert(!(m == m1));
    assert(!(m == m2));
    Matrix m4(3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            m[i][j] = 1;
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            m4[i][j] = 1;
        }
    }
    assert(m == m4);
    assert(!(m != m4));
}

void test4() {
    Matrix m(2, 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            m[i][j] = 1;
        }
    }
    Matrix m1(2, 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            m1[i][j] = 2;
        }
    }
    m *= 2;
    assert(m == m1);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
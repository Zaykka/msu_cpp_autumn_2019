#include <iostream>
#include "bigInt.h"
#include <limits.h>
#include <sstream>


void test1() {
    BigInt a = 123;
    BigInt b = 1;
    assert(a + b == 124);
    assert(a - b == 122);
}

void test2() {
    BigInt a = 3;
    BigInt b = 125;
    assert(a > b == false);
    assert(a < b == true);
    assert(a == b == false);
    assert(a != b == true);
    assert(a >= b == false);
    assert(a <= b == true);
}

int main() {
    test1();
    test2();
    return 0;
}
#include <iostream>
#include "allocator.h"

void test1() {
    LinearAllocator a(16);
    char *ptr = a.alloc(30);
    assert(ptr == nullptr);
    if ( ptr == nullptr) {
        std::cout << "test1 ";
    }
}
void test2() {
    LinearAllocator a(16);
    char* ptr1 = a.alloc(8);
    assert(ptr1 != nullptr);
    std::cout << ptr1 << std::endl;
    char* ptr2 = a.alloc(4);
    assert(ptr2 != nullptr);
    std::cout << ptr2 << std::endl;
    char* ptr3 = a.alloc(8);
    assert(ptr3 == nullptr);
    std::cout << "test2 " << std::endl;
}
void test3() {
    LinearAllocator a(16);
    char* ptr1 = a.alloc(8);
    char* ptr2 = a.alloc(4);
    a.reset();
    ptr2 = a.alloc(8);
    assert(ptr1 == ptr2);

}
void test4() {
    LinearAllocator a(16);
    char* ptr1 = a.alloc(8);
    for (int i = 0; i < 8; ++i) {
        ptr1[i] = 'i';
    }
    std::string s(ptr1, ptr1+8);
    assert(s == "iiiiiiii");
    std::cout << s << std::endl;
}
int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
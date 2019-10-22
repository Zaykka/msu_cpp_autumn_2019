#pragma once
#include <cstddef>

class LinearAllocator {
    char* mem;
    std::size_t offset;
    std::size_t maxSize;
public:
    LinearAllocator(std::size_t);
    char* alloc(std::size_t);
    void reset();
    ~LinearAllocator();
};

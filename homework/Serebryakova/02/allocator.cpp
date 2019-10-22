#include "allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) : maxSize(maxSize), offset(0) {
    mem = new char[maxSize];
};

char* LinearAllocator::alloc(std::size_t size) {
    size_t new_offset = offset + size;
    if (new_offset <= maxSize) {
        char*ptr = mem + size;
        offset = new_offset;
        return ptr;
    }
    return nullptr;
}

void LinearAllocator::reset() {
    offset = 0;
}

LinearAllocator::~LinearAllocator() {
    delete [] mem;
}


#include <cstdlib>
#include <iostream>
#include "lalloc.hpp"

int main()
{
    char *p;
    // Don't allocate if impossible
    makeAllocator(INT64_MAX);
    p=alloc(1);
    assert(!p);

    // Allocate all memory
    makeAllocator(123);
    p = alloc(123);
    std::cout << p;
    assert(p);
    // Check if reset working
    reset();
    p = alloc(123);
    assert(p);
    // Allocator overflow
    p=alloc(1);
    assert(!p);

    // Re-allocate
    makeAllocator(1024);
    p = alloc(1000);
    assert(p);
    p = alloc(16);
    assert(p);
    p = alloc(8);
    assert(p);
    p = alloc(1);
    assert(!p);
    std::cout << "Seems to work fine" << std::endl;
}
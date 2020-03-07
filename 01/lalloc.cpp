#include <new>
#include <iostream>
#include "lalloc.hpp"

size_t data_size = 0;
size_t offset = 0;

char *mem = nullptr;

void makeAllocator(size_t maxSize)
{
    if (!mem || maxSize != data_size) {
        delete[] mem;
        try {
            mem = new char[maxSize];
        }
        catch (std::bad_alloc &ba) {
            mem = nullptr;
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }
    }

    data_size = maxSize;
    offset = 0;
}

char *alloc(size_t size)
{
    if (mem == nullptr || (offset + size > data_size))
        return nullptr;
    offset += size;
    return static_cast<char *>(mem + offset - size);
}

void reset()
{
    offset = 0;
}
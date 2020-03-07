#pragma once

#ifndef MSU_CPP_SPRING_2020_LALLOC_HPP
#define MSU_CPP_SPRING_2020_LALLOC_HPP

#include <cstdlib>

void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();

#endif //MSU_CPP_SPRING_2020_LALLOC_HPP

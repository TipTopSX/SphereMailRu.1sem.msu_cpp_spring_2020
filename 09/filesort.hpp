#ifndef MSU_CPP_SPRING_2020_FILESORT_HPP
#define MSU_CPP_SPRING_2020_FILESORT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <cstdint>

using arr_type = uint64_t;

void print_file(const char *filename);

std::ifstream::pos_type file_size(const char *filename);

// Количество доступной памяти передается в функцию, ибо так удобнее и проще тестировать

void file_sort(const char *filename, const size_t mem_available);

void two_thread_sort(const char *in, const char *out, const size_t mem_available);

#endif //MSU_CPP_SPRING_2020_FILESORT_HPP

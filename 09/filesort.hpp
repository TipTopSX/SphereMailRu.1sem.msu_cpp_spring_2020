#ifndef MSU_CPP_SPRING_2020_FILESORT_HPP
#define MSU_CPP_SPRING_2020_FILESORT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <cstdint>

using arr_type = uint16_t;

void print_file(const char *filename);

std::ifstream::pos_type file_size(const char *filename);

void file_sort(const char *filename, const size_t mem_available);

#endif //MSU_CPP_SPRING_2020_FILESORT_HPP

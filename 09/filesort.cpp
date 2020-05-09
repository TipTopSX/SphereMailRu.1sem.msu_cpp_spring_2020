#include <thread>
#include "filesort.hpp"

void print_file(const char *filename)
{
    arr_type elem;
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    while (input) {
        input.read(reinterpret_cast<char *>(&elem), sizeof(elem));
        if (input)
            std::cout << elem << '\t';
    }
    std::cout << std::endl;
}

std::ifstream::pos_type file_size(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void split_file(const char *filename, const char *out_name1, const char *out_name2)
{
    auto fsize = file_size(filename);
    auto elem_count = fsize / sizeof(arr_type);
    auto split = elem_count / 2;
    arr_type elem;

    std::ifstream input(filename, std::ios::in | std::ios::binary);
    std::ofstream output1(out_name1, std::ios::out | std::ios::binary);
    for (auto i = 0; i < split; ++i) {
        input.read(reinterpret_cast<char *>(&elem), sizeof(elem));
        output1.write(reinterpret_cast<const char *>(&elem), sizeof(elem));
    }
    output1.close();
    std::ofstream output2(out_name2, std::ios::out | std::ios::binary);
    for (auto i = split; i < elem_count; ++i) {
        input.read(reinterpret_cast<char *>(&elem), sizeof(elem));
        output2.write(reinterpret_cast<const char *>(&elem), sizeof(elem));
    }
    output2.close();
    input.close();
}

void merge_sorted(const char *in1_name, const char *in2_name, const char *out_name)
{
    std::ifstream input1(in1_name, std::ios::in | std::ios::binary);
    std::ifstream input2(in2_name, std::ios::in | std::ios::binary);
    std::ofstream result(out_name, std::ios::out | std::ios::binary);
    arr_type elem, elem1, elem2;
    input1.read(reinterpret_cast<char *>(&elem1), sizeof(elem1));
    input2.read(reinterpret_cast<char *>(&elem2), sizeof(elem2));
    while (input1 || input2) {
        if (!input1) {
            elem = elem2;
            input2.read(reinterpret_cast<char *>(&elem2), sizeof(elem2));
        } else if (!input2 || (elem1 <= elem2)) {
            elem = elem1;
            input1.read(reinterpret_cast<char *>(&elem1), sizeof(elem1));
        } else {
            elem = elem2;
            input2.read(reinterpret_cast<char *>(&elem2), sizeof(elem2));
        }
        result.write(reinterpret_cast<const char *>(&elem), sizeof(elem));
    }
    input1.close();
    input2.close();
    result.close();
    std::remove(in1_name);
    std::remove(in2_name);
}

void file_sort(const char *filename, const size_t mem_available)
{
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    auto fsize = file_size(filename);
    if (fsize % sizeof(arr_type))
        throw std::runtime_error("corrupted file");
    arr_type elem;
    auto elem_count = fsize / sizeof(arr_type);
    std::vector<arr_type> elems;
    // Сортируем все, что влезает в память
    if (fsize <= mem_available) {
        for (size_t i = 0; i < elem_count; ++i) {
            input.read(reinterpret_cast<char *>(&elem), sizeof(elem));
            elems.push_back(elem);
        }
        input.close();
        std::sort(elems.begin(), elems.end());
        std::ofstream output(filename, std::ios::out | std::ios::binary);
        for (auto const &buf: elems) {
            output.write(reinterpret_cast<const char *>(&buf), sizeof(buf));
        }
        output.close();
        // Все, что не влезает, разбиваем пополам для merge sort
    } else {
        input.close();
        std::string out_name1(filename);
        out_name1.append("1");
        std::string out_name2(filename);
        out_name2.append("2");
        split_file(filename, out_name1.c_str(), out_name2.c_str());

        file_sort(out_name1.c_str(), mem_available);
        file_sort(out_name2.c_str(), mem_available);
        merge_sorted(out_name1.c_str(), out_name2.c_str(), filename);
    }
}

void two_thread_sort(const char *in, const char *out, const size_t mem_available)
{
    auto mem_for_thread = mem_available / 2;
    auto out1 = std::string(out) + "1";
    auto out2 = std::string(out) + "2";
    split_file(in, out1.c_str(), out2.c_str());

    auto th1 = std::thread([&](){
        file_sort(out1.c_str(), mem_for_thread);
    });
    auto th2 = std::thread([&](){
        file_sort(out2.c_str(), mem_for_thread);
    });
    th1.join();
    th2.join();
    merge_sorted(out1.c_str(), out2.c_str(), out);
}
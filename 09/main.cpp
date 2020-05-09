#include "filesort.hpp"

void generate_random_file(const char *filename, size_t num)
{
    std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
    std::ofstream data(filename, std::ios::out | std::ios::binary);
    char buf[sizeof(arr_type) / sizeof(char)];
    for (size_t i = 0; i < num; ++i) {
        urandom.read(buf, sizeof(arr_type));
        data.write(buf, sizeof(arr_type));
    }
    urandom.close();
    data.close();
}

int main()
{
    arr_type prev, next;
    const char *iname = "data";
    const char *oname = "out";

    generate_random_file("data", 100000);
    two_thread_sort("data", oname, 1024);
    assert(file_size(iname) == file_size(oname));

    bool sorted = true;
    std::ifstream input(oname, std::ios::in | std::ios::binary);
    input.read(reinterpret_cast<char *>(&prev), sizeof(prev));
    while (input.good()) {
        input.read(reinterpret_cast<char *>(&next), sizeof(next));
        if (prev > next) {
            sorted = false;
            break;
        }
        prev = next;
    }
    input.close();
    assert(sorted);
    std::cout << "OK" << std::endl;
    return 0;
}
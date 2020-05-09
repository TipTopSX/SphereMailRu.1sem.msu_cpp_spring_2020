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
    generate_random_file("data", 20);
    std::cout << file_size("data") << std::endl;
    print_file("data");
    file_sort("data", 16);
    std::cout << file_size("data") << std::endl;
    print_file("data");
    std::ifstream input("data", std::ios::in | std::ios::binary);
    input.read(reinterpret_cast<char *>(&prev), sizeof(prev));
    while (input.good()) {
        input.read(reinterpret_cast<char *>(&next), sizeof(next));
        if (prev > next) {
            std::cout << "unsorted" << std::endl;
            break;
        }
        prev = next;
    }
    input.close();
    return 0;
}
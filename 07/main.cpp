#include "vector.hpp"
#include <sstream>

template<class T>
auto vec_str(T &vec)
{
    std::stringstream s;
    for (auto &x:vec)
        s << x;
    return s.str();
}

int main()
{
    Vector<int> vec(2);
    assert(vec_str(vec) == "00");
    vec.clear();
    assert(vec.empty());
    for (int i = 1; i < 9; ++i)
        vec.push_back(i);
    assert(vec_str(vec) == "12345678");
    vec.pop_back();
    assert(vec_str(vec) == "1234567");
    for (int i = 1; i < 9; ++i)
        vec.push_back(i * 10);
    assert(vec.size() == 15);
    assert(vec.capacity() == 16);

    std::stringstream s;
    for (auto it = vec.begin(); it < vec.end(); ++it)
        s << *it;
    assert(s.str() == "12345671020304050607080");
    s.str("");
    for (auto it = vec.rbegin(); it < vec.rend(); ++it)
        s << *it;
    assert(s.str() == "80706050403020107654321");
    vec.resize(9);
    assert(vec_str(vec) == "12345671020");
    vec.resize(12);
    assert(vec_str(vec) == "12345671020000");
    std::cout << "OK" << std::endl;
}
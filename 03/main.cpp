#include <cassert>
#include <iostream>
#include "matrix.hpp"

int main()
{
    Matrix m(5, 3);
    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
    m[0][0] = 4;
    m[1][2] = 77;
    bool exceptionThrown = false;
    try {
        m[3][8] = 4;
    } catch (std::out_of_range &e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    assert(m[1][2] == 77);

    auto x = m * 4;
    auto y = 4 * m;
    assert(m == m);
    assert(x == y);
    assert(x != m);

    m *= 3;
    assert(m[1][2] == 77 * 3);
    std::cout << "OK" << std::endl;
}
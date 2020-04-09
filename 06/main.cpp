#include <iostream>
#include "format.hpp"

#define assert_error(expression, message) {\
    test.str("");\
    try {\
        expression;\
    } catch (const std::runtime_error &e) {\
        test << e.what();\
    }\
    assert(test.str() == message);\
}

int main()
{
    assert(format("").empty());
    assert(format("bdjsk") == "bdjsk");
    assert(format("123{1}{2}{3}", 4, 8 ,12, "asd") == "123812asd");
    assert(format("{1} + {1} = {0}", 2, "one") == "one + one = 2");

    std::stringstream test;
    assert_error(format("some bad string {", 1), "empty braces or end of string");
    assert_error(format("{}", 1), "empty braces or end of string");
    assert_error(format("{0} }", 1), "unexpected closing brace");
    assert_error(format("{0} {NaN}", 1), "not a number");
    assert_error(format("{0} {12{}", 1), "not a number");
    assert_error(format("{0} {12}", 1), "index out of range");
    std::cout << "OK" << std::endl;
}
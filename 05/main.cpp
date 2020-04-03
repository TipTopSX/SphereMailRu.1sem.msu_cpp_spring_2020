#include "bigint.hpp"
#include <iostream>
#include <sstream>

int main()
{
    // Тест инициализации и вывода в поток
    const int numbers[9] = {0, 1, -1, 9, -9, 33, -33, 100500, -100500};
    std::stringstream ss_bigint, ss_int;
    for (int number : numbers) {
        ss_bigint << BigInt(number);
        ss_int << number;
    }
    assert(ss_bigint.str() == ss_int.str());

    // Тест сравнений
    ss_bigint.str(std::string());
    ss_int.str(std::string());
    for (int num1 : numbers) {
        for (int num2 : numbers) {
            ss_bigint << (BigInt(num1) < BigInt(num2));
            ss_int << (num1 < num2);
            ss_bigint << (BigInt(num1) <= BigInt(num2));
            ss_int << (num1 <= num2);
            ss_bigint << (BigInt(num1) > BigInt(num2));
            ss_int << (num1 > num2);
            ss_bigint << (BigInt(num1) >= BigInt(num2));
            ss_int << (num1 >= num2);
            ss_bigint << (BigInt(num1) == BigInt(num2));
            ss_int << (num1 == num2);
            ss_bigint << (BigInt(num1) != BigInt(num2));
            ss_int << (num1 != num2);
        }
    }
    assert(ss_bigint.str() == ss_int.str());

    // Тест арифметических операций
    ss_bigint.str(std::string());
    ss_int.str(std::string());
    for (int num1 : numbers) {
        for (int num2 : numbers) {
            ss_bigint << (BigInt(num1) + BigInt(num2));
            ss_int << (num1 + num2);
            ss_bigint << (BigInt(num1) - BigInt(num2));
            ss_int << (num1 - num2);
        }
    }
    assert(ss_bigint.str() == ss_int.str());

    std::cout << "OK" << std::endl;
    return 0;
}
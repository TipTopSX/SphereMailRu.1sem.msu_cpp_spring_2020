#ifndef MSU_CPP_SPRING_2020_BIGINT_HPP
#define MSU_CPP_SPRING_2020_BIGINT_HPP
#pragma once

#include <cstdlib>
#include <iostream>

class BigInt
{
    constexpr static int base = 10;
    using digit_t = u_int8_t;
    digit_t *num;
    size_t size;
    bool positive;

    BigInt(size_t new_size, bool new_positive);

    BigInt plus(const BigInt &other) const;

    BigInt minus(const BigInt &other) const;

    int abs_cmp(const BigInt &other) const;

public:
    BigInt();

    BigInt(const BigInt &copied);

    BigInt(int n);

    ~BigInt();

    friend std::ostream &operator<<(std::ostream &out, const BigInt &val);

    BigInt operator-() const;

    BigInt operator+(const BigInt &other) const;

    BigInt operator-(const BigInt &other) const;

    bool operator==(const BigInt &other) const;

    bool operator!=(const BigInt &other) const;

    bool operator>(const BigInt &other) const;

    bool operator>=(const BigInt &other) const;

    bool operator<(const BigInt &other) const;

    bool operator<=(const BigInt &other) const;

    friend BigInt operator+(const int number, const BigInt &bignumber);

    friend BigInt operator-(const int number, const BigInt &bignumber);

    friend BigInt operator==(const int number, const BigInt &bignumber);

    friend BigInt operator!=(const int number, const BigInt &bignumber);

    friend BigInt operator>(const int number, const BigInt &bignumber);

    friend BigInt operator>=(const int number, const BigInt &bignumber);

    friend BigInt operator<(const int number, const BigInt &bignumber);

    friend BigInt operator<=(const int number, const BigInt &bignumber);
};


#endif //MSU_CPP_SPRING_2020_BIGINT_HPP

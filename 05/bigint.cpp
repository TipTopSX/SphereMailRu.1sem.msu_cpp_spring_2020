#include "bigint.hpp"

BigInt::BigInt() : num(nullptr), size(0), positive(true)
{}

BigInt::BigInt(const BigInt &copied) : num(new digit_t[copied.size]), size(copied.size)
{
    positive = copied.positive;
    std::copy(copied.num, copied.num + size, num);
}

BigInt::BigInt(int n)
{
    if (n == 0) {
        size = 1;
        positive = true;
        num = new digit_t[1];
        num[0] = 0;
    } else {
        size = 0;
        positive = n > 0;
        if (n < 0)
            n = -n;
        int tmp = n;
        for (size = 0; tmp; ++size)
            tmp /= base;
        num = new digit_t[size];
        for (int i = 0; i < size; ++i) {
            num[i] = n % base;
            n /= base;
        }
    }
}

BigInt::BigInt(size_t new_size, bool new_positive)
{
    size = new_size;
    positive = new_positive;
    num = new digit_t[size];
}


BigInt::~BigInt()
{
    delete[] num;
}

std::ostream &operator<<(std::ostream &out, const BigInt &val)
{
    if (!val.positive) {
        out << '-';
    }
    for (size_t i = val.size; i > 0; --i) {
        out << static_cast<char>(val.num[i - 1] + '0');
    }
    return out;
}

BigInt BigInt::operator-() const
{
    auto result = BigInt(*this);
    result.positive = !result.positive;
    return result;
}

BigInt BigInt::plus(const BigInt &other) const
{
    size_t new_size = std::max(this->size, other.size) + 1;
    BigInt result(new_size, this->positive);
    digit_t l, r;
    int sum, carry = 0;
    for (size_t i = 0; i < new_size - 1; ++i) {
        l = i < this->size ? this->num[i] : 0;
        r = i < other.size ? other.num[i] : 0;
        sum = l + r + carry;
        result.num[i] = sum % base;
        carry = sum / base;
    }
    if (carry > 0)
        result.num[this->size] = carry;
    else
        result.size -= 1;
    return result;
}

BigInt BigInt::minus(const BigInt &other) const
{
    BigInt result(this->size, this->positive);
    int diff, carry = 0;
    digit_t r;
    for (size_t i = 0; i < this->size; ++i) {
        r = i < other.size ? other.num[i] : 0;
        diff = this->num[i] - r + carry;
        if (diff < 0) {
            diff += base;
            carry = -1;
        } else
            carry = 0;
        result.num[i] = diff;
    }
    if (result.num[result.size - 1] == 0)
        result.size -= 1;
    return result;
}

int BigInt::abs_cmp(const BigInt &other) const
{
    // 1 if greater than other, 0 if equal, -1 if less
    if (this->size > other.size)
        return 1;
    else if (this->size < other.size)
        return -1;
    else {
        for (size_t i = this->size; i > 0; --i) {
            if (this->num[i - 1] > other.num[i - 1])
                return 1;
            else if (this->num[i - 1] < other.num[i - 1])
                return -1;
        }
        return 0;
    }
}

BigInt BigInt::operator+(const BigInt &other) const
{
    if (this->positive == other.positive) {
        return plus(other);
    } else {
        switch (abs_cmp(other)) {
        case 0:
            return BigInt(0);
        case 1:
            return minus(other);
        case -1:
            return other.minus(*this);
        }
    }
    // Сюда программа не заходит, но компилятор все равно ругается
    return BigInt(0);
}

BigInt BigInt::operator-(const BigInt &other) const
{
    if (this->positive == other.positive) {
        switch (abs_cmp(other)) {
        case 0:
            return BigInt(0);
        case 1:
            return minus(other);
        case -1:
            auto result = other.minus(*this);
            result.positive = !result.positive;
            return result;
        }
    } else {
        return plus(other);
    }
    // Сюда программа не заходит, но компилятор все равно ругается
    return BigInt(0);
}

bool BigInt::operator==(const BigInt &other) const
{
    return ((this == &other) ||
            (this->positive == other.positive && this->size == other.size && abs_cmp(other) == 0));
}

bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

bool BigInt::operator>(const BigInt &other) const
{
    if (this->positive != other.positive)
        return this->positive;
    int cmp = abs_cmp(other);
    if (this->positive)
        return cmp > 0;
    else
        return cmp < 0;
}

bool BigInt::operator>=(const BigInt &other) const
{
    if (this->positive != other.positive)
        return this->positive;
    int cmp = abs_cmp(other);
    if (this->positive)
        return cmp >= 0;
    else
        return cmp <= 0;
}

bool BigInt::operator<(const BigInt &other) const
{
    return (other > *this);
}

bool BigInt::operator<=(const BigInt &other) const
{
    return (other >= *this);
}

BigInt operator+(const int number, const BigInt &bignumber)
{
    return bignumber + number;
}

BigInt operator-(const int number, const BigInt &bignumber)
{
    return BigInt(number) - bignumber;
}

BigInt operator==(const int number, const BigInt &bignumber)
{
    return bignumber == number;
}

BigInt operator!=(const int number, const BigInt &bignumber)
{
    return bignumber != number;
}

BigInt operator>(const int number, const BigInt &bignumber)
{
    return BigInt(number) > bignumber;
}

BigInt operator>=(const int number, const BigInt &bignumber)
{
    return BigInt(number) >= bignumber;
}

BigInt operator<(const int number, const BigInt &bignumber)
{
    return BigInt(number) < bignumber;
}

BigInt operator<=(const int number, const BigInt &bignumber)
{
    return BigInt(number) <= bignumber;
}

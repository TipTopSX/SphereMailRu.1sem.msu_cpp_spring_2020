#include <stdexcept>
#include "matrix.hpp"

Matrix::Matrix(size_t rowCount, size_t colCount)
{
    rows = rowCount;
    cols = colCount;
    matrix = new int[rowCount * colCount];
}

Matrix::~Matrix()
{
    delete[] matrix;
}

size_t Matrix::getRows()
{
    return rows;
}

size_t Matrix::getColumns()
{
    return cols;
}

Matrix::Row::Row(int *matrix, size_t rowNum, size_t colCount)
{
    row = matrix + rowNum * colCount;
    cols = colCount;
}

Matrix::Row Matrix::operator[](size_t i)
{
    if (i >= rows)
        throw std::out_of_range("");
    return Matrix::Row(matrix, i, cols);
}

const Matrix::Row Matrix::operator[](size_t i) const
{
    if (i >= rows)
        throw std::out_of_range("");
    const auto result = Matrix::Row(matrix, i, cols);
    return result;
}

Matrix Matrix::operator*(const int num) const
{
    auto result = Matrix(rows, cols);
    for (size_t i = 0; i < rows * cols; ++i) {
        result.matrix[i] = this->matrix[i] * num;
    }
    return result;
}

Matrix operator*(const int num, const Matrix &m)
{
    return m * num;
}

Matrix &Matrix::operator*=(const int num)
{
    for (size_t i = 0; i < rows * cols; ++i) {
        this->matrix[i] *= num;
    }
    return *this;
}

bool Matrix::operator==(const Matrix &other) const
{
    if (this == &other)
        return true;

    for (size_t i = 0; i < rows * cols; ++i)
        if (matrix[i] != other.matrix[i])
            return false;

    return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

int &Matrix::Row::operator[](size_t i)
{
    if (i >= cols)
        throw std::out_of_range("");
    return row[i];
}

int Matrix::Row::operator[](size_t i) const
{
    if (i >= cols)
        throw std::out_of_range("");
    return row[i];
}

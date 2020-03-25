#include <cstddef>

#ifndef MSU_CPP_SPRING_2020_MATRIX_HPP
#define MSU_CPP_SPRING_2020_MATRIX_HPP

#endif //MSU_CPP_SPRING_2020_MATRIX_HPP

class Matrix
{
    int *matrix;
    size_t rows, cols;
public:
    Matrix(int rowCount, int colCount);

    ~Matrix();

    size_t getRows();

    size_t getColumns();

    Matrix operator*(int num) const;

    friend Matrix operator*(int num, const Matrix &m);

    Matrix &operator*=(int num);

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    class Row
    {
        int *row;
        int cols;
    public:
        Row(int *matrix, size_t rowNum, size_t colCount);

        int &operator[](size_t i);
    };

    Row operator[](size_t i) const;
};

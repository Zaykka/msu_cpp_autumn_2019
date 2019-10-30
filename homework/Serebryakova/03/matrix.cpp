#include <iostream>
#include "header.h"

Matrix::Row::Row(int* arr, size_t cols): arr(arr), len(cols) {}

int& Matrix::Row::operator[](const size_t j) {
    if (j >= len) {
        throw std::out_of_range("");
    }
    return arr[j];
}

Matrix::Row::~Row() =default;

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    ptr = new int*[rows];
    for (int i = 0; i < rows; ++i){
        ptr[i] = new int [cols];
    }
}

    Matrix::Row Matrix::operator[](const size_t i) {
    if (i >= rows) {
        throw std::out_of_range("");
    }
    return Matrix::Row(ptr[i], cols);
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getColumns() const {
    return cols;
}

Matrix& Matrix::operator*=(const int val) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            ptr[i][j] *= val;
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other) {
        return true;
    }
    if (getColumns() != other.getColumns() ||
        getRows() != other.getRows()) {
        return false;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (ptr[i][j] != other.ptr[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete [] ptr[i];
    }
    delete ptr;
}



#pragma once

#include <stdexcept>
#include <iostream>
#include "pair.h"

template<typename T, int N = 1>
class Matrix {
public:
    Matrix() {
        array = new T *[N];
        for (int i = 0; i < N; ++i) array[i] = new T[N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                array[i][j] = {};
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < N; ++i) delete[] array[i];
        delete[] array;
    }

    void set(Pair<int, int> p, T value) {
        if (p.first < 0 || p.first >= N || p.second < 0 || p.second >= N)
            throw std::runtime_error("Index out of bounds");
        array[p.first][p.second] = value;
    }

    T &get(Pair<int, int> p) const {
        return array[p.first][p.second];
    }

    Matrix<T, N> operator+(const Matrix<T, N> &other) {
        Matrix<T, N> newMatrix;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                newMatrix.array[i][j] = array[i][j] + other.array[i][j];
            }
        }
        return newMatrix;
    }

    Matrix<T, N> operator-(const Matrix<T, N> &other) {
        Matrix<T, N> newMatrix;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                newMatrix.array[i][j] = array[i][j] - other.array[i][j];
            }
        }
        return newMatrix;
    }

    Matrix<T, N> operator*(const Matrix<T, N> &other) {
        Matrix<T, N> newMatrix;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    newMatrix.array[i][j] = array[j][k] * other.array[k][j];
                }
            }
        }
        return newMatrix;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix &obj) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                out << obj.array[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

private:
    T **array;
};
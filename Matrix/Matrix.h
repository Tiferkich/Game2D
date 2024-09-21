

#ifndef GAMELAB3_MATRIX_H
#define GAMELAB3_MATRIX_H

#include <iostream>
#include <vector>
#include <functional>


template<typename T>
class Matrix {
public:

    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        if (rows < 0 || cols < 0) throw std::invalid_argument("error indexes");
        data = new T *[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    }

    Matrix(std::vector<std::vector<T>> vector, int rows, int cols) : rows_(rows), cols_(cols) {
        data = new T *[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = vector[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows_; i++) {
            delete[] data[i];
        }
        delete[] data;
    }


    class Iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
    public:

        Iterator(Matrix<value_type> &matrix, int row, int col) : matrix(matrix),
                                                                 row(row),
                                                                 col(col), predicateFunc(alwaysTruePredicate) {}

        Iterator(Matrix<value_type> &matrix, int row, int col, std::function<bool(const T &)> predicateFunc) : matrix(
                matrix),
                                                                                                               row(row),
                                                                                                               col(col),
                                                                                                               predicateFunc(
                                                                                                                       predicateFunc) {}

        bool operator==(const Iterator &other) const {
            return row == other.row && col == other.col;
        }

        bool operator!=(const Iterator &other) const {
            return row != other.row || col != other.col;
        }

        reference operator*() {
            return matrix.data[row][col];
        }

        Iterator &operator++() {
            do {

                col++;
                if (col == matrix.cols_) {
                    col = 0;
                    row++;
                }
                if (col == 0 && row == matrix.rows_) break;
            } while (!predicateFunc(*(*this)));
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        Matrix<value_type> &matrix;
        int row;
        int col;
        std::function<bool(const T &)> predicateFunc;
    };

    Iterator begin(std::function<bool(const T &)> predicateFunc = alwaysTruePredicate) {
        Iterator iter(*this, 0, 0, predicateFunc);
        while (!predicateFunc(*iter)) {
            ++iter;
        }
        return iter;
    }


    Iterator end() {
        return Iterator(*this, rows_, 0);
    }


private:
    int rows_ = 0;
    int cols_ = 0;
    T **data = NULL;


public:
    static bool alwaysTruePredicate(const T &value) {
        return true;
    }

    friend Iterator;

    Matrix(const Matrix &anoter) noexcept: rows_(anoter.rows_), cols_(anoter.cols_) {
        data = new T *[rows_];
        for (int i = 0; i < rows_; i++) {
            data[i] = new T[cols_];
            for (int j = 0; j < cols_; j++) {
                data[i][j] = anoter.data[i][j];
            }
        }

    };

    Matrix &operator=(const Matrix &anoter) {
        if (this != &anoter) {
            for (int i = 0; i < rows_; i++) {
                delete[] data[i];
            }
            delete[] data;

            rows_ = anoter.rows_;
            cols_ = anoter.cols_;
            data = new T *[rows_];
            for (int i = 0; i < rows_; i++) {
                data[i] = new T[cols_];
                for (int j = 0; j < cols_; j++) {
                    data[i][j] = anoter.data[i][j];
                }
            }
        }
        return *this;
    }

    Matrix(Matrix &&another) noexcept: rows_(another.rows_), cols_(another.cols_), data(std::move(another.data)) {
        another.rows_ = 0;
        another.cols_ = 0;
        another.data = NULL;
    }

    Matrix &operator=(Matrix &&another) noexcept {
        rows_ = another.rows_;
        cols_ = another.cols_;
        data = another.data;
        another.data = NULL;
        another.rows_ = 0;
        another.cols_ = 0;
        return *this;
    }

    void deleteCol(int indexCol) {
        if (indexCol > cols_ || indexCol < 0) throw std::runtime_error("Bad index");
        for (int i = 0; i < rows_; i++) {
            for (int j = indexCol; j < cols_ - 1; j++) {
                std::swap(data[i][j], data[i][j + 1]);
            }
        }
        T **newdata = new T *[rows_];
        for (int i = 0; i < rows_; i++) {
            newdata[i] = new T[cols_ - 1];
            for (int j = 0; j < cols_ - 1; j++) {
                newdata[i][j] = data[i][j];
            }
        }
        for (int i = 0; i < rows_; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = newdata;
        --cols_;
    }

    void deleteRow(int indexRow) {
        if (indexRow > rows_ || indexRow < 0) throw std::runtime_error("Bad index");
        for (int i = indexRow; i < rows_ - 1; i++) {
            std::swap(data[i], data[i + 1]);
        }
        T **newdata = new T *[rows_ - 1];
        for (int i = 0; i < rows_ - 1; i++) {
            newdata[i] = new T[cols_];
            for (int j = 0; j < cols_; j++) {
                newdata[i][j] = data[i][j];
            }
        }
        for (int i = 0; i < rows_; i++) {
            delete[] data[i];
        }
        delete[] data;
        --rows_;
        data = newdata;
    }

    void addRow(int indexRow) {
        if (indexRow > rows_ || indexRow < 0) throw std::runtime_error("Bad index");
        T **newData = new T *[rows_ + 1];
        bool flag = false;
        for (int i = 0; i < rows_ + 1; i++) {
            newData[i] = new T[cols_];
            for (int j = 0; j < cols_; j++) {
                if (i == indexRow) {
                    newData[i][j] = 0;
                    flag = true;
                    continue;
                }
                if (!flag)
                    newData[i][j] = data[i][j];
                else
                    newData[i][j] = data[i - 1][j];
            }
        }
        for (int i = 0; i < rows_; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = newData;
        ++rows_;
    }

    void addCol(int indexCol) {
        if (indexCol > rows_ || indexCol < 0) throw std::runtime_error("Bad index");
        T **newData = new T *[rows_];
        for (int i = 0; i < rows_; i++) {
            newData[i] = new T[cols_ + 1];
            bool flag = false;
            for (int j = 0; j < cols_ + 1; j++) {
                if (j == indexCol) {
                    newData[i][j] = 0;
                    flag = true;
                    continue;
                }
                if (!flag)
                    newData[i][j] = data[i][j];
                else
                    newData[i][j] = data[i][j - 1];
            }
        }
        for (int i = 0; i < rows_; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = newData;
        cols_++;
    }


    int rows() { return rows_; }

    int cols() { return cols_; }

    class Proxy {
    private:
        Matrix &parent;
        int row;
        friend Matrix;

        explicit Proxy(Matrix &parent, int row_) : row(row_), parent(parent) {};
    public:

        T &operator[](int col) {
            if (0 > col || col > parent.cols_) throw (std::invalid_argument("Not good col"));
            return parent.data[row][col];
        }

        const T &operator[](int col) const {
            if (0 > col || col > parent.cols_) throw (std::invalid_argument("Not good col"));
            return parent.data[row][col];
        }
    };

    Proxy operator[](int row) const {
        if (0 > row || row > rows_) throw (std::invalid_argument("Not good row"));
        return Proxy(*this, row);
    }

    Proxy operator[](int row) {
        if (0 > row || row > rows_) throw (std::invalid_argument("Not good row"));
        return Proxy(*this, row);
    }

};


#endif


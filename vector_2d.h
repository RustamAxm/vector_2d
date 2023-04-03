#pragma once

#include <vector>
#include <utility>
#include <stdexcept>


template <typename Type>
class Vector2D {
public:
    Vector2D() = default;
    explicit Vector2D(size_t m, size_t n) : cols_(m), rows_(n) {
        for (size_t i = 0; i < cols_; ++i) {
            vector2d_.reserve(rows_);
        }
    }

    Vector2D(size_t m, size_t n, Type value) : cols_(m), rows_(n) {
        for (size_t i = 0; i < cols_; ++i) {
            std::vector<Type> tmp;
            for (size_t j = 0; j < rows_; ++j) {
                tmp.push_back(value);
            }
            vector2d_.push_back(tmp);
        }
    }

    Vector2D(Vector2D<Type> & other) {
        auto tmp = copy(other);
        swap(tmp);
    }

    Vector2D(Vector2D<Type> && other) {
        vector2d_ = std::move(other.vector2d_);
        cols_ = std::move(other.cols_);
        rows_ = std::move(other.rows_);
    }

    class Proxy {
    public:
        Proxy(std::vector<Type> vec, size_t index) : vec_(vec), index_(index) {}

        Type& operator[](size_t index) {
            return vec_[index];
        }
        Type& operator=(const Type & other) {
            Type tmp = other;
            std::swap(vec_[index_], tmp);
            return vec_[index_];
        }
    private:
        std::vector<Type> vec_;
        size_t index_;
    };

    Proxy operator[](size_t index) {
        return Proxy(vector2d_[index], index);
    }

    Type& operator()(size_t x, size_t y) {
        if (!isValidCol(x)) {
            throw std::invalid_argument("out of range cols");
        }

        if (!isValidRow(y)) {
            throw std::invalid_argument("out of range rows");
        }
        return vector2d_[x][y];
    }

    Vector2D& operator=(const Vector2D& rhs) {
        if (this != &rhs) {
            Vector2D<Type> rhs_copy(rhs);
            swap(rhs_copy);
        }
        return *this;
    }

    Vector2D& operator=(Vector2D && rhs) {
        swap(rhs);
        return *this;
    }

    Vector2D operator|(const Vector2D & rhs) {
        Vector2D tmp(*this);
        for (size_t i = 0; i < cols_ || i < rhs.cols_; ++i) {
            tmp.vector2d_[i].insert(tmp.vector2d_[i].end(),
                                    rhs.vector2d_[i].begin(),
                                    rhs.vector2d_[i].end());
        }
        tmp.cols_ += rhs.cols_;

        return tmp;
    }

    Vector2D operator+(const Vector2D & rhs) {
        if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
            throw std::invalid_argument("not same rows or cols");
        }
        Vector2D tmp(cols_, rows_, 0);
        for (size_t i = 0; i < cols_; ++i) {
            for (size_t j = 0; j < rows_; ++j) {
                tmp.vector2d_[i][j] = vector2d_[i][j] + rhs.vector2d_[i][j];
            }
        }
        return tmp;
    }

    Vector2D & operator+=(const Vector2D & rhs) {
        Vector2D tmp = *this + rhs;
        swap(tmp);
        return *this;
    }

    std::vector<Type> GetColumn(size_t index) const {
        if (!isValidCol(index)) {
            throw std::invalid_argument("out of range cols");
        }
        return vector2d_.at(index);
    }

    std::vector<Type> GetRow(size_t index) {
        if (!isValidRow(index)) {
            throw std::invalid_argument("out of range rows");
        }

        std::vector<Type> to_return;
        for (size_t j = 0; j < rows_; ++j) {
            to_return.push_back(vector2d_.at(j).at(index));
        }
        return to_return;
    };

    size_t GetRows_size() {
        return rows_;
    }

    size_t GetCols_size() {
        return cols_;
    }

    using cols_it = std::vector< std::vector<Type> >::iterator;

    cols_it begin() {
        return vector2d_.begin();
    }

    cols_it end() {
        return vector2d_.end();
    }

private:

    std::vector<std::vector<Type>> vector2d_;
    size_t cols_ = 0;
    size_t rows_ = 0;

    bool isValidRow(const size_t index) const {
        return index < rows_;
    }

    bool isValidCol(const size_t index) const {
        return index < cols_;
    }

    Vector2D<Type> copy(const Vector2D & other) {
        Vector2D tmp;
        for (size_t i = 0; i < other.cols_; ++i) {
            tmp.vector2d_.push_back(other.GetColumn(i));
        }
        tmp.cols_ = other.cols_;
        tmp.rows_ = other.rows_;
        return tmp;
    }

    void swap(Vector2D<Type> & other) {
        std::swap(vector2d_, other.vector2d_);
        std::swap(cols_, other.cols_);
        std::swap(rows_, other.rows_);
    }

};



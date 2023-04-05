#pragma once

#include <vector>
#include <utility>
#include <unordered_map>

struct index {
public:
    index(std::size_t x, std::size_t y) : x_(x), y_(y) {}
    std::size_t x_;
    std::size_t y_;
    bool operator==(const index & rhs) const {
        return x_ == rhs.x_ && y_ == rhs.y_;
    }
};

class Hasher {
public:
    std::size_t operator()(const index ind) const {
        std::size_t h1 = std::hash<std::size_t>()(ind.x_);
        return std::hash<std::size_t>()(ind.y_) ^ (h1 << 1);
    }
};

template <typename Type>
class Array2D_umap {
public:
    Array2D_umap() = default;
    Array2D_umap(size_t m, size_t n) : cols_(m), rows_(n) {
    }
    Array2D_umap(size_t m, size_t n, const Type value) : cols_(m), rows_(n) {

        for (size_t i = 0; i < cols_; i++) {
            for (size_t j = 0; j < rows_; ++j) {
                index index_(i, j);
                arr_[index_] = value;
            }
        }
    }
    Array2D_umap(const Array2D_umap & other) {
        auto tmp = copy(other);
        swap(tmp);
    }

    Array2D_umap(Array2D_umap && other) {
        arr_ = std::move(other.arr_);
        cols_ = std::move(other.cols_);
        rows_ = std::move(other.rows_);
    }

    Array2D_umap & operator=(const Array2D_umap & rhs) {
        if (this != rhs) {
            Array2D_umap rhs_copy(rhs);
            swap(rhs_copy);
        }
        return *this;
    }

    Array2D_umap & operator=(Array2D_umap && rhs) {
        swap(rhs);
        return *this;
    }

    class Proxy {
    public:
        Proxy(std::vector<Type> vec, size_t index) : vec_(vec), index_(index) {}

        Type& operator[](size_t index) {
            return vec_[index];
        }
        Type& operator=(Type other) {
            return vec_[index_] = other;
        }
    private:
        std::vector<Type> vec_;
        size_t index_;
    };

    Proxy operator[](size_t index) {
        return Proxy();
    }

    ~Array2D_umap() = default;

private:

    std::unordered_map<index, Type, Hasher> arr_;
    size_t rows_;
    size_t cols_;


    Array2D_umap copy(const Array2D_umap & other) {
        Array2D_umap<Type> tmp;
        for (size_t i = 0; i < other.cols_; i++) {
            for (size_t j = 0; j < other.rows_; ++j) {
                index index_(i, j);
                tmp.arr_[index_] = other.arr_.at(index_);
            }
        }
        tmp.rows_ = other.rows_;
        tmp.cols_ = other.cols_;
        return tmp;
    }

    void swap(Array2D_umap & other) {
        std::swap(arr_, other.arr_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }
};
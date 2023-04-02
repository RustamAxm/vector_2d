#pragma once

#include <vector>
#include <utility>
#include <unordered_map>


template <typename Type>
class Vector2D {
public:
    Vector2D() = default;
    explicit Vector2D(size_t m, size_t n) : cols_(m), rows_(n) {

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
            return vec_[index_] = other;
        }
    private:
        std::vector<Type> vec_;
        size_t index_;
    };

    Proxy operator[](size_t index) {
        return Proxy(vector2d_[index], index);
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

    Vector2D & operator|(const Vector2D & rhs) {
        for (size_t i = 0; i < cols_ || i < rhs.cols_; ++i) {
            vector2d_[i].insert(vector2d_[i].end(),
                             std::make_move_iterator(rhs.vector2d_[i].begin()),
                             std::make_move_iterator(rhs.vector2d_[i].end()));
        }
        cols_ += rhs.cols_;
        return *this;
    }

    std::vector<Type> GetColumn(size_t index) const {
        return vector2d_.at(index);
    }

    std::vector<Type> GetRow(size_t index) {
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

private:

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

    std::vector<std::vector<Type>> vector2d_;
    size_t cols_ = 0;
    size_t rows_ = 0;
};

struct index {
public:
    index(size_t x, size_t y) : x_(x), y_(y) {}
    size_t x_;
    size_t y_;
    bool operator==(const index & rhs) const {
        return x_ == rhs.x_ && y_ == rhs.y_;
    }
};

class Hasher {
public:
    size_t operator()(const index ind) const {
        size_t h1 = std::hash<size_t>()(ind.x_);
        return std::hash<size_t>()(ind.y_) ^ (h1 << 1);
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

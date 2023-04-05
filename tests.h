#pragma once

#include <iostream>
#include <sstream>
#include "vector_2d.h"


using namespace std;

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file,
                     const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cout << boolalpha;
        cout << file << "("s << line << "): "s << func << ": "s;
        cout << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cout << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        cout << endl;
        abort();
    }
}

template <typename Type>
void RunTestImpl(const Type& func, const string& str) {
    func();
    cerr << str << " OK" << endl;
}

template <typename Type>
ostream & print_arr(ostream & out, Vector2D<Type> & arr_) {
    for (const auto & x : arr_) {
        for (const auto & y : x) {
            out << y << " ";
        }
        out << std::endl;
    }
    return out;
}


#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)
#define RUN_TEST(expr)  RunTestImpl((expr), #expr)

void TestConstructors() {
    Vector2D<int> arr_(3, 3, 0);
    ASSERT_EQUAL(arr_.GetCols_size(), 3);
    ASSERT_EQUAL(arr_.GetRows_size(), 3);

    Vector2D<int> arr2(arr_);
    ASSERT_EQUAL(arr2.GetRows_size(), 3);
    ASSERT_EQUAL(arr2.GetCols_size(), 3);

    Vector2D<int> arr3 = arr2;
    ASSERT_EQUAL(arr3.GetRows_size(), 3);
    ASSERT_EQUAL(arr3.GetCols_size(), 3);
}

void TestConcacinate() {
    Vector2D<int> arr_(3, 3, 0);
    Vector2D<int> arr_2(3, 3, 0);
    arr_ = arr_|arr_2;
    ASSERT_EQUAL(arr_.GetRows_size(), 3);
    ASSERT_EQUAL(arr_.GetCols_size(), 6);
}

void TestGetIndex() {
    Vector2D<int> arr_(3, 3, 1);
    ASSERT_EQUAL(arr_(1, 1), 1);
    arr_(1, 1) = 4;
    ASSERT_EQUAL(arr_(1, 1), 4);
}

void TestPlusOperator() {
    Vector2D<int> arr_(3, 3, 1);
    Vector2D<int> arr_2(3, 3, 2);

    arr_2 += arr_;
    ASSERT_EQUAL(arr_2(1, 1), 3);
    Vector2D<int> arr_3;
    arr_3 = arr_2 + arr_;
    ASSERT_EQUAL(arr_3(1, 1), 4);
}

void TestRange() {
    Vector2D<int> arr_(3, 3, 0);
    std::stringstream str;
    for (auto & x : arr_) {
        for (auto & y : x) {
            y = 1;
        }
    }
    print_arr(str, arr_);
    ASSERT_EQUAL(str.str(), "1 1 1 \n"
                            "1 1 1 \n"
                            "1 1 1 \n");

}








#include <iostream>
#include <algorithm>

#include "vector_2d.h"
#include "array2d_umap.h"

void TestArrayUmap() {
    Array2D_umap<int> arru_(3, 3, 1);
    Array2D_umap<int> arru_2(arru_);
    Array2D_umap<int> arru_3 = arru_2;
}

template <typename Type>
void print_arr(Vector2D<Type> & arr_) {
    for (const auto & x : arr_) {
        for (const auto & y : x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
}

void Test2Dvector() {
    std::cout << "Constarutors" << std::endl;

    Vector2D<int> arr_(3, 3, 0);
    std::cout << arr_.GetRows_size() << " " << arr_.GetCols_size() << std::endl;

    Vector2D<int> arr2(arr_);
    std::cout << arr2.GetRows_size() << " " << arr2.GetCols_size() << std::endl;

    Vector2D<int> arr3 = arr2;
    std::cout << arr3.GetRows_size() << " " << arr3.GetCols_size() << std::endl;
    std::cout << std::endl;


    std::cout << "concatenate" << std::endl;
    arr3 | arr2;
    std::cout << arr3.GetRows_size() << " " << arr3.GetCols_size() << std::endl;
    print_arr(arr3);
    std::cout << std::endl;

    std::cout << "Index impl" << std::endl;
    std::cout << arr3[2][2] << " " << arr_[2][2] << std::endl;
    std::cout << arr3(2, 2) << " " << arr_(2, 2) << std::endl;
    arr3[2][2] = 5;
    arr_(2, 2) = 7;
    std::cout << arr3[2][2] << " " << arr_[2][2] << std::endl;
//    std::cout << arr3.GetColumn(2).size() << " " << arr3.GetRow(2).size() << std::endl;
    std::cout << std::endl;

    print_arr(arr_);

    for (auto & x : arr_) {
        for (auto & y : x) {
            y = 1;
        }
    }
    print_arr(arr_);

}

int main() {
    Test2Dvector();
    return 0;
}

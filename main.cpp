#include <iostream>
#include "vector_2d.h"
#include "array2d_umap.h"

void TestArrayUmap() {
    Array2D_umap<int> arru_(3, 3, 1);
    Array2D_umap<int> arru_2(arru_);
    Array2D_umap<int> arru_3 = arru_2;
}

void Test2Dvector() {
    Vector2D<int> arr_(3, 3, 0);
    std::cout << arr_.GetRows_size() << " " << arr_.GetCols_size() << std::endl;

    Vector2D<int> arr2(arr_);
    std::cout << arr2.GetRows_size() << " " << arr2.GetCols_size() << std::endl;

    Vector2D<int> arr3 = arr2;
    std::cout << arr3.GetRows_size() << " " << arr3.GetCols_size() << std::endl;

    arr3 | arr2;
    std::cout << arr3.GetRows_size() << " " << arr3.GetCols_size() << std::endl;

    std::cout << arr3[2][2] << " " << arr_[2][2] << std::endl;
    std::cout << arr3(2, 2) << " " << arr_(2, 2) << std::endl;

    arr3(2, 2) = 5;
    arr_(2, 2) = 7;
    std::cout << arr3[2][2] << " " << arr_[2][2] << std::endl;
    std::cout << arr3.GetColumn(2).size() << " " << arr3.GetRow(2).size() << std::endl;

    for (const auto & x : arr_) {
        for (const auto & y : x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }

}

int main() {
    Test2Dvector();
    return 0;
}

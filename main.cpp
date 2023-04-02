#include <iostream>
#include "vector_2d.h"



int Test2Dvector() {
    Vector2D<int> arr_(10, 10, 0);
    std::cout << arr_.GetRows_size() << " " << arr_.GetCols_size() << std::endl;

    Vector2D<int> arr2(arr_);
    std::cout << arr2.GetRows_size() << " " << arr2.GetCols_size() << std::endl;

    Vector2D<int> arr3 = arr2;
    std::cout << arr3.GetRows_size() << " " << arr3.GetCols_size() << std::endl;

    std::cout << arr3[5][5] << " " << arr_[5][5] << std::endl;
    std::cout << arr3.GetColumn(7).size() << " " << arr3.GetRow(3).size() << std::endl;
    return 0;
}

int main() {
    Test2Dvector();
    return 0;
}

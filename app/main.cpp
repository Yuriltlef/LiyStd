#include <iostream>
#include "LinearList.hpp"

int main() {
    std::cout << VERSION_Y;
    int* ptr = new int;
    free(ptr);
    ptr = nullptr;
}
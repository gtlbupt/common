#include "scope_guard.hpp"
#include <iostream>

int main() {
    ON_SCOPE_EXIT([](){
        std::cout << "Hello";
    });
    return 0;
}


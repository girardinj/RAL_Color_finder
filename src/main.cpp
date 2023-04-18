#include <iostream>
#include "RAL.h"

int main(int argc, char* argv[]) {
    
    std::cout << "name: " << RAL::getName(192, 183, 124) << std::endl;
    std::cout << "ral: " << RAL::getName(1005) << std::endl;

    return 0;
}

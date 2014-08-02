/*
A few Known Answer Tests for the Symmetric Algorithms
*/

#include <iostream>
#include "../Encryptions/Encryptions.h"

int main(){
    std::cout << "\n\n"
              << (validate_all_symalg(std::cout)?std::string("Passed"):std::string("Failed"))
              << std::endl;
    return 0;
}
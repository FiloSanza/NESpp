#include <iostream>
#include "nestest.h"

int main() {
    std::cout << "NESTEST RUN" << std::endl;
    auto nestest_exit_code = nespp::nestest::run_nestest();
    std::cout << "Exit code: " << nestest_exit_code << std::endl;
}
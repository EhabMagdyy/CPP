#include "IOStream.hpp"

void IOStream::writeDigit(int digit) {
    if(digit < 0 || digit > 9) {
        throw std::out_of_range("Digit must be between 0 and 9");
    }
    std::cout << "Writing digit: " << digit << std::endl;
}
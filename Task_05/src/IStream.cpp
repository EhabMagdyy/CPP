#include "IStream.hpp"

int IStream::readDigit(){
    std::string input;
    std::cout << "Please enter a digit (0-9): ";
    std::cin >> input;

    if(input.length() == 1 && std::isdigit(input[0])){
        return input[0] - '0';
    }
    else if(input[0] == 'e'){
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }
    else{
        throw std::invalid_argument("Invalid input. Please enter a single digit between 0 and 9.");
    }
}
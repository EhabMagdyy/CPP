#include <iostream>
#include <memory>
#include "IOStream.hpp"
#include "SevenSegment.hpp"
#include "OStream.hpp"

int main(){
    std::unique_ptr<Stream> ref;

    int choice;
    std::cout << "Select output:\n1) Terminal\n2) Seven Segment\n> ";
    std::cin >> choice;

    if(choice == 1){
        ref = std::make_unique<IOStream>();
    }
    else{
        ref = std::make_unique<SevenSegment>(17,27,22,10,9,11,0);
    }

    int digit = 0;

    while(true){
        try{
            digit = ref->readDigit();
        }
        catch(const std::invalid_argument& e){
            std::cerr << "Caught an error: " << e.what() << std::endl;
            continue;
        }
        catch(const std::exception& e){
            std::cerr << "An error occurred: " << e.what() << std::endl;
            continue;
        }

        try{
            ref->writeDigit(digit);
        }
        catch(const std::out_of_range& e){
            std::cerr << "Caught an error: " << e.what() << std::endl;
        }
        catch(const std::exception& e){
            std::cerr << "An error occurred: " << e.what() << std::endl;
        }
    }
}

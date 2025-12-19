#include <iostream>
#include "IOStream.hpp"
#include "SevenSegment.hpp"

int main(){
    SevenSegment* sevSegment = new SevenSegment(17,27,22,10,9,11,0);
    int digit = 0;
    while(true){
        try{
            digit = sevSegment->readDigit();
        }
        catch(const std::invalid_argument& e){
            std::cerr << "Caught an error: " << e.what() << std::endl;
            continue; 
        }

        try{
            sevSegment->writeDigit(digit); 
        } 
        catch(const std::out_of_range& e){
            std::cerr << "Caught an error: " << e.what() << std::endl;
        } 
    }

    delete sevSegment;
    return 0;
}
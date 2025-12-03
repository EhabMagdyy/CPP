#include "GPIO/gpio.hpp"
#include <unistd.h>

int main(int argc, char* argv[]){
    int pinNumber = 22;
    if(argc > 1){
        pinNumber = std::stoi(argv[1]);
    }
    GPIO pin(pinNumber, "out");

    while (true){
        pin << 1;
        sleep(1);

        pin << 0;
        sleep(1);
    }

    return 0;
}

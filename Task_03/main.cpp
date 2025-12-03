#include "GPIO/gpio.hpp"
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <cstdio>

GPIO* ledPin = nullptr;

// Signal handler
void signalHandler(int signum) {
    if (ledPin) {
        printf("\nCtrl+C pressed. Cleaning up GPIO...\n");
        *ledPin << 0;
    }
    exit(0);
}

int main(int argc, char* argv[]){
    signal(SIGINT, signalHandler);  // Register SIGINT handler

    int pinNumber = 22;
    std::string mode = "out";
    int val;
    
    if(argc == 2){
        pinNumber = std::stoi(argv[1]);
    }
    else if(argc == 3){
        mode = argv[2];
    }

    GPIO pin(pinNumber, mode);
    ledPin = &pin;                  // Set global pointer for signal handler

    while (true){
        pin << 1;

        pin >> val;   // read current value
        std::cout << "GPIO value: " << val << std::endl;
        usleep(500000);

        pin << 0;
        pin >> val;   // read current value
        std::cout << "GPIO value: " << val << std::endl;
        usleep(500000);
    }

    return 0;
}

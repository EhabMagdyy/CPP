#include "GPIO/gpio.hpp"
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
    _exit(0);
}

int main(int argc, char* argv[]){
    signal(SIGINT, signalHandler);  // Register SIGINT handler

    int pinNumber = 22;
    if(argc > 1){
        pinNumber = std::stoi(argv[1]);
    }
    GPIO pin(pinNumber, "out");
    ledPin = &pin;                  // Set global pointer for signal handler

    while (true){
        pin << 1;
        usleep(500000);

        pin << 0;
        usleep(500000);
    }

    return 0;
}

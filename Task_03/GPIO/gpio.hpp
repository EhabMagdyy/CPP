#pragma once
#include <string>

class GPIO {
public:
    GPIO(int gpioNumber, const std::string& direction);
    ~GPIO();

    // operator<< to write 0 or 1
    GPIO& operator<<(int value);

private:
    int gpio;
    int fdValue;

    void exportGPIO();
    void unexportGPIO();
    void setDirection(const std::string& direction);
    void openValueFD();
};

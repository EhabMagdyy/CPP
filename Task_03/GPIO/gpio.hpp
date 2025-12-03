#pragma once            // like #ifndef GPIO_GPIO_HPP
#include <string>

class GPIO {
public:
    GPIO(int gpioNumber, const std::string& direction);
    ~GPIO();

    GPIO& operator<<(int value);

private:
    int gpio;
    int fdValue;

    void exportGPIO();
    void unexportGPIO();
    void setDirection(const std::string& direction);
    void openValueFD();
};

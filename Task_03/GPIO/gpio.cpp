#include "gpio.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>

GPIO::GPIO(int gpioNumber, const std::string& direction)
    : gpio(gpioNumber + 512), fdValue(-1){
    exportGPIO();
    setDirection(direction);
    openValueFD();
}

GPIO::~GPIO(){
    if (fdValue != -1)
        close(fdValue);
    unexportGPIO();
}

GPIO& GPIO::operator<<(int value){
    if(fdValue == -1)
        throw std::runtime_error("Value file not opened");

    const char* v = (value == 0 ? "0" : "1");
    if(write(fdValue, v, 1) < 0)
        throw std::runtime_error("Failed to write GPIO value");

    // Reset pointer for sysfs
    lseek(fdValue, 0, SEEK_SET);

    return *this;
}

void GPIO::exportGPIO() {
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0)
        throw std::runtime_error("Cannot open export");

    std::string num = std::to_string(gpio);
    write(fd, num.c_str(), num.size());
    close(fd);
    usleep(200000);
}

void GPIO::unexportGPIO() {
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) return;

    std::string num = std::to_string(gpio);
    write(fd, num.c_str(), num.size());
    close(fd);
}

void GPIO::setDirection(const std::string& direction) {
    std::string path = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/direction";
    int fd = open(path.c_str(), O_WRONLY);
    if (fd < 0)
        throw std::runtime_error("Cannot open direction");

    write(fd, direction.c_str(), direction.size());
    close(fd);
}

void GPIO::openValueFD() {
    std::string path = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/value";
    fdValue = open(path.c_str(), O_WRONLY);
    if (fdValue < 0)
        throw std::runtime_error("Cannot open value fd");
}

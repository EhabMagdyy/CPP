#include "gpio.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

GPIO::GPIO(int gpioNumber, const std::string& direction) : gpio(gpioNumber + 512), fdValue(-1){
    exportGPIO();
    setDirection(direction);
    openValueFD();
}

GPIO::~GPIO(){
    if(fdValue != -1)
        close(fdValue);
    unexportGPIO();
}

GPIO& GPIO::operator<<(int value){
    if(fdValue == -1){
        perror("GPIO value file not opened for writing");
        return *this;
    }

    const char* v =(value == 0 ? "0" : "1");
    if(write(fdValue, v, 1) < 0)
        perror("Failed to write GPIO value");

    lseek(fdValue, 0, SEEK_SET);
    return *this;
}

GPIO& GPIO::operator>>(int &value){
    // Reopen for reading
    int fd = open(("/sys/class/gpio/gpio" + std::to_string(gpio) + "/value").c_str(), O_RDONLY);
    if(fd < 0){
        perror("Cannot open GPIO value file for reading");
        value = -1;
        return *this;
    }

    char buf;
    if(read(fd, &buf, 1) < 0){
        perror("Failed to read GPIO value");
        value = -1;
    } else {
        value =(buf == '0' ? 0 : 1);
    }

    close(fd);
    return *this;
}

void GPIO::exportGPIO(){
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd < 0){
        perror("Cannot open /sys/class/gpio/export");
        return;
    }

    std::string num = std::to_string(gpio);
    if(write(fd, num.c_str(), num.size()) < 0)
        perror("Failed to write to /sys/class/gpio/export");

    close(fd);
    usleep(200000);
}

void GPIO::unexportGPIO(){
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd < 0)
        return;

    std::string num = std::to_string(gpio);
    if(write(fd, num.c_str(), num.size()) < 0)
        perror("Failed to write to /sys/class/gpio/unexport");

    close(fd);
}

void GPIO::setDirection(const std::string& direction){
    std::string path = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/direction";
    int fd = open(path.c_str(), O_WRONLY);
    if(fd < 0){
        perror(("Cannot open " + path).c_str());
        return;
    }

    if(write(fd, direction.c_str(), direction.size()) < 0)
        perror(("Failed to set direction " + direction).c_str());

    close(fd);
}

void GPIO::openValueFD(){
    std::string path = "/sys/class/gpio/gpio" + std::to_string(gpio) + "/value";
    fdValue = open(path.c_str(), O_WRONLY);
    if(fdValue < 0)
        perror(("Cannot open " + path).c_str());
}

#pragma once
#include <iostream>

class Stream{
public:
    virtual ~Stream() = default;
    virtual void writeDigit(int digit) = 0;
    virtual int readDigit() = 0;
};
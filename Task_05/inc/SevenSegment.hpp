#pragma once            // like #ifndef SEVENSEGMENT_HPP
#include "gpio.hpp"
#include "IStream.hpp"
#include "OStream.hpp"

class SevenSegment : public IStream, public OStream {
public:
    SevenSegment(int a, int b, int c, int d, int e, int f, int g);
    ~SevenSegment();
    void writeDigit(int digit);
private:
    GPIO segA;
    GPIO segB;
    GPIO segC;
    GPIO segD;
    GPIO segE;
    GPIO segF;
    GPIO segG;
};
#pragma once
#include "Stream.hpp"

class OStream : virtual public Stream{
public:
    virtual ~OStream() = default;
    virtual void writeDigit(int digit) = 0;
};
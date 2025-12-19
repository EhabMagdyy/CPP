#pragma once
#include "Stream.hpp"

class IStream : virtual public Stream{
public:
    virtual ~IStream() = default;
    int readDigit();
};
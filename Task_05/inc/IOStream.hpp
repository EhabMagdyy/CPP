#pragma once
#include "IStream.hpp"
#include "OStream.hpp"

class IOStream : public IStream, public OStream{
public:
    virtual ~IOStream() = default;
    void writeDigit(int digit) override;
};
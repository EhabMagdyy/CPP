#include "SevenSegment.hpp"

SevenSegment::SevenSegment(int a, int b, int c, int d, int e, int f, int g)
    : segA(a, "out"), segB(b, "out"), segC(c, "out"), segD(d, "out"),
      segE(e, "out"), segF(f, "out"), segG(g, "out"){}

SevenSegment::~SevenSegment(){}

void SevenSegment::writeDigit(int digit){
    // Segment mapping for digits 0-9
    static const int segmentMap[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    if(digit < 0 || digit > 9)
        return; // Invalid digit

    segA << segmentMap[digit][0];
    segB << segmentMap[digit][1];
    segC << segmentMap[digit][2];
    segD << segmentMap[digit][3];
    segE << segmentMap[digit][4];
    segF << segmentMap[digit][5];
    segG << segmentMap[digit][6];
}
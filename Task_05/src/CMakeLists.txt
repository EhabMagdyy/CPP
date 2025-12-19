add_library(StreamLib SHARED 
    IStream.cpp
    OStream.cpp
    SevenSegment.cpp
    Stream.cpp
    IOStream.cpp
    gpio.cpp
)
target_include_directories(StreamLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
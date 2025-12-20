# Creatijng a shared library named StreamLib containing the source files
add_library(StreamLib SHARED 
    IStream.cpp
    OStream.cpp
    SevenSegment.cpp
    Stream.cpp
    IOStream.cpp
    gpio.cpp
)
# Including the header files for the StreamLib library
# PUBLIC -> makes the include directories available to targets that link to this library
target_include_directories(StreamLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)
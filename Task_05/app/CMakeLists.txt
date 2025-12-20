# Adding an executable target named Task05 using main.cpp
add_executable(Task05 main.cpp)
# Linking the StreamLib library target to the Task05 executable target
# PRIVATE -> the linkage is only for this target
target_link_libraries(Task05 PRIVATE StreamLib)

# Adding a post-build command to copy the built executable and shared library to my RPi
add_custom_command(
    TARGET Task05
    POST_BUILD  # Runs after building the Task05 target
    COMMAND scp /home/ehab/Documents/ITI_9Months/CPP/Task_05/build/app/Task05 pi@192.168.50.2:/home/pi/Documents/ITI_9Months/CPP/02_SevenSegment
    COMMAND scp /home/ehab/Documents/ITI_9Months/CPP/Task_05/build/src/libStreamLib.so pi@192.168.50.2:/home/pi/Documents/ITI_9Months/CPP/02_SevenSegment
)
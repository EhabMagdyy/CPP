# Adding an executable target named Task05 using main.cpp
add_executable(Task05 main.cpp)
# Linking the StreamLib library target to the Task05 executable target
# PRIVATE -> the linkage is only for this target
target_link_libraries(Task05 PRIVATE StreamLib)
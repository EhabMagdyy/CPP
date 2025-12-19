# Target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Toolchain path
set(TOOLCHAIN_PREFIX aarch64-rpi3-linux-gnu)
set(TOOLCHAIN_PATH $ENV{HOME}/x-tools/aarch64-rpi3-linux-gnu/bin)

# Compilers
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-g++)

# Sysroot (IMPORTANT)
set(CMAKE_SYSROOT $ENV{HOME}/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot)

# Where CMake looks for headers & libs
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# Never look on host system
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

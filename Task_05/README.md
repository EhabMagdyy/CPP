### CPP Task 5 - RPi 7 Segment  Multiple Inheritance

---

#### Demo



---

#### On Host

##### Generate Build & Libs

```bash
cmake -S . -B build-rpi   -DCMAKE_TOOLCHAIN_FILE=toolchains/rpi3-aarch64.cmake   -DCMAKE_BUILD_TYPE=Release
```

##### Cross build the project

```bash
cmake --build build-rpi -j$(nproc)
```

##### Check the output file type

```bash
ehab@HP:~/Documents/ITI_9Months/CPP/Task_05$ file build-rpi/app/Task05
build-rpi/app/Task05: ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, for GNU/Linux 6.4.0, with debug_info, not stripped
```

##### Send Executable & Library to RPi

```bash
ehab@HP:~/Documents/ITI_9Months/CPP/Task_05$ scp build-rpi/app/Task05 pi@192.168.50.2:/home/pi/Documents/ITI_9Months/CPP/02_SevenSegment
pi@192.168.50.2's password: 
Task05                                              100%   77KB  10.9MB/s   00:00    
ehab@HP:~/Documents/ITI_9Months/CPP/Task_05$ scp build-rpi/src/libStreamLib.so pi@192.168.50.2:/home/pi/Documents/ITI_9Months/CPP/02_SevenSegment
pi@192.168.50.2's password: 
libStreamLib.so   								    100%   76KB   8.4MB/s   00:00
```

---

#### On RPi

```bash
export LD_LIBRARY_PATH=.
```

##### Run your Project

```bash
pi@ehabpi:~/Documents/ITI_9Months/CPP/02_SevenSegment $ ./Task05 
Please enter a digit (0-9): 1
Please enter a digit (0-9): 0
Please enter a digit (0-9): 6
Please enter a digit (0-9): 7
Please enter a digit (0-9): 4
Please enter a digit (0-9): 1
Please enter a digit (0-9): 079
Caught an error: Invalid input. Please enter a single digit between 0 and 9.
Please enter a digit (0-9): 6
Please enter a digit (0-9): 8
Please enter a digit (0-9): fdfg
Caught an error: Invalid input. Please enter a single digit between 0 and 9.
Please enter a digit (0-9): 5
Please enter a digit (0-9): 1
Please enter a digit (0-9): 0
Please enter a digit (0-9): 8
Please enter a digit (0-9): e
Exiting...
```
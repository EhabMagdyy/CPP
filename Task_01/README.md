## `gcc` == `g++` <if we want>

1. ##### Compiling `main.c` & `gpio.c` using `gcc `  -> Works Fine!

   ```
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ gcc main.c MCAL/gpio.c
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ ./a.out 
   GPIO Initialized
   GPIO Write Operation
   ```

2. ##### Compiling `main.c` & `gpio.c` using `g++ `  -> Works Fine!

   ```bash
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ g++ main.c MCAL/gpio.c
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ ./a.out 
   GPIO Initialized
   GPIO Write Operation
   ```

3. #####  Compiling `main.c`  using `gcc` & `gpio.c` using `g++ `  -> Problem (undefined reference) <**Mangling**>

   ```bash
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ g++ MCAL/gpio.c -c -o gpio.o
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ gcc main.c gpio.o 
   /usr/bin/ld: /tmp/ccCEsE9R.o: in function `main':
   main.c:(.text+0xe): undefined reference to `GPIO_Init'
   /usr/bin/ld: main.c:(.text+0x18): undefined reference to `GPIO_Write'
   collect2: error: ld returned 1 exit status
   ```

4. ##### Redo step `3` but using `extern "C"`, so that no C++ name mangling occurs 

   ```bash
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ g++ MCAL/gpio.c -c -o gpio.o
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ gcc main.c gpio.o 
   ehab@HP:~/Documents/ITI_9Months/CPP/Task_01$ ./a.out 
   GPIO Initialized
   GPIO Write Operation
   ```



#### Summary

| Condition                                       | extern "C" Used?                                             | Explanation                                                  |
| ----------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Compile all files with gcc** (C compiler)     | Not needed                                                   | Everything is compiled as C, so no C++ name mangling occurs. All function names remain plain (e.g., `LED_Init`). |
| **Compile all files with g++** (C++ compiler)   | Not needed                                                   | All files are treated as C++. so name mangling won't be a problem. |
| **Compile main.c with gcc and gpio.c with g++** | Required in headers and C++ source files for exported functions | The C++-compiled file (`gpio.c/.cpp`) will mangle names unless you wrap function definitions and declarations with `extern "C"`. This ensures C-compatible names so `main.c` can link correctly. |
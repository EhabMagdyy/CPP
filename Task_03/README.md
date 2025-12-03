### Control Raspberry Pi LED using C++ file descriptors (Cross Compile)

###### On Host

##### Create Dynamic Library

```bash
~/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-g++ -fPIC -shared GPIO/gpio.cpp -o libgpio
.so
```

##### Compile main and link with the shared library

```bash
~/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-g++ main.cpp -L. -lgpio -o app.o
```

##### Send Output file and Dynamic library to your RPi

```bash
scp app.o libgpio.so pi@192.168.1.6:/home/pi/Documents/ITI_9Months/CPP/00_GPIO_ControlLED/
```

```bash
pi@192.168.1.6's password: 
app.o                                                                      100%   80KB  23.6KB/s   00:03    
libgpio.so                                                                 100%   73KB  58.3KB/s   00:01  
```

---

###### On RPi

##### Go to your folder which contains received files

```bash
cd Documents/ITI_9Months/CPP/00_GPIO_ControlLED/
```

```bash
pi@ehabpi:~/Documents/ITI_9Months/CPP/00_GPIO_ControlLED $ ls
app.o  libgpio.so
```

##### Make your library visible

```bash
export LD_LIBRARY_PATH=.
```

##### Run the app (you can give it the gpio you want to toggle "by default <22>")

```bash
./app.o 27
```


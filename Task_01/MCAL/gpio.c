#include "gpio.h"
#include <stdio.h>

#ifdef __cplusplus
namespace GPIO {
#endif

void GPIO_Init(){
    printf("GPIO Initialized\n");
}
void GPIO_Write(){
    printf("GPIO Write Operation\n");
}

#ifdef __cplusplus
} // namespace GPIO
#endif
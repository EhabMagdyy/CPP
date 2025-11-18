#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
namespace GPIO {
#endif

void GPIO_Init();
void GPIO_Write();

#ifdef __cplusplus
} // extern "C"
} // namespace GPIO
#endif

#endif // GPIO_H
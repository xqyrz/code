#ifndef LINUX_GPIO_H
#define LINUX_GPIO_H
#include "chardevice.h"
#include <linux/gpio.h>
enum GPIO_STATUS{
    GPIO_RESET =0U,
    GPIO_SET 
};
typedef enum{
    gpio_out = 0,
    gpio_input
}GPIO_MODEL;
int GPIO_Init(charDeviceStructPtr,GPIO_MODEL);
int GPIO_outSet(int index,enum GPIO_STATUS);
#endif // !LINUX_GPIO_H

#ifndef MAIN_H
#define MAIN_H
#include <linux/module.h>
#include <linux/printk.h>
#include "chardevice.h"
#include "linux_gpio.h"
typedef enum{
    no_key = 0,
    key0
}KEY_VALUE;
typedef struct main
{
    charDeviceStruct dev;
    atomic_t value;
    /* data */
}KEY_STRCUCT,*PKEY_STRCUCT;

extern PKEY_STRCUCT keygpio;

#endif
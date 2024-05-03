#include "linux_gpio.h"
#include <linux/of_gpio.h>
/**
 * @ingroup gpio输出
 * @index： charDeviceStruct.gpio_index
*/
int GPIO_outSet(int index,enum GPIO_STATUS status)
{
    int err = gpio_direction_output(index,status);
    if(err) printk("set gpio faild = %d\n",err);
    return err;
}
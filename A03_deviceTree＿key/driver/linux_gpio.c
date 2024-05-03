#include "linux_gpio.h"
#include <linux/of_gpio.h>
/**
 * @brief 
 * 
 * @return int 
 */
int GPIO_Init(charDeviceStructPtr dev,GPIO_MODEL model){
    int ret = 0;
    ret = gpio_request(dev->treeInfo.gpio_index, dev->treeInfo.gpio_name);
    if(ret) goto fail_request;
    switch (model)
    {
    case gpio_out:
        /* code */
        break;
    case gpio_input:
        gpio_direction_input(dev->treeInfo.gpio_index);
        break;
    default:
        break;
    }
    
fail_request:
    printk(KERN_ERR "%s:%s Failed to request GPIO %d: %d\n",dev->name,dev->treeInfo.gpio_name, dev->treeInfo.gpio_index, ret);
    return ret;
}
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
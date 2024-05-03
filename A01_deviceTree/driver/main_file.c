#include "main_file.h"
#include <asm/uaccess.h>
#include "linux_gpio.h"
#include "main.h"
int dev_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    charDeviceStructPtr device;
    filp->private_data = ledgpio;
    device =(charDeviceStructPtr) filp->private_data;
    ret = GPIO_Init(device,gpio_out);
    if(ret) return ret;
    printk("dev open %s \n",device->name);
    /** */
    return 0;
}
int dev_release(struct inode *inode, struct file *filp)
{
        charDeviceStructPtr device;
    filp->private_data = ledgpio;
    device =(charDeviceStructPtr) filp->private_data;
    
    if(gpio_is_valid(device->treeInfo.gpio_index))
    {
        gpio_free(device->treeInfo.gpio_index);
        printk("release %s\n",device->treeInfo.gpio_name);
    }
    
    return 0;
}
ssize_t dev_read(struct file *filp, char __user *buf,size_t cnt, loff_t *offt)
{
    return -1;
}
ssize_t dev_write(struct file *filp, const char __user *buf,size_t cnt, loff_t *offt)
{
    int retvalue;
    char databuf[1];
    char status;
    charDeviceStructPtr dev =(charDeviceStructPtr ) filp->private_data;
    retvalue = copy_from_user(databuf, buf, cnt);
    if(retvalue < 0) {
        printk("copy_from_user;kernel write faikey!\r\n");
    return -EFAULT;
    }
    status = databuf[0];
    if(status == GPIO_SET) GPIO_outSet(dev->treeInfo.gpio_index,GPIO_SET); 
    else if(status == GPIO_RESET) GPIO_outSet(dev->treeInfo.gpio_index,GPIO_RESET); 
    else {
        printk("parameter is error = %d\r\n",status);
        return -EFAULT;
    }
    return 0;
    
}

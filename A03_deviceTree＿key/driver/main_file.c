#include "main_file.h"
#include <asm/uaccess.h>

#include "linux_gpio.h"

#include "main.h"
int dev_open(struct inode *inode, struct file *filp)
{
    int ret = 0;
    PKEY_STRCUCT device;
    filp->private_data = keygpio;
    device =(PKEY_STRCUCT) filp->private_data;
    ret = GPIO_Init(&device->dev,gpio_input);
    if(ret) return ret;
    printk("dev open %s \n",device->dev.name);
    /** */
    return 0;
}
int dev_release(struct inode *inode, struct file *filp)
{
        PKEY_STRCUCT device;
    filp->private_data = keygpio;
    device =(PKEY_STRCUCT) filp->private_data;
    
    if(gpio_is_valid(device->dev.treeInfo.gpio_index))
    {
        gpio_free(device->dev.treeInfo.gpio_index);
        printk("release %s\n",device->dev.treeInfo.gpio_name);
    }
    
    return 0;
}
ssize_t dev_read(struct file *filp, char __user *buf,size_t cnt, loff_t *offt)
{
      PKEY_STRCUCT dev =(PKEY_STRCUCT )filp->private_data;
      int value;
      printk("read key %d %d\n",dev->dev.treeInfo.gpio_index,gpio_get_value(dev->dev.treeInfo.gpio_index));
      if(!gpio_get_value(dev->dev.treeInfo.gpio_index)){
        while(!gpio_get_value(dev->dev.treeInfo.gpio_index)); /* 等待按键释放 */
        atomic_set(&(dev->value), key0);
        printk("read presss\n");
      }
      else{
        atomic_set(&(dev->value), no_key);
      }
    value = atomic_read(&dev->value);
   return copy_to_user(buf, &value, sizeof(value));
}
ssize_t dev_write(struct file *filp, const char __user *buf,size_t cnt, loff_t *offt)
{
    /*
    int retvalue;
    char databuf[1];
    char status;
    PKEY_STRCUCT *dev =(PKEY_STRCUCT *) filp->private_data;
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
    */
   printk("this dev is not write");
    return -2;
    
}
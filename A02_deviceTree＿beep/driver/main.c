#include "main.h"
#include "main_file.h"
charDeviceStructPtr beepgpio= &(charDeviceStruct){
    .name = "beepgpio",
    .count = 1,
    .treeInfo = {
        .path = "/gpiobeep",
        .gpio_name = "beep-gpios",
    }
};
struct file_operations gpiobeep_fops = {
    .owner = THIS_MODULE,
     .open = dev_open,
    //  .read = dev_read,
    .write = dev_write,
    // .release = dev_release,
};
int __init beep_init(void)
{

    printk("enter beep_init; name = %s\r\n",beepgpio->name);
    beepgpio->operations = &gpiobeep_fops;
    if(getPinCtrlInfo(beepgpio)<0) goto faild_initPinCtrl;
    GPIO_outSet(beepgpio->treeInfo.gpio_index,GPIO_SET);
    if(initCharDevice(beepgpio,THIS_MODULE)<0) goto faild_initCharDevice;
    printk("beep_init success\n");
    return 0; 
faild_initPinCtrl:
    printk("initPinCtrl faild = %s\n",beepgpio->treeInfo.gpio_name) ;
    return -EINVAL;
faild_initCharDevice:
    printk("initCharDevice faild = %s\n",beepgpio->name) ;
    return -EINVAL;
}

void __exit beep_exit(void)
{
        exitCharDevice(beepgpio);
    printk("exit beep\r\n");
}
module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL"); //本驱动程序遵循GPL开源协议，必写
MODULE_AUTHOR("xqyr");

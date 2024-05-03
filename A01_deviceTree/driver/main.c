#include "main.h"
#include "main_file.h"
charDeviceStructPtr ledgpio= &(charDeviceStruct){
    .name = "ledgpio",
    .count = 1,
    .treeInfo = {
        .path = "/gpioled",
        .gpio_name = "led-gpios",
    }
};
struct file_operations gpioled_fops = {
    .owner = THIS_MODULE,
     .open = dev_open,
    //  .read = dev_read,
    .write = dev_write,
    .release = dev_release,
    
};
int __init led_init(void)
{

    printk("enter led_init; name = %s\r\n",ledgpio->name);
    ledgpio->operations = &gpioled_fops;
    if(getPinCtrlInfo(ledgpio)<0) goto faild_initPinCtrl;
    GPIO_outSet(ledgpio->treeInfo.gpio_index,GPIO_SET);
    if(initCharDevice(ledgpio,THIS_MODULE)<0) goto faild_initCharDevice;
    printk("led_init success\n");
    return 0; 
faild_initPinCtrl:
    printk("initPinCtrl faild = %s\n",ledgpio->treeInfo.gpio_name) ;
    return -EINVAL;
faild_initCharDevice:
    printk("initCharDevice faild = %s\n",ledgpio->name) ;
    return -EINVAL;
}

void __exit led_exit(void)
{
	gpio_free(ledgpio->treeInfo.gpio_index);	
        exitCharDevice(ledgpio);
    printk("exit led\r\n");
}
module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL"); //本驱动程序遵循GPL开源协议，必写
MODULE_AUTHOR("xqyr");

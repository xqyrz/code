#include "main.h"
#include "main_file.h"
PKEY_STRCUCT keygpio= &(KEY_STRCUCT){
    .dev={
        .name = "keygpio",
        .count = 1,
        .treeInfo = {
        .path = "/gpiokey",
        .gpio_name = "key-gpios"  
        },
    }
};
struct file_operations gpiokey_fops = {
    .owner = THIS_MODULE,
     .open = dev_open,
     .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};
int __init key_init(void)
{

    printk("enter key_init; name = %s\r\n",keygpio->dev.name);
    (keygpio->dev).operations = &gpiokey_fops;
    if(getPinCtrlInfo(&keygpio->dev)<0) goto faild_initPinCtrl;
    GPIO_outSet(keygpio->dev.treeInfo.gpio_index,GPIO_SET);
    if(initCharDevice(&keygpio->dev,THIS_MODULE)<0) goto faild_initCharDevice;
    printk("key_init success\n");
    return 0; 
faild_initPinCtrl:
    printk("initPinCtrl faild = %s\n",keygpio->dev.treeInfo.gpio_name) ;
    return -EINVAL;
faild_initCharDevice:
    printk("initCharDevice faild = %s\n",keygpio->dev.name) ;
    return -EINVAL;
}

void __exit key_exit(void)
{
    gpio_free(keygpio->dev.treeInfo.gpio_index);
    exitCharDevice(&keygpio->dev);

    printk("exit key\r\n");
}
module_init(key_init);
module_exit(key_exit);
MODULE_LICENSE("GPL"); //本驱动程序遵循GPL开源协议，必写
MODULE_AUTHOR("xqyr");

#include "chardevice.h"
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/fs.h>
#include <linux/device.h>
/**
 * 1. 获取设备节点
*/
int getTreeNd(charDeviceStruct* device)
{
    device->treeInfo.nd = of_find_node_by_path(device->treeInfo.path);
    if(device->treeInfo.nd)
    {
        return 0;  
    }else
    {
        return -EINVAL;
    }

}
/**
 * 2、 获取设备树中的 gpio 属性,得到 LED 所使用的 LED 编号
*/
int getTreeGPIO(charDeviceStruct* device)
{
    device->treeInfo.gpio_index = of_get_named_gpio(device->treeInfo.nd,device->treeInfo.gpio_name,0);
    if(device->treeInfo.gpio_index <0)
    {
        printk("not find %s gpio_num is %d\n", device->treeInfo.gpio_name,device->treeInfo.gpio_index);
        return -EINVAL;
    }
    printk("%s getTreeGPIO succeces num = %d\n", device->treeInfo.gpio_name, device->treeInfo.gpio_index);
    return device->treeInfo.gpio_index;
}

int initCharDevice(charDeviceStruct* device,struct module* module)
{
    int err = 0;
    if(device->major) /*定义了设备号*/
    {
      
        device->devid = MKDEV(device->major, device->minjor);/* 大部分驱动次设备号都选择 0 */
        err = register_chrdev_region(device->devid, device->major, device->name);
    
    }
    else{
      
        err =   alloc_chrdev_region(&(device->devid), device->minjor, device->count, device->name);
        if(err) goto faild_get_major;
        device->major = MAJOR(device->devid);
        device->minjor = MINOR(device->devid);
    }
    device->manjor_flag = true;
    if(device->operations){
        device->cdev.owner = device->operations->owner;
        cdev_init(&(device->cdev),device->operations);
    } else goto operations_hasNot;
    err = cdev_add(&device->cdev, device->devid, device->count);
    if(err) goto fiald_cdev_add;

    device->cdev_del_flag = true;
    	/* 4、创建类 */
	device->class = class_create(THIS_MODULE, device->name);
	if (IS_ERR(device->class)) {
        //PTR_ERR函数用于从指针类型的错误码中提取错误码值。通常在内核中，当函数调用失败时，会返回一个错误码，这个错误码可能是一个指针类型。
        //PTR_ERR函数可以将这个指针类型的错误码转换为整数类型的错误码值。
		err =  PTR_ERR(device->class);
        goto class_create;
	}
    
    /*5.创建设备*/
    device->device= device_create(device->class, NULL, device->devid, NULL, device->name);
    device->device_create_flag = true;
     printk("charDeivce init success = %d;major = %d;minjor = %d\n",err,device->major,device->minjor);
    return err;
operations_hasNot:
    printk("err operations_hasNot is empty\n");
faild_get_major:
    printk("faild_get_major = %d\n",err);
    return err;   
fiald_cdev_add:
    printk("faild_cdev_add = %d\n",err);
    return err;   
class_create:
    printk("faild_class_create = %d\n",err);
    return err;   
}
/**
 * 
*/
int exitCharDevice(charDeviceStruct *device)
{
    if(device->device_create_flag)
    {
        device_destroy(device->class, device->devid);
        class_destroy(device->class);
        device->device_create_flag = false;
    }
    if(device->cdev_del_flag)
    {
        cdev_del(&device->cdev);
        device->cdev_del_flag = false;
    }
    if(device->manjor_flag)
    {
        unregister_chrdev_region(device->devid,device->count);
        device->manjor_flag = false;
    }    
    return 0;
}

/**
 * @brief 获取PinCtrl 所需要的信息
 */
int getPinCtrlInfo(charDeviceStruct* dev)
{
    if(getTreeNd(dev)) goto faild_get_treeNode; // 获取设备节点
    if(getTreeGPIO(dev) == -EINVAL) goto faild_get_gpioinfo; // 获取设备树中的 gpio 属性
    printk("%s pintctrl success\n",dev->treeInfo.gpio_name);
    return 0;
faild_get_treeNode:
    printk("get nd faild = %s\n",dev->treeInfo.path) ;
    return -EINVAL;
faild_get_gpioinfo:
    printk("get gpio info faild = %s\n",dev->treeInfo.gpio_name);
    return -EINVAL;
}
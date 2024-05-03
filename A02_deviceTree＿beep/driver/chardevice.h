#ifndef CHARDEVICE_H
#define CHARDEVICE_H
#include <linux/types.h>
#include <linux/cdev.h>
#include <stdbool.h>
typedef struct{
    const char *path;
 const char* gpio_name;
 int gpio_index;
 struct device_node *nd; /* 设备节点 */
}treeDevice;
typedef struct 
{
    const int count;
    const struct file_operations* operations;
    struct module* module;
    treeDevice treeInfo;
    const char* name;// 驱动名称
    int major;// 驱动主设备号
    int minjor;// 驱动次设备号
    dev_t devid;// 驱动设备号变量
    struct cdev cdev;// 字符设备
    struct class *class;// 驱动类
    struct device *device;// 驱动设备
    ///
    bool manjor_flag; //获得设备号标志位
    bool cdev_del_flag; //添加字符设备到系统标志位
    bool device_create_flag;//添加设备节点
    /* data */
}charDeviceStruct,*charDeviceStructPtr;// 
int getTreeNd(charDeviceStruct*);
int getTreeGPIO(charDeviceStruct*);
/**
 *  初始化字符设备
*/
int getPinCtrlInfo(charDeviceStruct*);
int initCharDevice(charDeviceStruct* device,struct module* module);
int exitCharDevice(charDeviceStruct* device);

//__weak void  dev_open(struct inode *inode, struct file *filp);
#endif // #define 


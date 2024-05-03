#ifndef MAIN_FILE_H
#define MAIN_FILE_H
#include <linux/fs.h>
int dev_open(struct inode *inode, struct file *filp);\
int dev_release(struct inode *inode, struct file *filp);
ssize_t dev_write(struct file *filp,const char __user *buf,size_t cnt, loff_t *offt);
ssize_t dev_read(struct file *filp, char __user *buf,size_t cnt, loff_t *offt);
#endif
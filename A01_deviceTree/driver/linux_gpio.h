#ifndef LINUX_GPIO_H
#define LINUX_GPIO_H
enum GPIO_STATUS{
    GPIO_RESET =0U,
    GPIO_SET 
};
int GPIO_outSet(int index,enum GPIO_STATUS);
#endif // !LINUX_GPIO_H

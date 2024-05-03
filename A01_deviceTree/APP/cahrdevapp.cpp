#include <utility>
#include <unistd.h>
#include "chardevapp.h"
#include <iostream>
charDeviceAPP::charDeviceAPP(string  filename):
        filename(std::move(filename)){

}

int charDeviceAPP::openDev(int model) {
   fd= open(filename.data(),model);
   if(fd<0){
       std::cout<<"openDev error = "<<fd<<std::endl;
       return -1;
   }
    oepned = true;
    return 0;
}

int charDeviceAPP::writeDev(const void *__buf, size_t __n) const {
    if(!oepned){
        std::cout<<"writeDev error = "<<fd<<std::endl;
        return -1;
    }
    write(fd,__buf,__n);
    return 0;
}

#ifndef CHAR_DEV_APP_H
#define CHAR_DEV_APP_H
#include <string>
#include <fcntl.h>
using std::string;
class charDeviceAPP{
 public:
    explicit charDeviceAPP(string  filename);
    ~charDeviceAPP();
   int openDev(int model = O_RDWR);
   int closeDev();
   int writeDev(const void *__buf, size_t __n) const;
   int readDev(void *__buf, size_t __n) const;
 private:
  const  string filename;
  int fd = -1;
  bool oepned = false;
};



#endif // CHAR_DEV_APP_H

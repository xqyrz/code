#ifndef CHAR_DEV_APP_H
#define CHAR_DEV_APP_H
#include <string>
#include <fcntl.h>
using std::string;
class charDeviceAPP{
 public:
    explicit charDeviceAPP(string  filename);
   int openDev(int model = O_RDWR);
   int writeDev(const void *__buf, size_t __n) const;
 private:
  const  string filename;
  int fd = -1;
  bool oepned = false;
};



#endif // CHAR_DEV_APP_H

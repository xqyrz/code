#include "beepapp.h"
#include <string>
enum GPIO_STATUS{
    GPIO_RESET =0U,
    GPIO_SET
};
int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("parameter error is %d,should be 2;you can try './beepAPP -help'\n",argc);
        return -1;
    }
    if(argv[1][0] == '-' && argv[1][1] == 'h'){
        printf("you can try './beepAPP ON' or './beepAPP OFF'\n");
        return 0;
    }else if(argv[1][0] == 'O'){
        std::string str = argv[1];
        beepAPP app("/dev/beepgpio");
        app.openDev();
        if(str == "ON") {
            auto s = GPIO_RESET;
            printf("beep ON\r\n");
            app.writeDev(&s,1);
        }
        else if(str == "OFF")
        {
            auto s = GPIO_SET;
            printf("beep OFF\r\n");
            app.writeDev(&s,1);
        }

    }else {
        printf("parameter error is %s,should be 2;you can try './beepAPP -help'\n",argv[1]);
        return -1;
    }
    return 0;
}

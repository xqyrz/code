#include "keyapp.h"
#include <string>
int main(int argc, char *argv[]) {
    printf("run\n");
    if(argc  !=2){
        printf("parameter error is %d,should be 2;you can try './keyAPP -help'\n",argc);
        return -1;
    }

    if(argv[1][0] == '-' && argv[1][1] == 'h'){
        printf("you can try './keyAPP /dev/keygpio'\n");
        return 0;
    }else if(argv[1][0] == '/'){
        std::string str = argv[1];
        keyAPP app(str);
        if(app.openDev() == -1) goto fail_open;
        app.readDev(&(app.value),sizeof(app.value));
        switch (app.value) {
            case keyAPP::key0:
                printf("key0 is Pressed\n");
                break;
            case keyAPP::no_key:
                printf("no_key is Pressed\n");
                break;
            default:
                printf("unknown is %d\n",app.value);
                break;
        }
        return -1;
    }else   {
        printf("parameter error is %s,should be 2;you can try './keyAPP -help'\n",argv[1]);
        return -1;
    }

    return 0;

fail_open:
    return -1;
}

//
// Created by x on 2/25/24.
//

#ifndef LEDAPP_BEEPAPP_H
#define LEDAPP_BEEPAPP_H

#include "chardevapp.h"
class keyAPP : public charDeviceAPP{
    using charDeviceAPP::charDeviceAPP;
public:
    typedef enum{
        no_key = 0,
        key0
    }KEY_VALUE;
    KEY_VALUE value;
};


#endif //LEDAPP_BEEPAPP_H
